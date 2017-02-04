// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Package ccir translates cc ASTs to intermediate representation. (Work In Progress)
package ccir

import (
	"fmt"
	"go/token"
	"os"
	"path"
	"runtime"

	"github.com/cznic/cc"
	"github.com/cznic/internal/buffer"
	"github.com/cznic/ir"
)

var (
	// Testing amends things for tests.
	Testing bool

	sizes = map[int]string{
		0:  "0",
		1:  "8",
		2:  "16",
		4:  "32",
		8:  "64",
		16: "128",
	}
)

//TODO remove me.
func TODO(more ...interface{}) string { //TODOOK
	_, fn, fl, _ := runtime.Caller(1)
	fmt.Fprintf(os.Stderr, "%s:%d: %v\n", path.Base(fn), fl, fmt.Sprint(more...)) //TODOOK
	os.Stderr.Sync()
	panic("TODO")
}

type c struct {
	ast    *cc.TranslationUnit
	ctypes map[cc.Type]ir.Type
	model  ir.MemoryModel
	out    []ir.Object
	types  ir.TypeCache
}

func newC(model ir.MemoryModel, ast *cc.TranslationUnit) *c {
	return &c{
		ast:    ast,
		ctypes: map[cc.Type]ir.Type{},
		model:  model,
		types:  ir.TypeCache{},
	}
}

func (c *c) nm2(d *cc.Declarator) (ir.NameID, *cc.Bindings) {
	id, sc := d.Identifier()
	return ir.NameID(id), sc
}

func (c *c) nm(d *cc.Declarator) ir.NameID {
	id, _ := d.Identifier()
	return ir.NameID(id)
}

func (c *c) tnm(d *cc.Declarator) ir.NameID { return ir.NameID(d.RawSpecifier().TypedefName()) }

func (c *c) typ0(dst *buffer.Bytes, t cc.Type) {
	for t.Kind() == cc.Ptr {
		dst.WriteByte('*')
		t = t.Element()
	}

	sou := "struct{"
	switch k := t.Kind(); k {
	case cc.Enum:
		dst.WriteString("int")
		dst.WriteString(sizes[c.ast.Model.Items[cc.Int].Size])
	case cc.Char, cc.SChar, cc.Short, cc.Int, cc.Long, cc.LongLong:
		dst.WriteString("int")
		dst.WriteString(sizes[c.ast.Model.Items[k].Size])
	case cc.UChar, cc.UShort, cc.UInt, cc.ULong, cc.ULongLong:
		dst.WriteString("uint")
		dst.WriteString(sizes[c.ast.Model.Items[k].Size])
	case cc.Float, cc.Double:
		dst.WriteString("float")
		dst.WriteString(sizes[c.ast.Model.Items[k].Size])
	case cc.Function:
		dst.WriteString("func(")
		p, variadic := t.Parameters()
		for i, v := range p {
			c.typ0(dst, v.Type)
			if i+1 < len(p) {
				dst.WriteByte(',')
			}
		}
		if variadic {
			dst.WriteString("...")
		}
		dst.WriteByte(')')
		if r := t.Result(); r.Kind() != cc.Void {
			c.typ0(dst, r)
		}
	case cc.Array:
		switch n := t.Elements(); {
		case n < 0:
			panic("internal error")
		default:
			dst.WriteByte('[')
			fmt.Fprintf(dst, "%d", n)
			dst.WriteByte(']')
			c.typ0(dst, t.Element())
		}
	case cc.Union:
		sou = "union{"
		fallthrough
	case cc.Struct:
		dst.WriteString(sou)
		switch m, incomplete := t.Members(); {
		case incomplete:
			TODO()
		default:
			for i, v := range m {
				t := v.Type
				if v.Bits != 0 {
					if v.BitOffsetOf != 0 {
						continue
					}

					t = v.BitFieldType
				}

				c.typ0(dst, t)
				if i+1 < len(m) {
					dst.WriteByte(',')
				}
			}
		}
		dst.WriteByte('}')
	case cc.Void:
		dst.WriteString("struct{}")
	default:
		panic(fmt.Errorf("internal error %v", k))
	}
}

func (c *c) typ(in cc.Type) ir.Type {
	if r := c.ctypes[in]; r != nil {
		return r
	}

	var dst buffer.Bytes
	c.typ0(&dst, in)
	out, err := c.types.Type(ir.TypeID(dict.ID(dst.Bytes())))
	if err != nil {
		panic(fmt.Errorf("internal error: %v", err))
	}

	dst.Close()
	return out
}

func (c *c) linkage(l cc.Linkage) ir.Linkage {
	switch l {
	case cc.External:
		return ir.ExternalLinkage
	case cc.Internal:
		return ir.InternalLinkage
	default:
		return ir.Linkage(0)
	}
}

func (c *c) initializer(n *cc.Initializer) ir.Value {
	if n == nil {
		return nil
	}

	TODO(position(n))
	panic("TODO")
}

func (c *c) initDeclarator(n *cc.InitDeclarator) (p token.Position, nm, tnm ir.NameID, typ ir.TypeID, l ir.Linkage, v ir.Value) {
	d := n.Declarator
	return position(n), c.nm(d), c.tnm(d), c.typ(d.Type).ID(), c.linkage(d.Linkage), c.initializer(n.Initializer)
}

func (c *c) fileScopeDeclaration(n *cc.Declaration) {
	switch n.Case {
	case 0: // DeclarationSpecifiers InitDeclaratorListOpt ';'
		if n.DeclarationSpecifiers.IsTypedef() {
			return
		}

		if o := n.InitDeclaratorListOpt; o != nil {
			for l := o.InitDeclaratorList; l != nil; l = l.InitDeclaratorList {
				c.out = append(c.out, ir.NewDeclaration(c.initDeclarator(l.InitDeclarator)))
			}
		}
	case 1: // StaticAssertDeclaration                          // Case 1
		TODO(position(n))
	default:
		panic("internal error")
	}
}

func (c *c) functionDefinition(n *cc.FunctionDefinition) {
	switch n.Case {
	case 0: // DeclarationSpecifiers Declarator DeclarationListOpt FunctionBody
		d := n.Declarator
		f := ir.NewFunctionDefinition(position(n), c.nm(d), c.tnm(d), c.typ(d.Type).ID(), c.linkage(d.Linkage))
		TODO(position(n), f)
	case 1: // Declarator DeclarationListOpt FunctionBody                        // Case 1
		TODO(position(n))
	default:
		panic("internal error")
	}
}

func (c *c) externalDeclaration(n *cc.ExternalDeclaration) {
	switch n.Case {
	case 0: // FunctionDefinition
		c.functionDefinition(n.FunctionDefinition)
	case 1: // Declaration                  // Case 1
		c.fileScopeDeclaration(n.Declaration)
	case 2: // BasicAssemblerStatement ';'  // Case 2
		TODO(position(n))
	case 3: // ';'                          // Case 3
		TODO(position(n))
	default:
		panic("internal error")
	}
}

func (c *c) gen() {
	for l := c.ast; l != nil; l = l.TranslationUnit {
		//TODO c.externalDeclaration(l.ExternalDeclaration)
	}
}

// New returns ir.Objects generated from ast or an error, if any. The modelName
// parameter is used to select a named memory model from ir.MemoryModels. The
// ast must have been produced using a cc.Model provided by the Model function
// for the same modelName. Scheme/example (error handling elided):
//
//	model, _ := ccir.Model(modelName)
//	ast, _ := cc.Parse(..., model, ...)
//	objects, ... := ccir.New(modelName, ast)
func New(modelName string, ast *cc.TranslationUnit) (_ []ir.Object, err error) {
	if !Testing {
		defer func() {
			switch x := recover().(type) {
			case nil:
				// nop
			case error:
				err = x
			default:
				err = fmt.Errorf("%v", x)
			}
		}()
	}

	model, ok := ir.MemoryModels[modelName]
	if !ok {
		return nil, fmt.Errorf("unknown memory model %q", modelName)
	}

	c := newC(model, ast)
	c.gen()
	return c.out, nil
}
