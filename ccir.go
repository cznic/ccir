// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Package ccir translates cc[0] ASTs to intermediate representation. (Work In Progress)
//
//  [0]: https://github.com/cznic/cc
package ccir

import (
	"fmt"
	"go/token"
	"math"
	"os"
	"path"
	"runtime"

	"github.com/cznic/cc"
	"github.com/cznic/internal/buffer"
	"github.com/cznic/ir"
	"github.com/cznic/mathutil"
	"github.com/cznic/virtual"
)

const (
	_ = iota //TODOOK
	stmtExprValue
	stmtExprAddress
)

var (
	// Testing amends things for tests.
	Testing bool

	isTesting bool // Running tests.

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
	fmt.Fprintf(os.Stderr, "%s:%d: %v\n", path.Base(fn), fl, fmt.Sprint(more...))
	os.Stderr.Sync()
	panic(fmt.Errorf("%s:%d: %v", path.Base(fn), fl, fmt.Sprint(more...)))
}

type labels struct {
	breakLabel    int
	caseLabel     int
	continueLabel int
}

func (l *labels) setBreak(n int) int {
	r := l.breakLabel
	l.breakLabel = n
	return r
}

func (l *labels) setContinue(n int) int {
	r := l.continueLabel
	l.continueLabel = n
	return r
}

type varInfo struct {
	index      int
	staticName ir.NameID
	typ        ir.TypeID

	arg    bool
	static bool
}

type fdata struct {
	arguments  []ir.TypeID
	blockLevel int
	cResult    cc.Type
	f          *ir.FunctionDefinition
	index      int // Current function object index.
	label      int
	loop       bool
	result     ir.TypeID
	static     int
	variable   int
	variables  map[*cc.Declarator]varInfo
}

type c struct {
	ast      *cc.TranslationUnit
	builtins map[ir.NameID]struct{}
	ctypes   map[cc.Type]ir.Type
	f        fdata
	model    ir.MemoryModel
	out      []ir.Object
	types    ir.TypeCache
}

func newC(model ir.MemoryModel, ast *cc.TranslationUnit) *c {
	return &c{
		ast:      ast,
		builtins: map[ir.NameID]struct{}{},
		ctypes:   map[cc.Type]ir.Type{},
		model:    model,
		types:    ir.TypeCache{},
	}
}

func (c *c) isVLA(t cc.Type) *cc.Expression {
	switch d := t.Declarator().DirectDeclarator; d.Case {
	case 0: // IDENTIFIER
		return nil
	case 1: // '(' Declarator ')'                                                 // Case 1
		TODO(position(d))
	case 2: // DirectDeclarator '[' TypeQualifierListOpt ExpressionOpt ']'        // Case 2
		o := d.ExpressionOpt
		if o == nil {
			return nil
		}

		if e := o.Expression; e.Value == nil {
			return e
		}

		return nil
	case 3: // DirectDeclarator '[' "static" TypeQualifierListOpt Expression ']'  // Case 3
		TODO(position(d))
	case 4: // DirectDeclarator '[' TypeQualifierList "static" Expression ']'     // Case 4
		TODO(position(d))
	case 5: // DirectDeclarator '[' TypeQualifierListOpt '*' ']'                  // Case 5
		TODO(position(d))
	case 6: // DirectDeclarator '(' ParameterTypeList ')'                         // Case 6
		return nil
	case 7: // DirectDeclarator '(' IdentifierListOpt ')'                         // Case 7
		return nil
	}
	panic("internal error")
}

func (c *c) nm(d *cc.Declarator) ir.NameID {
	id, _ := d.Identifier()
	return ir.NameID(id)
}

func (c *c) tnm(d *cc.Declarator) ir.NameID { return ir.NameID(d.RawSpecifier().TypedefName()) }

func (c *c) typ0(dst *buffer.Bytes, t cc.Type, flat bool) {
	sou := "struct{"
	switch k := t.Kind(); k {
	case cc.Ptr:
		dst.WriteByte('*')
		if flat {
			switch t.Element().Kind() {
			case cc.Struct, cc.Union, cc.Array:
				dst.WriteString("struct{}")
				return
			}
		}

		c.typ0(dst, t.Element(), flat)
	case cc.Enum:
		dst.WriteString("int")
		dst.WriteString(sizes[c.ast.Model.Items[cc.Int].Size])
	case cc.Bool, cc.Char, cc.SChar, cc.Short, cc.Int, cc.Long, cc.LongLong:
		dst.WriteString("int")
		dst.WriteString(sizes[c.ast.Model.Items[k].Size])
	case cc.UChar, cc.UShort, cc.UInt, cc.ULong, cc.ULongLong:
		dst.WriteString("uint")
		dst.WriteString(sizes[c.ast.Model.Items[k].Size])
	case cc.Float, cc.Double, cc.LongDouble:
		dst.WriteString("float")
		dst.WriteString(sizes[c.ast.Model.Items[k].Size])
	case cc.FloatComplex, cc.DoubleComplex, cc.LongDoubleComplex:
		dst.WriteString("complex")
		dst.WriteString(sizes[c.ast.Model.Items[k].Size])
	case cc.Function:
		dst.WriteString("func(")
		p, variadic := t.Parameters()
		for i, v := range p {
			c.typ0(dst, v.Type, flat)
			if i+1 < len(p) {
				dst.WriteByte(',')
			}
		}
		if variadic {
			dst.WriteString("...")
		}
		dst.WriteByte(')')
		if r := t.Result(); r.Kind() != cc.Void {
			c.typ0(dst, r, flat)
		}
	case cc.Array:
		switch n := t.Elements(); {
		case n < 0:
			panic("internal error")
		default:
			dst.WriteByte('[')
			fmt.Fprintf(dst, "%d", n)
			dst.WriteByte(']')
			c.typ0(dst, t.Element(), flat)
		}
	case cc.Union:
		sou = "union{"
		fallthrough
	case cc.Struct:
		dst.WriteString(sou)
		switch m, incomplete := t.Members(); {
		case incomplete:
			// nop
		default:
			for i, v := range m {
				t := v.Type
				if c.isVLA(t) != nil {
					panic(fmt.Errorf("%s: struct/union member cannot be a variable length array", position(t.Declarator())))
				}

				if v.Bits != 0 {
					if v.BitOffsetOf != 0 {
						continue
					}

					t = v.BitFieldType
					if t == nil {
						t = c.ast.Model.IntType
					}
				}

				c.typ0(dst, t, true)
				if i+1 < len(m) {
					dst.WriteByte(',')
				}
			}
		}
		dst.WriteByte('}')
	case cc.Void:
		dst.WriteString("struct{}")
	default:
		panic(fmt.Errorf("internal error %v:%v", t, k))
	}
}

func (c *c) typ(in cc.Type) ir.Type {
	if r := c.ctypes[in]; r != nil {
		return r
	}

	var dst buffer.Bytes
	c.typ0(&dst, in, false)
	out, err := c.types.Type(ir.TypeID(dict.ID(dst.Bytes())))
	if err != nil {
		dst.Close()
		panic(fmt.Errorf("%s: type %q:%q, type specifier %q: internal error: %v", position(in.Declarator()), in, in.Kind(), dst.Bytes(), err))
	}

	dst.Close()
	return out
}

func (c *c) typeID(in cc.Type) ir.TypeID {
	if in == nil {
		return 0
	}

	return c.typ(in).ID()
}

func (c *c) linkage(l cc.Linkage) ir.Linkage {
	switch l {
	case cc.External:
		return ir.ExternalLinkage
	case cc.Internal:
		return ir.InternalLinkage
	case cc.None:
		return ir.Linkage(-1)
	default:
		panic("internal error")
	}
}

func (c *c) addressInitializer(n *cc.Expression) ir.Value {
	n = c.normalize(n)
	switch n.Case {
	case 0: // IDENTIFIER
		if n.Type.Kind() == cc.Function {
			id := n.Token.Val
			b, s := n.IdentResolutionScope().Lookup2(cc.NSIdentifiers, id)
			d := b.Node.(*cc.DirectDeclarator).TopDeclarator()
			switch s.Scope() {
			case cc.ScopeFile:
				return &ir.AddressValue{Index: -1, Linkage: c.linkage(d.Linkage), NameID: c.nm(d)}
			}
		}
	case 17: // '&' Expression                                     // Case 17
		switch n := n.Expression; n.Case {
		case 0: // IDENTIFIER
			id := n.Token.Val
			b, s := n.IdentResolutionScope().Lookup2(cc.NSIdentifiers, id)
			d := b.Node.(*cc.DirectDeclarator).TopDeclarator()
			switch s.Scope() {
			case cc.ScopeFile:
				return &ir.AddressValue{Index: -1, Linkage: c.linkage(d.Linkage), NameID: c.nm(d)}
			}
		}
	}
	return nil
}

func (c *c) arrayInitializerList(t cc.Type, n *cc.InitializerList) (ir.Value, bool) {
	values := &ir.CompositeValue{}
	complete := true
	var designators int
	elem := t.Element()
	for l := n; l != nil; l = l.InitializerList {
		val, init := c.initializer(elem, l.Initializer, false)
		if init != nil {
			complete = false
		}

		if o := l.DesignationOpt; o != nil {
			dl := o.Designation.DesignatorList
			if dl.DesignatorList != nil {
				TODO(position(n))
			}

			switch d := dl.Designator; d.Case {
			case 0: // '[' ConstantExpression ']'
				TODO(position(n))
			case 1: // '.' IDENTIFIER              // Case 1
				panic("internal error")
			default:
				panic("internal error")
			}
		}

		values.Values = append(values.Values, val)
	}
	if designators != 0 {
		TODO(position(n))
	}

	return values, complete
}

func (c *c) members(t cc.Type) []cc.Member {
	members, incomplete := t.Members()
	if incomplete {
		TODO(position(t.Declarator()))
	}

	w := 0
	for _, v := range members {
		if v.Name == 0 {
			continue
		}

		members[w] = v
		w++
	}
	return members[:w]
}

func (c *c) structInitializerList(t cc.Type, n *cc.InitializerList) (ir.Value, bool) {
	members := c.members(t)
	if len(members) == 1 && n.Len() > 1 {
		if t0 := members[0].Type; t0.Kind() == cc.Array {
			val, complete := c.arrayInitializerList(t0, n)
			if val != nil {
				val = &ir.CompositeValue{Values: []ir.Value{val}}
			}
			return val, complete
		}
	}

	values := make([]ir.Value, len(members))
	complete := true
	var i int
	for l := n; l != nil; l = l.InitializerList {
	search2:
		switch in := l.Initializer; in.Case {
		case 2: // IDENTIFIER ':' Initializer        // Case 2
			nm := in.Token.Val
			for j, v := range members {
				if v.Name == nm {
					i = j
					break search2
				}
			}

			panic("internal error")
		default:
			if o := l.DesignationOpt; o != nil {
				dl := o.Designation.DesignatorList
				if dl.DesignatorList != nil {
					TODO(position(n))
				}

			search:
				switch d := dl.Designator; d.Case {
				case 0: // '[' ConstantExpression ']'
					panic("internal error")
				case 1: // '.' IDENTIFIER              // Case 1
					nm := d.Token2.Val
					for j, v := range members {
						if v.Name == nm {
							i = j
							break search
						}
					}

					panic("internal error")
				default:
					panic("internal error")
				}
			}
		}

		ft := members[i].Type
		val, init := c.initializer(ft, l.Initializer, true)
		if init != nil {
			complete = false
		}
		values[i] = val
		i++
	}

	iField := 0
	iValue := 0
	for i := 0; i < len(members) && iValue < len(values); i++ {
		m := members[i]
		if m.Bits != 0 {
			group := m.BitFieldGroup
			groupStart := i
			groupEnd := len(members)
			for ; i < len(members); i++ {
				if members[i].Bits == 0 || members[i].BitFieldGroup != group {
					groupEnd = i
					i--
					break
				}
			}

			var bval uint64
			var val ir.Value
			for j := groupStart; j < groupEnd && iValue < len(values); j++ {
				var bits uint64
				switch x := values[iValue].(type) {
				case nil:
					// ok
				case *ir.Int32Value:
					bits = uint64(x.Value)
				case *ir.Int64Value:
					bits = uint64(x.Value)
				default:
					panic(fmt.Errorf("%s: TODO %T", position(n), x))
				}
				bits &= 1<<uint(members[j].Bits) - 1
				bval |= bits << uint(members[j].BitOffsetOf)
				iValue++
			}

			if bval != 0 {
				switch {
				case bval > math.MaxUint32:
					val = &ir.Int64Value{Value: int64(bval)}
				default:
					val = &ir.Int32Value{Value: int32(bval)}
				}
			}

			// The bit field group has zero value.
			values[iField] = val
			iField++
			continue
		}

		// Normal field.
		values[iField] = values[iValue]
		iValue++
		iField++
	}
	values = values[:iField]
	w := -1
	for i, v := range values {
		if v != nil {
			w = i
		}
	}
	values = values[:w+1]
	return &ir.CompositeValue{Values: values}, complete
}

func (c *c) initializerList(t cc.Type, n *cc.InitializerList) (ir.Value, bool) {
	switch t.Kind() {
	case cc.Array, cc.Ptr:
		return c.arrayInitializerList(t, n)
	case cc.Struct, cc.Union:
		return c.structInitializerList(t, n)
	default:
		panic(fmt.Errorf("%s: internal error %v %v", position(n), t, t.Kind()))
	}
}

func (c *c) initializer(t cc.Type, n *cc.Initializer, ok bool) (ir.Value, *cc.Initializer) {
	if n == nil {
		return nil, nil
	}

	switch n.Case {
	case 0: // Expression
		switch x := n.Expression.Value.(type) {
		case nil:
			if val := c.addressInitializer(n.Expression); val != nil {
				return val, nil
			}

			return nil, n
		case cc.StringLitID:
			return &ir.StringValue{StringID: ir.StringID(x)}, nil
		case cc.LongStringLitID:
			return &ir.WideStringValue{Value: []rune(string(dict.S(int(x))))}, nil
		case int8:
			return &ir.Int32Value{Value: int32(x)}, nil
		case uint8:
			return &ir.Int32Value{Value: int32(x)}, nil
		case int16:
			return &ir.Int32Value{Value: int32(x)}, nil
		case uint16:
			return &ir.Int32Value{Value: int32(x)}, nil
		case int32:
			return &ir.Int32Value{Value: x}, nil
		case uint32:
			if x <= math.MaxInt32 {
				return &ir.Int32Value{Value: int32(x)}, nil
			}

			return &ir.Int64Value{Value: int64(x)}, nil
		case int64:
			switch {
			case x >= math.MinInt32 && x <= math.MaxInt32:
				return &ir.Int32Value{Value: int32(x)}, nil
			default:
				return &ir.Int64Value{Value: x}, nil
			}
		case float32:
			return &ir.Float32Value{Value: x}, nil
		case float64:
			return &ir.Float64Value{Value: x}, nil
		case uint64:
			switch {
			case x <= math.MaxInt32:
				return &ir.Int32Value{Value: int32(x)}, nil
			default:
				return &ir.Int64Value{Value: int64(x)}, nil
			}
		case uintptr:
			switch {
			case x <= math.MaxInt32:
				return &ir.Int32Value{Value: int32(x)}, nil
			default:
				return &ir.Int64Value{Value: int64(x)}, nil
			}
		case complex64:
			return &ir.Complex64Value{Value: x}, nil
		case complex128:
			return &ir.Complex128Value{Value: x}, nil
		case cc.ComputedGotoID:
			return &ir.AddressValue{NameID: c.f.f.NameID, Linkage: c.f.f.Linkage, Label: ir.NameID(x), Index: -1}, nil
		default:
			TODO(position(n), fmt.Sprintf(" %T", x))
		}
	case 1: // '{' InitializerList CommaOpt '}'  // Case 1
		init := n
		val, ok := c.initializerList(t, n.InitializerList)
		if ok {
			init = nil
		}

		return val, init
	case 2: // IDENTIFIER ':' Initializer        // Case 2
		if ok {
			return c.initializer(t, n.Initializer, false)
		}

		TODO(position(n), t)
	}
	panic("internal error")
}

func (c *c) exprInitializerListStructField(t, ft cc.Type, pt ir.Type, i, nm int, n *cc.InitializerList) int {
	if o := n.DesignationOpt; o != nil {
		l := o.Designation.DesignatorList
		if l.DesignatorList != nil {
			TODO(position(n))
		}

	outer:
		switch d := l.Designator; d.Case {
		case 0: // '[' ConstantExpression ']'
			panic("internal error")
		case 1: // '.' IDENTIFIER              // Case 1
			nm = d.Token2.Val
			members, _ := t.Members()
			for j, v := range members {
				if v.Name == nm {
					i = j
					ft = v.Type
					break outer
				}
			}

			panic("internal error")
		default:
			panic("internal error")
		}
	}

	fi, bits, bitoff, bt, vt := c.field(n, t, nm)
	c.emit(&ir.Field{Address: true, TypeID: pt.ID(), Index: fi, Position: position(n)})

	switch init := n.Initializer; init.Case {
	case 0: // Expression
		if bits != 0 {
			c.expression(bt, init.Expression)
			bt := c.typ(bt).ID()
			vt := c.typ(vt).ID()
			c.emit(&ir.Store{Bits: bits, BitOffset: bitoff, BitFieldType: bt, TypeID: vt, Position: position(init)})
			c.emit(&ir.Drop{TypeID: bt, Position: position(init)})
			break
		}

		c.expression(ft, init.Expression)
		c.emit(&ir.Store{TypeID: c.typ(ft).ID(), Position: position(init)})
		c.emit(&ir.Drop{TypeID: c.typ(ft).ID(), Position: position(init)})
	case 1: // '{' InitializerList CommaOpt '}'  // Case 1
		switch ft.Kind() {
		case cc.Array:
			pt := c.typ(ft.Element().Pointer())
			c.exprInitializerArray(ft, pt, init.InitializerList)
			c.emit(&ir.Drop{TypeID: pt.ID(), Position: position(init)})
		case cc.Struct:
			c.exprInitializerStruct(t, c.typ(t).Pointer(), init.InitializerList)
		default:
			panic(fmt.Errorf("%s: %v:%v", position(n.Initializer), ft, ft.Kind()))
		}
	default:
		panic("internal error")
	}
	i++
	return i
}

func (c *c) exprInitializerListArrayElement(t, et cc.Type, pt ir.Type, i int, n *cc.InitializerList) int {
	if o := n.DesignationOpt; o != nil {
		TODO(position(n))
	}

	c.emit(&ir.Const32{TypeID: idInt32, Value: int32(i), Position: position(n)})
	c.emit(&ir.Element{Address: true, IndexType: idInt32, TypeID: c.typ(et.Pointer()).ID(), Position: position(n)})
	switch init := n.Initializer; init.Case {
	case 0: // Expression
		c.expression(et, init.Expression)
		c.emit(&ir.Store{TypeID: c.typ(et).ID(), Position: position(init)})
		c.emit(&ir.Drop{TypeID: c.typ(et).ID(), Position: position(init)})
	case 1: // '{' InitializerList CommaOpt '}'  // Case 1
		TODO(position(n))
	default:
		panic("internal error")
	}
	i++
	return i
}

func (c *c) exprInitializerStruct(t cc.Type, pt ir.Type, l *cc.InitializerList) {
	i := 0
	ma := c.members(t)
	for ; l != nil; l = l.InitializerList {
		c.emit(&ir.Dup{TypeID: pt.ID(), Position: position(l)})
		i = c.exprInitializerListStructField(t, ma[i].Type, pt, i, ma[i].Name, l)
	}
}

func (c *c) exprInitializerArray(t cc.Type, pt ir.Type, l *cc.InitializerList) {
	e := t.Element()
	i := 0
	for ; l != nil; l = l.InitializerList {
		c.emit(&ir.Dup{TypeID: pt.ID(), Position: position(l)})
		i = c.exprInitializerListArrayElement(t, e, pt, i, l)
	}
}

func (c *c) exprInitializerList(t cc.Type, vi int, vp token.Position, l *cc.InitializerList) {
	var pt ir.Type
	switch t.Kind() {
	case cc.Struct, cc.Union:
		pt = c.typ(t).Pointer()
		c.emit(&ir.Variable{Address: true, Index: vi, TypeID: pt.ID(), Position: vp})
		c.exprInitializerStruct(t, pt, l)
	case cc.Array:
		pt = c.typ(t.Element().Pointer())
		c.emit(&ir.Variable{Address: true, Index: vi, TypeID: pt.ID(), Position: vp})
		c.exprInitializerArray(t, pt, l)
	default:
		TODO(position(l.Initializer), t.Kind())
	}
	c.emit(&ir.Drop{TypeID: pt.ID(), Position: vp})
}

func (c *c) staticDeclaration(d *cc.Declarator, l *cc.InitDeclaratorList) {
	typ := c.typ(d.Type).ID()
	val, init := c.initializer(l.InitDeclarator.Declarator.Type, l.InitDeclarator.Initializer, false)
	var b buffer.Bytes
	// func\x00varname\x00index
	b.Write(dict.S(int(c.f.f.NameID)))
	b.WriteByte(0)
	b.Write(dict.S(int(c.nm(d))))
	b.WriteByte(0)
	fmt.Fprintf(&b, "%v", c.f.static)
	snm := ir.NameID(dict.ID(b.Bytes()))
	b.Close()
	c.f.variables[d] = varInfo{index: c.f.static, static: true, typ: typ, staticName: snm}
	c.out = append(c.out, ir.NewDataDefinition(position(d), snm, c.tnm(d), typ, ir.InternalLinkage, val))
	c.f.static++
	if init != nil {
		TODO(position(init))
	}
}

func (c *c) isStaticInitializer(t cc.Type, n *cc.Initializer, list bool) bool {
	if n == nil {
		return true
	}

	switch n.Case {
	case 0: // Expression
		switch x := n.Expression.Value.(type) {
		case nil:
			return false
		case cc.StringLitID:
			return !list && t != nil && t.Kind() == cc.Array
		case int32, uint32, int64, uint64, float32, float64, complex64, complex128, uintptr:
			return true
		case cc.ComputedGotoID:
			return true
		default:
			panic(fmt.Errorf("%s: TODO %T", position(n), x))
		}
	case 1: // '{' InitializerList CommaOpt '}'  // Case 1
		for l := n.InitializerList; l != nil; l = l.InitializerList {
			if !c.isStaticInitializer(t, l.Initializer, true) {
				return false
			}
		}

		return true
	case 2: // IDENTIFIER ':' Initializer        // Case 2
		m, err := t.Member(n.Token.Val)
		if err != nil {
			panic(fmt.Errorf("%s: type %v has no member %s", position(n), t, dict.S(n.Token.Val)))
		}

		return c.isStaticInitializer(m.Type, n.Initializer, false)
	}
	panic("internal error")
}

func (c *c) isCompoundInitializer(n *cc.Initializer) bool {
	return n != nil && n.Case == 1 // '{' InitializerList CommaOpt '}'  // Case 1
}

func (c *c) variableDeclaration(d *cc.Declarator, l *cc.InitDeclaratorList, alwaysEvalInitializers bool) {
	var val ir.Value
	init := l.InitDeclarator.Initializer
	if c.isCompoundInitializer(init) {
		val = &ir.CompositeValue{}
	}
	if !alwaysEvalInitializers && c.isStaticInitializer(d.Type, init, false) {
		val, init = c.initializer(l.InitDeclarator.Declarator.Type, init, false)
	}
	vx := c.f.variable
	c.f.variable++
	typ := c.typ(d.Type).ID()
	c.f.variables[d] = varInfo{index: vx, typ: typ}
	c.emit(&ir.VariableDeclaration{Index: vx, NameID: c.nm(d), TypeID: typ, TypeName: c.tnm(d), Value: val, Position: position(d)})
	if init != nil {
		switch init.Case {
		case 0: // Expression
			pt := c.types.MustType(typ).Pointer().ID()
			c.emit(&ir.Variable{Address: true, Index: vx, TypeID: pt, Position: position(d)})
			c.expression(d.Type, init.Expression)
			c.emit(&ir.Store{TypeID: typ, Position: position(d)})
			c.emit(&ir.Drop{TypeID: typ, Position: position(d)})
		case 1: // '{' InitializerList CommaOpt '}'  // Case 1
			c.exprInitializerList(d.Type, vx, position(init), init.InitializerList)
		default:
			panic("internal error")
		}
	}
}

func (c *c) declaration(n *cc.Declaration, alwaysEvalInitializers bool) {
	switch n.Case {
	case 0: // DeclarationSpecifiers InitDeclaratorListOpt ';'
		if n.DeclarationSpecifiers.IsTypedef() {
			return
		}

		o := n.InitDeclaratorListOpt
		if o == nil {
			break
		}

		for l := o.InitDeclaratorList; l != nil; l = l.InitDeclaratorList {
			d := l.InitDeclarator.Declarator
			id, _ := d.Identifier()
			isFunc := d.Type.Kind() == cc.Function
			if isFunc && virtual.IsBuiltin(ir.NameID(id)) && !d.Type.Specifier().IsExtern() {
				if _, ok := c.builtins[ir.NameID(id)]; ok {
					continue
				}

				f := ir.NewFunctionDefinition(position(d), c.nm(d), c.tnm(d), c.typ(d.Type).ID(), c.linkage(d.Linkage), c.fnArgNames(d), nil)
				f.Body = []ir.Operation{&ir.Panic{Position: position(d)}}
				c.out = append(c.out, f)
				c.builtins[ir.NameID(id)] = struct{}{}
				continue
			}

			if d.Type.Specifier().IsExtern() || isFunc {
				continue
			}

			switch ln := c.linkage(d.Linkage); {
			case ln < 0: // linkage none
				if d.RawSpecifier().IsStatic() {
					c.staticDeclaration(d, l)
					break
				}

				c.variableDeclaration(d, l, alwaysEvalInitializers)
			default: // external, internal
				val, init := c.initializer(l.InitDeclarator.Declarator.Type, l.InitDeclarator.Initializer, false)
				if init != nil {
					TODO(position(init), val, c.typ(d.Type))
				}

				c.out = append(c.out, ir.NewDataDefinition(position(d), c.nm(d), c.tnm(d), c.typ(d.Type).ID(), ln, val))
			}
		}
	case 1: // StaticAssertDeclaration                          // Case 1
		TODO(position(n))
	default:
		panic("internal error")
	}
}

func (c *c) newFData(t cc.Type, f *ir.FunctionDefinition) {
	variables := map[*cc.Declarator]varInfo{}
	params, _ := t.Parameters()
	f.Arguments = make([]ir.NameID, len(params))
	for i, v := range params {
		f.Arguments[i] = ir.NameID(v.Name)
		variables[v.Declarator] = varInfo{index: i, arg: true, typ: c.typ(v.Type).ID()}
	}
	typ := c.types.MustType(f.TypeID).(*ir.FunctionType)
	var result ir.TypeID
	if len(typ.Results) != 0 {
		result = typ.Results[0].ID()
	}
	arguments := make([]ir.TypeID, len(typ.Arguments))
	for i, v := range typ.Arguments {
		arguments[i] = v.ID()
	}
	cResult := t.Result()
	if cResult.Kind() == cc.Void && f.NameID == idMain && f.Linkage == ir.ExternalLinkage {
		cResult = c.ast.Model.IntType
	}
	c.f = fdata{
		arguments: arguments,
		cResult:   cResult,
		f:         f,
		result:    result,
		variables: variables,
	}
}

func (c *c) emit(op ir.Operation) { c.f.f.Body = append(c.f.f.Body, op) }

func (c *c) arguments(f cc.Type, n *cc.ArgumentExpressionListOpt) int {
	args := 0
	if n != nil {
		for l := n.ArgumentExpressionList; l != nil; l = l.ArgumentExpressionList {
			args++
		}
	}
	c.emit(&ir.Arguments{Position: position(n)})
	p, _ := f.Parameters()
	if n != nil {
		i := 0
		for l := n.ArgumentExpressionList; l != nil; l = l.ArgumentExpressionList {
			var t cc.Type
			if i < len(p) {
				t = p[i].Type
			}
			if t == nil { // 6.5.2.2/6
				switch l.Expression.Type.Kind() {
				case cc.Char, cc.SChar, cc.UChar, cc.Short, cc.UShort:
					t = c.ast.Model.IntType
				case cc.Float:
					t = c.ast.Model.DoubleType
				}
			}
			c.expression(t, l.Expression)
			i++
		}
	}
	return args
}

func (c *c) dd(b *cc.Bindings, n cc.Node, nm int) (*cc.DirectDeclarator, *cc.Bindings) {
	switch x, s := b.Lookup2(cc.NSIdentifiers, nm); x := x.Node.(type) {
	case *cc.DirectDeclarator:
		return x, s
	case nil:
		var buf buffer.Bytes
		buf.Write(dict.S(idBuiltinPrefix))
		buf.Write(dict.S(nm))
		nm2 := dict.ID(buf.Bytes())
		buf.Close()
		switch x, s := b.Lookup2(cc.NSIdentifiers, nm2); x := x.Node.(type) {
		case *cc.DirectDeclarator:
			return x, s
		}

		panic(fmt.Errorf("%s: undefined %s", position(n), dict.S(nm)))
	default:
		panic(fmt.Errorf("%s: internal error %T", position(n), x))
	}
}

func (c *c) normalize(n *cc.Expression) *cc.Expression {
	for {
		switch n.Case {
		case 7: // '(' ExpressionList ')'
			l := n.ExpressionList
			if l.Len() != 1 {
				return n
			}

			n = l.Expression
		default:
			switch n.Case {
			case 0: // IDENTIFIER
				if x, _ := c.dd(n.IdentResolutionScope(), n, n.Token.Val); x != nil {
					n.Type = x.TopDeclarator().Type
					return n
				}

				panic(fmt.Errorf("%s: undefined %s", position(n), dict.S(n.Token.Val)))
			case 9: // Expression '(' ArgumentExpressionListOpt ')'       // Case 9
				n.Expression = c.normalize(n.Expression)
				t := n.Expression.Type
				if t.Kind() == cc.Ptr {
					t = t.Element()
				}
				if t.Kind() == cc.Function {
					n.Type = t.Result()
				}
			}
			return n
		}
	}
}

func (c *c) field(n cc.Node, st cc.Type, nm int) (index, bits, bitoff int, bitFieldType, valueType cc.Type) {
	ms, incomplete := st.Members()
	if incomplete {
		TODO(position(n))
	}

	group := -1
	for _, v := range ms {
		if v.Name == nm {
			if v.Bits != 0 {
				if v.BitFieldType == nil {
					v.BitFieldType = c.ast.Model.IntType
				}
				if v.Type == nil {
					v.Type = c.ast.Model.IntType
				}
				if group >= 0 && v.BitFieldGroup != group {
					index++
				}
				return index, v.Bits, v.BitOffsetOf, v.BitFieldType, v.Type
			}

			if group >= 0 {
				index++
			}
			return index, 0, 0, nil, v.Type
		}

		switch {
		case v.Bits != 0:
			if v.BitFieldGroup == group {
				continue
			}

			if group < 0 {
				group = v.BitFieldGroup
				continue
			}
		default:
			if group >= 0 {
				index++
			}
			group = -1
		}

		index++
	}
	panic(fmt.Errorf("%s: internal error: %s", position(n), st))
}

func (c *c) compoundLiteral(n *cc.Expression) varInfo {
	t := n.TypeName.Type
	typ := c.typ(t).ID()
	vx := c.f.variable
	c.f.variable++
	nfo := varInfo{index: vx, typ: typ}
	c.emit(&ir.VariableDeclaration{Index: vx, TypeID: typ, Position: position(n)})
	c.exprInitializerList(t, vx, position(n), n.InitializerList)
	return nfo
}

func (c *c) addr(n *cc.Expression) (bits, bitoff int, bfType, vtype cc.Type) {
	n = c.normalize(n)
	if n.Value != nil {
		TODO(position(n))
		return 0, 0, nil, nil
	}

	switch n.Case {
	case 0: // IDENTIFIER
		id := n.Token.Val
		dd, s := c.dd(n.IdentResolutionScope(), n, id)
		d := dd.TopDeclarator()
		switch s.Scope() {
		case cc.ScopeBlock:
			switch vi, ok := c.f.variables[d]; {
			case !ok:
				t := d.Type
				for s.Scope() == cc.ScopeBlock {
					s = s.Parent
				}
				dd, _ := c.dd(s, n, id)
				d := dd.TopDeclarator()
				n.Type = d.Type
				switch d.Linkage {
				case cc.External:
					c.emit(&ir.Global{Address: true, Index: -1, Linkage: ir.ExternalLinkage, NameID: c.nm(d), TypeID: c.typ(t.Pointer()).ID(), TypeName: c.tnm(d), Position: position(n)})
				default:
					c.emit(&ir.Global{Address: true, Index: -1, Linkage: ir.InternalLinkage, NameID: c.nm(d), TypeID: c.typ(t.Pointer()).ID(), TypeName: c.tnm(d), Position: position(n)})
				}
			case vi.static:
				t, _ := c.types.Type(vi.typ)
				switch {
				case t.Kind() == ir.Array:
					t = t.(*ir.ArrayType).Item.Pointer()
				default:
					t = t.Pointer()
				}
				c.emit(&ir.Global{Address: true, Index: -1, Linkage: ir.InternalLinkage, NameID: vi.staticName, TypeID: t.ID(), Position: position(n)})
			case vi.arg:
				at := c.f.arguments[vi.index]
				t := c.types.MustType(at)
				switch t.Kind() {
				case ir.Array:
					c.emit(&ir.Argument{Index: vi.index, TypeID: t.(*ir.ArrayType).Item.Pointer().ID(), Position: position(n)})
				default:
					c.emit(&ir.Argument{Address: true, Index: vi.index, TypeID: t.Pointer().ID(), Position: position(n)})
				}
			default:
				t, _ := c.types.Type(vi.typ)
				switch {
				case t.Kind() == ir.Array:
					t = t.(*ir.ArrayType).Item.Pointer()
				default:
					t = t.Pointer()
				}
				c.emit(&ir.Variable{Address: true, Index: vi.index, TypeID: t.ID(), Position: position(n)})
			}
		case cc.ScopeFile:
			t := d.Type
			if t.Kind() == cc.Array {
				t = t.Element()
			}
			switch d.Linkage {
			case cc.External:
				c.emit(&ir.Global{Address: true, Index: -1, Linkage: ir.ExternalLinkage, NameID: c.nm(d), TypeID: c.typ(t.Pointer()).ID(), TypeName: c.tnm(d), Position: position(n)})
			default:
				c.emit(&ir.Global{Address: true, Index: -1, Linkage: ir.InternalLinkage, NameID: c.nm(d), TypeID: c.typ(t.Pointer()).ID(), TypeName: c.tnm(d), Position: position(n)})
			}
		default:
			panic("internal error")
		}
		return 0, 0, nil, nil
	case 1: // CHARCONST                                          // Case 1
		TODO(position(n))
	case 2: // FLOATCONST                                         // Case 2
		TODO(position(n))
	case 3: // INTCONST                                           // Case 3
		TODO(position(n))
	case 4: // LONGCHARCONST                                      // Case 4
		TODO(position(n))
	case 5: // LONGSTRINGLITERAL                                  // Case 5
		TODO(position(n))
	case 6: // STRINGLITERAL                                      // Case 6
		TODO(position(n))
	case 7: // '(' ExpressionList ')'                             // Case 7
		TODO(position(n))
	case 8: // Expression '[' ExpressionList ']'                  // Case 8
		t := n.Expression.Type
		if t.Kind() == cc.Array {
			t = t.Element().Pointer()
		}
		c.expression(nil, n.Expression)
		c.expressionList(nil, n.ExpressionList)
		c.emit(&ir.Element{Address: true, IndexType: c.typ(n.ExpressionList.Type).ID(), TypeID: c.typ(t).ID(), Position: position(n)})
		return 0, 0, nil, nil
	case 9: // Expression '(' ArgumentExpressionListOpt ')'       // Case 9
		TODO(position(n))
	case 10: // Expression '.' IDENTIFIER                          // Case 10
		c.addr(n.Expression)
		fi, bits, bitoff, bt, vt := c.field(n, n.Expression.Type, n.Token2.Val)
		c.emit(&ir.Field{Address: true, Index: fi, TypeID: c.typ(n.Expression.Type.Pointer()).ID(), Position: position(n)})
		return bits, bitoff, bt, vt
	case 11: // Expression "->" IDENTIFIER                         // Case 11
		c.expression(nil, n.Expression)
		fi, bits, bitoff, bt, vt := c.field(n, n.Expression.Type.Element(), n.Token2.Val)
		t := n.Expression.Type
		if t.Kind() == cc.Array {
			t = t.Element().Pointer()
		}
		c.emit(&ir.Field{Address: true, Index: fi, TypeID: c.typ(t).ID(), Position: position(n.Token2)})
		return bits, bitoff, bt, vt
	case 12: // Expression "++"                                    // Case 12
		TODO(position(n))
	case 13: // Expression "--"                                    // Case 13
		TODO(position(n))
	case 14: // '(' TypeName ')' '{' InitializerList CommaOpt '}'  // Case 14
		vi := c.compoundLiteral(n)
		t, _ := c.types.Type(vi.typ)
		switch {
		case t.Kind() == ir.Array:
			t = t.(*ir.ArrayType).Item.Pointer()
		default:
			t = t.Pointer()
		}
		c.emit(&ir.Variable{Address: true, Index: vi.index, TypeID: t.ID(), Position: position(n)})
		return 0, 0, nil, nil
	case 15: // "++" Expression                                    // Case 15
		TODO(position(n))
	case 16: // "--" Expression                                    // Case 16
		TODO(position(n))
	case 17: // '&' Expression                                     // Case 17
		TODO(position(n))
	case 18: // '*' Expression                                     // Case 18
		c.expression(nil, n.Expression)
		return 0, 0, nil, nil
	case 19: // '+' Expression                                     // Case 19
		TODO(position(n))
	case 20: // '-' Expression                                     // Case 20
		TODO(position(n))
	case 21: // '~' Expression                                     // Case 21
		TODO(position(n))
	case 22: // '!' Expression                                     // Case 22
		TODO(position(n))
	case 23: // "sizeof" Expression                                // Case 23
		TODO(position(n))
	case 24: // "sizeof" '(' TypeName ')'                          // Case 24
		TODO(position(n))
	case 25: // '(' TypeName ')' Expression                        // Case 25
		TODO(position(n))
	case 26: // Expression '*' Expression                          // Case 26
		TODO(position(n))
	case 27: // Expression '/' Expression                          // Case 27
		TODO(position(n))
	case 28: // Expression '%' Expression                          // Case 28
		TODO(position(n))
	case 29: // Expression '+' Expression                          // Case 29
		TODO(position(n))
	case 30: // Expression '-' Expression                          // Case 30
		TODO(position(n))
	case 31: // Expression "<<" Expression                         // Case 31
		TODO(position(n))
	case 32: // Expression ">>" Expression                         // Case 32
		TODO(position(n))
	case 33: // Expression '<' Expression                          // Case 33
		TODO(position(n))
	case 34: // Expression '>' Expression                          // Case 34
		TODO(position(n))
	case 35: // Expression "<=" Expression                         // Case 35
		TODO(position(n))
	case 36: // Expression ">=" Expression                         // Case 36
		TODO(position(n))
	case 37: // Expression "==" Expression                         // Case 37
		TODO(position(n))
	case 38: // Expression "!=" Expression                         // Case 38
		TODO(position(n))
	case 39: // Expression '&' Expression                          // Case 39
		TODO(position(n))
	case 40: // Expression '^' Expression                          // Case 40
		TODO(position(n))
	case 41: // Expression '|' Expression                          // Case 41
		TODO(position(n))
	case 42: // Expression "&&" Expression                         // Case 42
		TODO(position(n))
	case 43: // Expression "||" Expression                         // Case 43
		TODO(position(n))
	case 44: // Expression '?' ExpressionList ':' Expression       // Case 44
		switch n.Type.Kind() {
		case cc.Function:
			c.condExpr(n)
		default:
			TODO(position(n))
		}
		return 0, 0, nil, nil
	case 45: // Expression '=' Expression                          // Case 45
		TODO(position(n))
	case 46: // Expression "*=" Expression                         // Case 46
		TODO(position(n))
	case 47: // Expression "/=" Expression                         // Case 47
		TODO(position(n))
	case 48: // Expression "%=" Expression                         // Case 48
		TODO(position(n))
	case 49: // Expression "+=" Expression                         // Case 49
		TODO(position(n))
	case 50: // Expression "-=" Expression                         // Case 50
		TODO(position(n))
	case 51: // Expression "<<=" Expression                        // Case 51
		TODO(position(n))
	case 52: // Expression ">>=" Expression                        // Case 52
		TODO(position(n))
	case 53: // Expression "&=" Expression                         // Case 53
		TODO(position(n))
	case 54: // Expression "^=" Expression                         // Case 54
		TODO(position(n))
	case 55: // Expression "|=" Expression                         // Case 55
		TODO(position(n))
	case 56: // "_Alignof" '(' TypeName ')'                        // Case 56
		TODO(position(n))
	case 57: // '(' CompoundStatement ')'                          // Case 57
		t := n.Type
		if t.Kind() == cc.Void {
			panic("internal error")
		}

		c.compoundStatement(&labels{-1, -1, -1}, n.CompoundStatement, stmtExprAddress)
		return 0, 0, nil, nil
	}
	panic(fmt.Errorf("internal error: %v", position(n)))
}

func (c *c) convert(n cc.Node, from, to cc.Type) {
	switch from.Kind() {
	case cc.Ptr:
		if t := from.Element(); t.Kind() == cc.Array {
			from = t.Element().Pointer()
		}
	case cc.Array:
		from = from.Element().Pointer()
	}
	c.emit(&ir.Convert{TypeID: c.typ(from).ID(), Result: c.typ(to).ID(), Position: position(n)})
}

func (c *c) constant(t cc.Type, v interface{}, n cc.Node) {
	if t.Kind() == cc.Void {
		return
	}

	switch x := v.(type) {
	case int8:
		c.emit(&ir.Const32{TypeID: idInt8, Value: int32(x), Position: position(n)})
		c.convert(n, c.ast.Model.CharType, t)
	case uint8:
		c.emit(&ir.Const32{TypeID: idUint8, Value: int32(x), Position: position(n)})
		c.convert(n, c.ast.Model.UCharType, t)
	case int16:
		c.emit(&ir.Const32{TypeID: idInt16, Value: int32(x), Position: position(n)})
		c.convert(n, c.ast.Model.ShortType, t)
	case uint16:
		c.emit(&ir.Const32{TypeID: idUint16, Value: int32(x), Position: position(n)})
		c.convert(n, c.ast.Model.UShortType, t)
	case int32:
		c.emit(&ir.Const32{TypeID: idInt32, Value: x, Position: position(n)})
		c.convert(n, c.ast.Model.IntType, t)
	case uint32:
		c.emit(&ir.Const32{TypeID: idUint32, Value: int32(x), Position: position(n)})
		c.convert(n, c.ast.Model.UIntType, t)
	case int64:
		c.emit(&ir.Const64{TypeID: idInt64, Value: x, Position: position(n)})
		c.convert(n, c.ast.Model.LongLongType, t)
	case uint64:
		c.emit(&ir.Const64{TypeID: idUint64, Value: int64(x), Position: position(n)})
		c.convert(n, c.ast.Model.ULongLongType, t)
	case float32:
		c.emit(&ir.Const32{TypeID: idFloat32, Value: int32(math.Float32bits(x)), Position: position(n)})
		c.convert(n, c.ast.Model.FloatType, t)
	case float64:
		c.emit(&ir.Const64{TypeID: idFloat64, Value: int64(math.Float64bits(x)), Position: position(n)})
		c.convert(n, c.ast.Model.DoubleType, t)
	case complex64:
		c.emit(&ir.Const64{TypeID: idComplex64, Value: int64(math.Float32bits(real(x)))<<32 | int64(math.Float32bits(imag(x))), Position: position(n)})
		c.convert(n, c.ast.Model.FloatComplexType, t)
	case complex128:
		c.emit(&ir.ConstC128{TypeID: idComplex128, Value: x, Position: position(n)})
		c.convert(n, c.ast.Model.DoubleComplexType, t)
	case cc.StringLitID:
		t0 := c.ast.Model.CharType.Pointer()
		c.emit(&ir.StringConst{Value: ir.StringID(x), TypeID: c.typ(t0).ID(), Position: position(n)})
		c.convert(n, t0, t)
	case cc.LongStringLitID:
		t0 := c.ast.Model.IntType.Pointer()
		c.emit(&ir.StringConst{Value: ir.StringID(x), TypeID: c.typ(t0).ID(), Position: position(n)})
		c.convert(n, t0, t)
	case uintptr:
		switch {
		case x == 0:
			c.emit(&ir.Nil{TypeID: c.typ(t).ID(), Position: position(n)})
		default:
			switch {
			case mathutil.BitLenUintptr(x) <= 32:
				c.emit(&ir.Const32{TypeID: idUint32, Value: int32(x), Position: position(n)})
				c.convert(n, c.ast.Model.UIntType, t)
			default:
				c.emit(&ir.Const64{TypeID: idUint64, Value: int64(x), Position: position(n)})
				c.convert(n, c.ast.Model.ULongLongType, t)
			}
		}
	default:
		TODO(position(n), fmt.Sprintf(" %T", x))
	}
}

func (c *c) binopType(n *cc.Expression) cc.Type {
	switch t := n.Expression.Type; t.Kind() {
	case cc.Array:
		return t.Element().Pointer()
	case cc.Function:
		return t.Pointer()
	default:
		n.Expression = c.normalize(n.Expression)
		n.Expression2 = c.normalize(n.Expression2)
		if a, b := n.Expression.Type, n.Expression2.Type; cc.IsArithmeticType(a) && cc.IsArithmeticType(b) {
			return c.ast.Model.BinOpType(a, b)
		}

		return t
	}
}

func (c *c) binop(ot cc.Type, n *cc.Expression, op ir.Operation) {
	t := c.binopType(n)
	//dbg("%s: ot %v, n.Type %v, e.Type %v, e2.Type %v, binopType %v", position(n), ot, n.Type, n.Expression.Type, n.Expression2.Type, t)
	c.expression(t, n.Expression)
	c.expression(t, n.Expression2)
	c.emit(op)
	if ot != nil {
		c.convert(n, t, ot)
	}
}

func (c *c) asopType(n *cc.Expression) cc.Type {
	a, b := n.Expression.Type, n.Expression2.Type
	switch {
	case a.Kind() == cc.Ptr:
		return a
	case cc.IsArithmeticType(a) && cc.IsArithmeticType(b):
		return c.ast.Model.BinOpType(a, b)
	default:
		panic(fmt.Errorf("internal error (%v, %v)", a, b))
	}
}

func (c *c) asop(n *cc.Expression, op ir.Operation, more ...cc.Type) cc.Type {
	evalType := c.asopType(n)
	bits, bitoff, bt, vt := c.addr(n.Expression)
	btid := c.typeID(bt)
	switch {
	case bits != 0:
		c.emit(&ir.Dup{TypeID: c.typ(bt.Pointer()).ID(), Position: position(n.Expression)})
		c.emit(&ir.Load{Bits: bits, BitOffset: bitoff, BitFieldType: btid, TypeID: c.typ(vt.Pointer()).ID(), Position: position(n)})
		c.convert(n, vt, evalType)
	default:
		pt := c.typ(n.Expression.Type.Pointer()).ID()
		c.emit(&ir.Dup{TypeID: pt, Position: position(n.Expression)})
		c.emit(&ir.Load{TypeID: pt, Position: position(n)})
		c.convert(n, n.Expression.Type, evalType)
	}
	switch {
	case n.Expression.Type.Kind() == cc.Ptr:
		c.expression(nil, n.Expression2)
	default:
		e2t := evalType
		if len(more) != 0 && more[0] != nil {
			e2t = more[0]
		}
		c.expression(e2t, n.Expression2)
	}
	c.emit(op)
	switch {
	case bits != 0:
		c.convert(n, evalType, bt)
		c.emit(&ir.Store{Bits: bits, BitOffset: bitoff, BitFieldType: btid, TypeID: c.typ(vt).ID(), Position: position(n)})
		return bt
	default:
		c.convert(n, evalType, n.Expression.Type)
		c.emit(&ir.Store{TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
		return n.Expression.Type
	}
}

func (c *c) shift(n *cc.Expression, op ir.Operation) {
	t := n.Expression.Type
	t = c.ast.Model.BinOpType(t, t)
	c.expression(t, n.Expression)
	t2 := n.Expression2.Type
	t2 = c.ast.Model.BinOpType(t2, t2)
	c.expression(t2, n.Expression2)
	c.convert(n.Expression2, t2, c.ast.Model.IntType)
	c.emit(op)
}

func (c *c) call(n *cc.Expression) cc.Type {
	fe := c.normalize(n.Expression)
	switch t := fe.Type; t.Kind() {
	case cc.Function:
		if r := t.Result(); r.Kind() != cc.Void {
			c.emit(&ir.AllocResult{TypeID: c.typ(r).ID(), TypeName: 0, Position: position(n)})
		}
		c.expression(t.Pointer(), n.Expression)
		args := c.arguments(n.Expression.Type, n.ArgumentExpressionListOpt)
		c.emit(&ir.CallFP{Arguments: args, TypeID: c.typ(t.Pointer()).ID(), Position: position(n)})
		return fe.Type.Result()
	case cc.Ptr:
		ft := t.Element()
		if ft.Kind() != cc.Function {
			panic("internal error")
		}

		if r := ft.Result(); r.Kind() != cc.Void {
			c.emit(&ir.AllocResult{TypeID: c.typ(r).ID(), TypeName: 0, Position: position(n)})
		}
		c.expression(t, n.Expression)
		args := c.arguments(ft, n.ArgumentExpressionListOpt)
		c.emit(&ir.CallFP{Arguments: args, TypeID: c.typ(t).ID(), Position: position(n)})
		return ft.Result()
	default:
		TODO(position(n), t.Kind())
	}
	panic("internal error")
}

func (c *c) condExpr(n *cc.Expression) {
	//case 44: // Expression '?' ExpressionList ':' Expression       // Case 44
	switch v := n.Expression.Value.(type) {
	case int32:
		if v != 0 {
			c.expressionList(nil, n.ExpressionList)
			break
		}

		c.expression(nil, n.Expression2)
	case nil:
		// eval expr
		// convert to bool if necessary
		// jz 0
		// eval exprlist
		// jmp 1
		// 0: eval expr2
		// 1:
		c.expression(nil, n.Expression)
		c.bool(n, n.Expression.Type)
		l0 := c.label()
		c.emit(&ir.Jz{Number: l0, Position: position(n.Expression)})
		c.expressionList(n.Type, n.ExpressionList)
		l1 := c.label()
		c.emit(&ir.Jmp{Number: l1, Position: position(n)})
		c.emit(&ir.Label{Number: l0, Position: position(n)})
		c.expression(n.Type, n.Expression2)
		c.emit(&ir.Label{Number: l1, Position: position(n)})
	default:
		TODO(position(n), fmt.Sprintf(" %T", v))
	}
}

func (c *c) expression(ot cc.Type, n *cc.Expression) cc.Type { // rvalue
	n = c.normalize(n)
	if v := n.Value; v != nil && n.Case != 58 && // "&&" IDENTIFIER
		n.Case != 7 { // '(' ExpressionList ')'                             // Case 7
		t := n.Type
		if ot != nil {
			t = ot
		}
		c.constant(t, v, n)
		return t
	}

	t := n.Type
	if t == nil {
		TODO(position(n))
	}

	switch t.Kind() {
	case cc.Function:
		c.addr(n)
		return t.Pointer()
	}

out:
	switch {
	case ot != nil && ot.Kind() != t.Kind():
		switch ot.Kind() {
		case cc.Void:
			if t := c.expression(nil, n); t.Kind() != cc.Void {
				c.emit(&ir.Drop{TypeID: c.typ(t).ID(), Position: position(n)})
			}
		default:
			switch {
			case cc.IsArithmeticType(ot) && cc.IsArithmeticType(t):
				c.expression(nil, n)
				c.convert(n, t, ot)
			case ot.Kind() == cc.Ptr && t.Kind() == cc.Array:
				break out
			case ot.Kind() == cc.Ptr && cc.IsIntType(t) || cc.IsIntType(ot) && t.Kind() == cc.Ptr:
				c.expression(nil, n)
				c.convert(n, t, ot)
			default:
				TODO(position(n), ot, ot.Kind(), t, t.Kind())
			}
		}
		return ot
	}

	if ot != nil && ot.Kind() == cc.Ptr && t.Kind() == cc.Ptr && ot.Element().Kind() != t.Element().Kind() {
		c.expression(nil, n)
		c.convert(n, t, ot)
		return ot
	}

	switch t.Kind() {
	case cc.Array:
		if n.Case != 45 { // Expression '=' Expression                          // Case 45
			c.addr(n)
			t2 := ot
			for t2 != nil && t2.Kind() == cc.Ptr {
				t2 = t2.Element()
			}
			if ot == nil || t2.Kind() == cc.Array {
				return t.Element().Pointer()
			}

			c.convert(n, t.Element().Pointer(), ot)
			return ot
		}
	}

	switch n.Case {
	case 0: // IDENTIFIER
		id := n.Token.Val
		b, s := n.IdentResolutionScope().Lookup2(cc.NSIdentifiers, id)
		d := b.Node.(*cc.DirectDeclarator).TopDeclarator()
		switch s.Scope() {
		case cc.ScopeBlock:
			switch vi, ok := c.f.variables[d]; {
			case !ok:
				t := d.Type
				if t.Kind() == cc.Function {
					c.addr(n)
					break
				}
				for s.Scope() == cc.ScopeBlock {
					s = s.Parent
				}
				dd, _ := c.dd(s, n, id)
				d := dd.TopDeclarator()
				n.Type = d.Type
				switch d.Linkage {
				case cc.External:
					c.emit(&ir.Global{Index: -1, Linkage: ir.ExternalLinkage, NameID: c.nm(d), TypeID: c.typ(t).ID(), TypeName: c.tnm(d), Position: position(n)})
				default:
					c.emit(&ir.Global{Index: -1, Linkage: ir.InternalLinkage, NameID: c.nm(d), TypeID: c.typ(t).ID(), TypeName: c.tnm(d), Position: position(n)})
				}
			case vi.static:
				t, _ := c.types.Type(vi.typ)
				switch {
				case t.Kind() == ir.Array:
					t = t.(*ir.ArrayType).Item.Pointer()
				}
				c.emit(&ir.Global{Index: -1, Linkage: ir.InternalLinkage, NameID: vi.staticName, TypeID: t.ID(), Position: position(n)})
			case vi.arg:
				c.emit(&ir.Argument{Index: vi.index, TypeID: c.f.arguments[vi.index], Position: position(n)})
			default:
				c.emit(&ir.Variable{Index: vi.index, TypeID: vi.typ, Position: position(n)})
			}
		case cc.ScopeFile:
			switch d.Linkage {
			case cc.External:
				c.emit(&ir.Global{Index: -1, Linkage: ir.ExternalLinkage, NameID: c.nm(d), TypeID: c.typ(t).ID(), TypeName: c.tnm(d), Position: position(n)})
			default:
				c.emit(&ir.Global{Index: -1, Linkage: ir.InternalLinkage, NameID: c.nm(d), TypeID: c.typ(t).ID(), TypeName: c.tnm(d), Position: position(n)})
			}
		default:
			panic("internal error")
		}
	case
		1, // CHARCONST                                          // Case 1
		2, // FLOATCONST                                         // Case 2
		3, // INTCONST                                           // Case 3
		4, // LONGCHARCONST                                      // Case 4
		5, // LONGSTRINGLITERAL                                  // Case 5
		6: // STRINGLITERAL                                      // Case 6

		panic("internal error")
	case 7: // '(' ExpressionList ')'                             // Case 7
		c.expressionList(n.Type, n.ExpressionList)
	case 8: // Expression '[' ExpressionList ']'                  // Case 8
		t := n.Expression.Type
		if t.Kind() == cc.Array {
			t = t.Element().Pointer()
		}
		c.expression(nil, n.Expression)
		c.expressionList(nil, n.ExpressionList)
		c.emit(&ir.Element{IndexType: c.typ(n.ExpressionList.Type).ID(), TypeID: c.typ(t).ID(), Position: position(n)})
	case 9: // Expression '(' ArgumentExpressionListOpt ')'       // Case 9
		return c.call(n)
	case 10: // Expression '.' IDENTIFIER                          // Case 10
		fi, bits, bitoff, _, vt := c.field(n, n.Expression.Type, n.Token2.Val)
		if e := c.normalize(n.Expression); e.Case == 9 { // Expression '(' ArgumentExpressionListOpt ')'       // Case 9
			c.call(e)
			c.emit(&ir.FieldValue{Index: fi, TypeID: c.typ(n.Expression.Type).ID(), Position: position(n.Token2)})
			break
		}

		c.addr(n.Expression)
		switch {
		case bits != 0:
			c.emit(&ir.Field{Bits: bits, BitOffset: bitoff, BitFieldType: c.typ(vt).ID(), Index: fi, TypeID: c.typ(n.Expression.Type.Pointer()).ID(), Position: position(n.Token2)})
			if vt.Kind() == cc.Bool && bits == 1 {
				c.emit(&ir.Neg{TypeID: c.typ(vt).ID(), Position: position(n)})
			}
		default:
			c.emit(&ir.Field{Index: fi, TypeID: c.typ(n.Expression.Type.Pointer()).ID(), Position: position(n.Token2)})
		}
	case 11: // Expression "->" IDENTIFIER                         // Case 11
		c.expression(nil, n.Expression)
		t := n.Expression.Type
		if t.Kind() == cc.Array {
			t = t.Element().Pointer()
		}
		fi, bits, bitoff, _, vt := c.field(n, n.Expression.Type.Element(), n.Token2.Val)
		switch {
		case bits != 0:
			c.emit(&ir.Field{Bits: bits, BitOffset: bitoff, BitFieldType: c.typ(vt).ID(), Index: fi, TypeID: c.typ(t).ID(), Position: position(n.Token2)})
			if vt.Kind() == cc.Bool && bits == 1 {
				c.emit(&ir.Neg{TypeID: c.typ(vt).ID(), Position: position(n)})
			}
		default:
			c.emit(&ir.Field{Index: fi, TypeID: c.typ(t).ID(), Position: position(n.Token2)})
		}
	case 12: // Expression "++"                                    // Case 12
		bits, bitoff, bft, vt := c.addr(n.Expression)
		if bits != 0 {
			c.emit(&ir.PostIncrement{Bits: bits, BitOffset: bitoff, BitFieldType: c.typ(bft).ID(), Delta: 1, TypeID: c.typ(vt).ID(), Position: position(n)})
			break
		}

		delta := 1
		if t := n.Expression.Type; t.Kind() == cc.Ptr {
			delta = t.Element().SizeOf()
		}
		c.emit(&ir.PostIncrement{Delta: delta, TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
	case 13: // Expression "--"                                    // Case 13
		bits, bitoff, bft, vt := c.addr(n.Expression)
		if bits != 0 {
			c.emit(&ir.PostIncrement{Bits: bits, BitOffset: bitoff, BitFieldType: c.typ(bft).ID(), Delta: -1, TypeID: c.typ(vt).ID(), Position: position(n)})
			break
		}

		delta := 1
		if t := n.Expression.Type; t.Kind() == cc.Ptr {
			delta = t.Element().SizeOf()
		}
		c.emit(&ir.PostIncrement{Delta: -delta, TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
	case 14: // '(' TypeName ')' '{' InitializerList CommaOpt '}'  // Case 14
		vi := c.compoundLiteral(n)
		t, _ := c.types.Type(vi.typ)
		switch {
		case t.Kind() == ir.Array:
			t = t.(*ir.ArrayType).Item.Pointer()
		}
		c.emit(&ir.Variable{Index: vi.index, TypeID: t.ID(), Position: position(n)})
	case 15: // "++" Expression                                    // Case 15
		bits, bitoff, bft, vt := c.addr(n.Expression)
		if bits != 0 {
			c.emit(&ir.PreIncrement{Bits: bits, BitOffset: bitoff, BitFieldType: c.typ(bft).ID(), Delta: 1, TypeID: c.typ(vt).ID(), Position: position(n)})
			break
		}

		delta := 1
		if t := n.Expression.Type; t.Kind() == cc.Ptr {
			delta = t.Element().SizeOf()
		}
		c.emit(&ir.PreIncrement{Delta: delta, TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
	case 16: // "--" Expression                                    // Case 16
		bits, bitoff, bft, vt := c.addr(n.Expression)
		if bits != 0 {
			c.emit(&ir.PreIncrement{Bits: bits, BitOffset: bitoff, BitFieldType: c.typ(bft).ID(), Delta: -1, TypeID: c.typ(vt).ID(), Position: position(n)})
			break
		}

		delta := 1
		if t := n.Expression.Type; t.Kind() == cc.Ptr {
			delta = t.Element().SizeOf()
		}
		c.emit(&ir.PreIncrement{Delta: -delta, TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
	case 17: // '&' Expression                                     // Case 17
		c.addr(n.Expression)
	case 18: // '*' Expression                                     // Case 18
		c.expression(n.Type.Pointer(), n.Expression)
		c.emit(&ir.Load{TypeID: c.typ(n.Type.Pointer()).ID(), Position: position(n)})
	case 19: // '+' Expression                                     // Case 19
		TODO(position(n))
	case 20: // '-' Expression                                     // Case 20
		c.expression(nil, n.Expression)
		c.emit(&ir.Neg{TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
	case 21: // '~' Expression                                     // Case 21
		c.expression(nil, n.Expression)
		c.emit(&ir.Cpl{TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
	case 22: // '!' Expression                                     // Case 22
		c.expression(nil, n.Expression)
		c.bool(n, n.Expression.Type)
		c.emit(&ir.Not{Position: position(n)})
	case 23: // "sizeof" Expression                                // Case 23
		if n.Expression.Type.Kind() == cc.Array {
			TODO(position(n))
			break
		}

		TODO(position(n))
	case 24: // "sizeof" '(' TypeName ')'                          // Case 24
		TODO(position(n))
	case 25: // '(' TypeName ')' Expression                        // Case 25
		c.expression(nil, n.Expression)
		if n.Expression.Type.Kind() == cc.Function && n.TypeName.Type.Kind() == cc.Ptr {
			c.convert(n, c.ast.Model.VoidType.Pointer(), n.TypeName.Type)
			break
		}

		switch {
		case n.TypeName.Type.Kind() == cc.Void:
			c.emit(&ir.Drop{TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
		default:
			c.convert(n, n.Expression.Type, n.TypeName.Type)
		}
	case 26: // Expression '*' Expression                          // Case 26
		c.binop(ot, n, &ir.Mul{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 27: // Expression '/' Expression                          // Case 27
		c.binop(ot, n, &ir.Div{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 28: // Expression '%' Expression                          // Case 28
		c.binop(ot, n, &ir.Rem{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 29: // Expression '+' Expression                          // Case 29
		switch n.Expression.Type.Kind() {
		case cc.Ptr, cc.Array:
			t := c.expression(nil, n.Expression)
			c.expression(t, n.Expression2)
			tid := c.typ(t).ID()
			if sz := t.Element().SizeOf(); sz > 1 {
				c.emit(&ir.Const32{TypeID: tid, Value: int32(sz), Position: position(n)})
				c.emit(&ir.Mul{TypeID: tid, Position: position(n)})
			}
			c.emit(&ir.Add{TypeID: tid, Position: position(n.Token)})
			return t
		}

		switch n.Expression2.Type.Kind() {
		case cc.Ptr, cc.Array:
			t := n.Expression2.Type
			c.expression(t, n.Expression)
			tid := c.typ(t).ID()
			if sz := t.Element().SizeOf(); sz > 1 {
				c.emit(&ir.Const32{TypeID: tid, Value: int32(sz), Position: position(n)})
				c.emit(&ir.Mul{TypeID: tid, Position: position(n)})
			}
			c.expression(nil, n.Expression2)
			c.emit(&ir.Add{TypeID: tid, Position: position(n.Token)})
			return t
		}

		c.binop(ot, n, &ir.Add{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 30: // Expression '-' Expression                          // Case 30
		switch n.Expression.Type.Kind() {
		case cc.Ptr, cc.Array:
			t := n.Expression.Type
			if t.Kind() == cc.Array {
				t = t.Element().Pointer()
			}
			switch n.Expression2.Type.Kind() {
			case cc.Ptr, cc.Array:
				c.expression(t, n.Expression)
				c.expression(t, n.Expression2)
				c.emit(&ir.PtrDiff{PtrType: c.typ(t).ID(), TypeID: c.typ(n.Type).ID(), Position: position(n)})
			default:
				c.expression(nil, n.Expression)
				c.expression(t, n.Expression2)
				tid := c.typ(t).ID()
				if sz := t.Element().SizeOf(); sz > 1 {
					c.emit(&ir.Const32{TypeID: tid, Value: int32(sz), Position: position(n)})
					c.emit(&ir.Mul{TypeID: tid, Position: position(n)})
				}
				c.emit(&ir.Sub{TypeID: tid, Position: position(n.Token)})
			}
			return t
		}

		switch n.Expression2.Type.Kind() {
		case cc.Ptr, cc.Array:
			TODO(position(n))
			return n.Type
		}

		//TODO if n.Expression.Type.Kind() == cc.Ptr || n.Expression2.Type.Kind() == cc.Ptr {
		//TODO 	c.expression(nil, n.Expression)
		//TODO 	c.expression(nil, n.Expression2)
		//TODO 	c.emit(&ir.PtrDiff{TypeID: c.typ(n.Type).ID(), Position: position(n)})
		//TODO 	break
		//TODO }

		c.binop(ot, n, &ir.Sub{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 31: // Expression "<<" Expression                         // Case 31
		c.shift(n, &ir.Lsh{TypeID: c.typ(n.Type).ID(), Position: position(n)})
	case 32: // Expression ">>" Expression                         // Case 32
		c.shift(n, &ir.Rsh{TypeID: c.typ(n.Type).ID(), Position: position(n)})
	case 33: // Expression '<' Expression                          // Case 33
		c.binop(nil, n, &ir.Lt{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 34: // Expression '>' Expression                          // Case 34
		c.binop(nil, n, &ir.Gt{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 35: // Expression "<=" Expression                         // Case 35
		c.binop(nil, n, &ir.Leq{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 36: // Expression ">=" Expression                         // Case 36
		c.binop(nil, n, &ir.Geq{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 37: // Expression "==" Expression                         // Case 37
		c.binop(nil, n, &ir.Eq{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 38: // Expression "!=" Expression                         // Case 38
		c.binop(nil, n, &ir.Neq{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 39: // Expression '&' Expression                          // Case 39
		c.binop(ot, n, &ir.And{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 40: // Expression '^' Expression                          // Case 40
		c.binop(ot, n, &ir.Xor{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 41: // Expression '|' Expression                          // Case 41
		c.binop(ot, n, &ir.Or{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 42: // Expression "&&" Expression                         // Case 42
		// push 0
		// eval expr
		// convert to bool if necessary
		// jz A
		// eval expr2
		// convert to bool if necessary
		// jz A
		// drop
		// push 1
		// A:
		c.emit(&ir.Const32{TypeID: idInt32, Position: position(n)})
		c.expression(nil, n.Expression)
		c.bool(n, n.Expression.Type)
		a := c.label()
		c.emit(&ir.Jz{Number: a, Position: position(n.Expression)})
		c.expression(nil, n.Expression2)
		c.bool(n, n.Expression2.Type)
		c.emit(&ir.Jz{Number: a, Position: position(n.Expression)})
		c.emit(&ir.Drop{TypeID: idInt32, Position: position(n)})
		c.emit(&ir.Const32{TypeID: idInt32, Value: 1, Position: position(n)})
		c.emit(&ir.Label{Number: a, Position: position(n)})
	case 43: // Expression "||" Expression                         // Case 43
		// push 1
		// eval expr
		// convert to bool if necessary
		// jnz A
		// eval expr2
		// convert to bool if necessary
		// jnz A
		// drop
		// push 0
		// A:
		c.emit(&ir.Const32{TypeID: idInt32, Value: 1, Position: position(n)})
		c.expression(nil, n.Expression)
		c.bool(n, n.Expression.Type)
		a := c.label()
		c.emit(&ir.Jnz{Number: a, Position: position(n.Expression)})
		c.expression(nil, n.Expression2)
		c.bool(n, n.Expression2.Type)
		c.emit(&ir.Jnz{Number: a, Position: position(n.Expression)})
		c.emit(&ir.Drop{TypeID: idInt32, Position: position(n)})
		c.emit(&ir.Const32{TypeID: idInt32, Position: position(n)})
		c.emit(&ir.Label{Number: a, Position: position(n)})
	case 44: // Expression '?' ExpressionList ':' Expression       // Case 44
		c.condExpr(n)
	case 45: // Expression '=' Expression                          // Case 45
		bits, bitoff, bfType, vt := c.addr(n.Expression)
		if bits != 0 {
			c.expression(bfType, n.Expression2)
			c.emit(&ir.Store{Bits: bits, BitOffset: bitoff, BitFieldType: c.typ(bfType).ID(), TypeID: c.typ(vt).ID(), Position: position(n)})
			return bfType
		}

		c.expression(n.Expression.Type, n.Expression2)
		switch t := n.Expression.Type; t.Kind() {
		case cc.Array:
			c.emit(&ir.Copy{TypeID: c.typ(n.Expression2.Type).ID(), Position: position(n)})
			return t.Element().Pointer()
		default:
			c.emit(&ir.Store{TypeID: c.typ(n.Expression.Type).ID(), Position: position(n.Token)})
		}
	case 46: // Expression "*=" Expression                         // Case 46
		return c.asop(n, &ir.Mul{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)})
	case 47: // Expression "/=" Expression                         // Case 47
		return c.asop(n, &ir.Div{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)})
	case 48: // Expression "%=" Expression                         // Case 48
		return c.asop(n, &ir.Rem{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)})
	case 49: // Expression "+=" Expression                         // Case 49
		if t := n.Expression.Type; t.Kind() == cc.Ptr {
			return c.asop(n, &ir.Element{Address: true, TypeID: c.typ(t).ID(), IndexType: c.typ(n.Expression2.Type).ID(), Position: position(n)})
		}

		return c.asop(n, &ir.Add{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)})
	case 50: // Expression "-=" Expression                         // Case 50
		if n.Expression.Type.Kind() == cc.Ptr {
			return c.asop(n, &ir.Element{Address: true, Neg: true, TypeID: c.typ(t).ID(), IndexType: c.typ(n.Expression2.Type).ID(), Position: position(n)})
		}

		return c.asop(n, &ir.Sub{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)})
	case 51: // Expression "<<=" Expression                        // Case 51
		return c.asop(n, &ir.Lsh{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)}, c.ast.Model.IntType)
	case 52: // Expression ">>=" Expression                        // Case 52
		return c.asop(n, &ir.Rsh{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)}, c.ast.Model.IntType)
	case 53: // Expression "&=" Expression                         // Case 53
		return c.asop(n, &ir.And{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)})
	case 54: // Expression "^=" Expression                         // Case 54
		return c.asop(n, &ir.Xor{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)})
	case 55: // Expression "|=" Expression                         // Case 55
		return c.asop(n, &ir.Or{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)})
	case 56: // "_Alignof" '(' TypeName ')'                        // Case 56
		TODO(position(n))
	case 57: // '(' CompoundStatement ')'                          // Case 57
		stmtExpr := 0
		if n.Type.Kind() != cc.Void {
			stmtExpr = stmtExprValue
		}
		c.compoundStatement(&labels{-1, -1, -1}, n.CompoundStatement, stmtExpr)
	default:
		panic(fmt.Errorf("%s: internal error: Expression.Case %v", position(n), n.Case))
	}

	return t
}

func (c *c) expressionList(ot cc.Type, n *cc.ExpressionList) {
	t := c.ast.Model.VoidType
	for l := n; l != nil; l = l.ExpressionList {
		if l.ExpressionList == nil {
			t = ot
		}
		c.expression(t, l.Expression)
	}
}

func (c *c) expressionListOpt(ot cc.Type, n *cc.ExpressionListOpt, stmtExpr int) {
	if n == nil {
		return
	}

	switch stmtExpr {
	case stmtExprValue:
		ot = n.ExpressionList.Type
	case stmtExprAddress:
		t := c.ast.Model.VoidType
		for l := n.ExpressionList; l != nil; l = l.ExpressionList {
			if l.ExpressionList == nil {
				c.addr(l.Expression)
				return
			}

			c.expression(t, l.Expression)
		}
		return
	}
	c.expressionList(ot, n.ExpressionList)
}

func (c *c) expressionStatement(n *cc.ExpressionStatement, stmtExpr int) {
	c.expressionListOpt(c.ast.Model.VoidType, n.ExpressionListOpt, stmtExpr)
}

func (c *c) jumpStatement(labels *labels, n *cc.JumpStatement) {
	switch n.Case {
	case 0: // "goto" IDENTIFIER ';'
		c.emit(&ir.Jmp{NameID: ir.NameID(n.Token2.Val), Position: position(n)})
	case 1: // "continue" ';'                  // Case 1
		c.emit(&ir.Jmp{Number: labels.continueLabel, Position: position(n)})
	case 2: // "break" ';'                     // Case 2
		label := labels.breakLabel
		if label < 0 {
			label = c.label()
			labels.breakLabel = label
		}
		c.emit(&ir.Jmp{Number: label, Position: position(n)})
	case 3: // "return" ExpressionListOpt ';'  // Case 3
		if o := n.ExpressionListOpt; o != nil {
			switch r := c.f.result; r {
			case 0:
				c.expressionList(c.ast.Model.VoidType, o.ExpressionList)
			default:
				c.emit(&ir.Result{Address: true, TypeID: c.types.MustType(r).Pointer().ID(), Position: position(n)})
				l := o.ExpressionList
				c.expressionList(c.f.cResult, l)
				c.emit(&ir.Store{TypeID: r, Position: position(n)})
				c.emit(&ir.Drop{TypeID: r, Position: position(n)})
			}
		}
		c.emit(&ir.Return{Position: position(n)})
	case 4: // "goto" Expression ';'           // Case 4
		switch e := n.Expression; e.Case {
		case 18: // '*' Expression                                     // Case 18
			c.expression(nil, e.Expression)
		default:
			TODO(position(n), e.Case)
		}
		c.emit(&ir.JmpP{Position: position(n)})
	default:
		panic("internal error")
	}
}

func (c *c) label() int {
	r := c.f.label
	c.f.label++
	return r
}

func (c *c) forStmt(n *cc.IterationStatement, labels *labels, init, cond, iter *cc.ExpressionListOpt) {
	switch {
	case n.Declaration != nil:
		c.declaration(n.Declaration, true)
	case init != nil:
		c.expressionListOpt(c.ast.Model.VoidType, init, 0)
	}
	test := c.label()
	cont := c.label()
	cl := labels.setContinue(cont)
	c.emit(&ir.Label{Number: test, Position: position(n)})
	end := c.label()
	if o := cond; o != nil {
		el := o.ExpressionList
		c.expressionList(el.Type, el)
		end = c.label()
		c.bool(n, el.Type)
		c.emit(&ir.Jz{Number: end, Position: position(n)})
	}
	breakLabel := labels.setBreak(end)
	loop := c.f.loop
	c.f.loop = true
	c.statement(labels, n.Statement, 0)
	c.f.loop = loop
	labels.setBreak(breakLabel)
	labels.setContinue(cl)
	c.emit(&ir.Label{Number: cont, Position: position(n)})
	c.expressionListOpt(c.ast.Model.VoidType, iter, 0)
	c.emit(&ir.Jmp{Number: test, Position: position(n)})
	c.emit(&ir.Label{Number: end, Position: position(n)})
}

func (c *c) iterationStatement(labels *labels, n *cc.IterationStatement) {
	switch n.Case {
	case 0: // "while" '(' ExpressionList ')' Statement
		begin := c.label()
		cl := labels.setContinue(begin)
		end := c.label()
		c.emit(&ir.Label{Number: begin, Position: position(n)})
		el := n.ExpressionList
		c.expressionList(el.Type, el)
		c.bool(n, el.Type)
		c.emit(&ir.Jz{Number: end, Position: position(n)})
		breakLabel := labels.setBreak(end)
		loop := c.f.loop
		c.f.loop = true
		c.statement(labels, n.Statement, 0)
		c.f.loop = loop
		labels.setBreak(breakLabel)
		labels.setContinue(cl)
		c.emit(&ir.Jmp{Number: begin, Position: position(n)})
		c.emit(&ir.Label{Number: end, Position: position(n)})
	case 1: // "do" Statement "while" '(' ExpressionList ')' ';'                                      // Case 1
		begin := c.label()
		c.emit(&ir.Label{Number: begin, Position: position(n)})
		breakLabel := labels.setBreak(-1)
		cl := labels.setContinue(begin)
		loop := c.f.loop
		c.f.loop = true
		c.statement(labels, n.Statement, 0)
		c.f.loop = loop
		el := n.ExpressionList
		c.expressionList(el.Type, el)
		c.bool(n, el.Type)
		c.emit(&ir.Jnz{Number: begin, Position: position(n.ExpressionList)})
		if e := labels.breakLabel; e >= 0 {
			c.emit(&ir.Label{Number: e, Position: position(n)})
		}
		labels.setBreak(breakLabel)
		labels.setContinue(cl)
	case 2: // "for" '(' ExpressionListOpt ';' ExpressionListOpt ';' ExpressionListOpt ')' Statement  // Case 2
		c.forStmt(n, labels, n.ExpressionListOpt, n.ExpressionListOpt2, n.ExpressionListOpt3)
	case 3: // "for" '(' Declaration ExpressionListOpt ';' ExpressionListOpt ')' Statement            // Case 3
		c.forStmt(n, labels, nil, n.ExpressionListOpt, n.ExpressionListOpt2)
	default:
		panic("internal error")
	}
}

func (c *c) switchStatement(n *cc.SelectionStatement) {
	// "switch" '(' ExpressionList ')' Statement               // Case 2
	t := n.ExpressionList.Type
	t = c.ast.Model.BinOpType(t, t)
	c.expressionList(t, n.ExpressionList)
	firstCase := -1
	defaultCase := -1
	var cases []*cc.ConstantExpression
	var f func(*cc.Statement)
	f = func(n *cc.Statement) {
		switch n.Case {
		case 0: // LabeledStatement
			switch n := n.LabeledStatement; n.Case {
			case 0: // IDENTIFIER ':' Statement
				f(n.Statement)
			case 1: // "case" ConstantExpression ':' Statement  // Case 1
				label := c.label()
				if firstCase < 0 {
					firstCase = label
				}
				cases = append(cases, n.ConstantExpression)
				f(n.Statement)
			case 2: // "default" ':' Statement                  // Case 2
				label := c.label()
				if defaultCase >= 0 {
					panic("internal error")
				}

				defaultCase = label
				if firstCase < 0 {
					firstCase = label
				}
				cases = append(cases, n.ConstantExpression)
				f(n.Statement)
			default:
				panic("internal error")
			}
		case 1: // CompoundStatement    // Case 1
			o := n.CompoundStatement.BlockItemListOpt
			if o == nil {
				break
			}

			for l := o.BlockItemList; l != nil; l = l.BlockItemList {
				switch n := l.BlockItem; n.Case {
				case 0: // Declaration
					// nop
				case 1: // Statement    // Case 1
					f(n.Statement)
				default:
					panic("internal error")
				}
			}
		case 2: // ExpressionStatement  // Case 2
			// nop
		case 3: // SelectionStatement   // Case 3
			switch n := n.SelectionStatement; n.Case {
			case 0: // "if" '(' ExpressionList ')' Statement
				f(n.Statement)
			case 1: // "if" '(' ExpressionList ')' Statement "else" Statement  // Case 1
				f(n.Statement)
			case 2: // "switch" '(' ExpressionList ')' Statement               // Case 2
				// nop
			default:
				panic("internal error")
			}
		case 4: // IterationStatement   // Case 4
			switch n := n.IterationStatement; n.Case {
			case
				0, // "while" '(' ExpressionList ')' Statement
				1, // "do" Statement "while" '(' ExpressionList ')' ';'                                      // Case 1
				2, // "for" '(' ExpressionListOpt ';' ExpressionListOpt ';' ExpressionListOpt ')' Statement  // Case 2
				3: // "for" '(' Declaration ExpressionListOpt ';' ExpressionListOpt ')' Statement            // Case 3
				f(n.Statement)
			default:
				panic("internal error")
			}
		case 5: // JumpStatement        // Case 5
			// nop
		case 9: // AssemblerStatement   // Case 6
			TODO(position(n))
		default:
			panic("internal error")
		}
	}
	f(n.Statement)
	if len(cases) == 0 {
		c.emit(&ir.Drop{TypeID: c.typ(t).ID(), Position: position(n.ExpressionList)})
		return
	}

	typ := c.typ(t).ID()
	for i, v := range cases {
		if v == nil { // default:
			continue
		}

		c.emit(&ir.Dup{TypeID: typ, Position: position(n.ExpressionList)})
		c.constant(t, v.Value, v)
		c.emit(&ir.Eq{TypeID: typ, Position: position(n.ExpressionList)})
		drop := c.label()
		c.emit(&ir.Jz{Number: drop, Position: position(n.ExpressionList)})
		c.emit(&ir.Drop{TypeID: typ, Position: position(n.ExpressionList)})
		c.emit(&ir.Jmp{Number: firstCase + i, Position: position(n.ExpressionList)})
		c.emit(&ir.Label{Number: drop, Position: position(n.ExpressionList)})

	}
	c.emit(&ir.Drop{TypeID: typ, Position: position(n.ExpressionList)})
	labels := labels{
		breakLabel:    -1,
		caseLabel:     firstCase,
		continueLabel: -1,
	}
	switch {
	case defaultCase < 0:
		labels.breakLabel = c.label()
		c.emit(&ir.Jmp{Number: labels.breakLabel, Position: position(n)})
	default:
		c.emit(&ir.Jmp{Number: defaultCase, Position: position(n)})
	}
	c.statement(&labels, n.Statement, 0)
	if labels.breakLabel >= 0 {
		c.emit(&ir.Label{Number: labels.breakLabel, Position: position(n.ExpressionList)})
	}
}

func (c *c) bool(n cc.Node, from cc.Type) {
	switch from.Kind() {
	case cc.Ptr:
		if t := from.Element(); t.Kind() == cc.Array {
			from = t.Element().Pointer()
		}
	case cc.Array:
		from = from.Element().Pointer()
	}
	if from.Kind() != cc.Int {
		c.emit(&ir.Bool{TypeID: c.typ(from).ID(), Position: position(n)})
	}
}

func (c *c) selectionStatement(labels *labels, n *cc.SelectionStatement) {
	switch n.Case {
	case 0: // "if" '(' ExpressionList ')' Statement
		// expr; jz 1; stmt; 1:
		c.expressionList(nil, n.ExpressionList)
		c.bool(n, n.ExpressionList.Type)
		l1 := c.label()
		c.emit(&ir.Jz{Number: l1, Position: position(n)})
		c.statement(labels, n.Statement, 0)
		c.emit(&ir.Label{Number: l1, Position: position(n)})
	case 1: // "if" '(' ExpressionList ')' Statement "else" Statement  // Case 1
		// expr; jz 1; stmt; jmp 2; 1: stmt2; 2:
		c.expressionList(nil, n.ExpressionList)
		c.bool(n, n.ExpressionList.Type)
		l1 := c.label()
		c.emit(&ir.Jz{Number: l1, Position: position(n)})
		c.statement(labels, n.Statement, 0)
		l2 := c.label()
		c.emit(&ir.Jmp{Number: l2, Position: position(n)})
		c.emit(&ir.Label{Number: l1, Position: position(n)})
		c.statement(labels, n.Statement2, 0)
		c.emit(&ir.Label{Number: l2, Position: position(n)})
	case 2: // "switch" '(' ExpressionList ')' Statement               // Case 2
		c.switchStatement(n)
	default:
		panic("internal error")
	}
}

func (c *c) labeledStatement(labels *labels, n *cc.LabeledStatement) {
	switch n.Case {
	case 0: // IDENTIFIER ':' Statement
		c.emit(&ir.Label{NameID: ir.NameID(n.Token.Val), Position: position(n)})
	case
		1, // "case" ConstantExpression ':' Statement  // Case 1
		2: // "default" ':' Statement                  // Case 2
		c.emit(&ir.Label{Number: labels.caseLabel, Position: position(n)})
		labels.caseLabel++
	default:
		panic("internal error")
	}
	c.statement(labels, n.Statement, 0)
}

func (c *c) assemblerStatement(n *cc.AssemblerStatement) {
	switch n.Case {
	case 0: // BasicAssemblerStatement
		for l := n.BasicAssemblerStatement.AssemblerInstructions; l != nil; l = l.AssemblerInstructions {
			if v := l.Token.Val; v != idEmptyString {
				panic(fmt.Errorf("%s: assembler instructions not supported: %s", position(l.Token), dict.S(v)))
			}
		}
	default:
		panic(fmt.Errorf("%s: assembler instructions not supported", position(n)))
	}
}

func (c *c) statement(labels *labels, n *cc.Statement, stmtExpr int) {
	switch n.Case {
	case 0: // LabeledStatement
		c.labeledStatement(labels, n.LabeledStatement)
	case 1: // CompoundStatement    // Case 1
		c.compoundStatement(labels, n.CompoundStatement, 0)
	case 2: // ExpressionStatement  // Case 2
		c.expressionStatement(n.ExpressionStatement, stmtExpr)
	case 3: // SelectionStatement   // Case 3
		c.selectionStatement(labels, n.SelectionStatement)
	case 4: // IterationStatement   // Case 4
		c.iterationStatement(labels, n.IterationStatement)
	case 5: // JumpStatement        // Case 5
		c.jumpStatement(labels, n.JumpStatement)
	case 6: // AssemblerStatement   // Case 6
		c.assemblerStatement(n.AssemblerStatement)
	default:
		panic("internal error")
	}
}

func (c *c) blockItem(labels *labels, n *cc.BlockItem, stmtExpr int, alwaysEvalInitializers bool) {
	switch n.Case {
	case 0: // Declaration
		c.declaration(n.Declaration, alwaysEvalInitializers)
	case 1: // Statement    // Case 1
		c.statement(labels, n.Statement, stmtExpr)
	default:
		panic("internal error")
	}
}

func (c *c) compoundStatement(labels *labels, n *cc.CompoundStatement, stmtExpr int) {
	v := stmtExpr == stmtExprValue || stmtExpr == stmtExprAddress
	c.f.blockLevel++
	c.emit(&ir.BeginScope{Position: position(n), Value: v})
	if o := n.BlockItemListOpt; o != nil {
		for l := o.BlockItemList; l != nil; l = l.BlockItemList {
			se := 0
			if l.BlockItemList == nil {
				se = stmtExpr
			}
			c.blockItem(labels, l.BlockItem, se, c.f.loop)
		}
	}
	c.f.blockLevel--
	if c.f.blockLevel == 0 {
		b := c.f.f.Body
		if _, ok := b[len(b)-1].(*ir.Return); !ok {
			c.emit(&ir.Return{Position: position(n.Token2)})
		}
	}
	c.emit(&ir.EndScope{Position: position(n.Token2), Value: v})
}

func (c *c) functionBody(n *cc.FunctionBody) {
	if c.f.f.NameID == idMain && c.f.f.Linkage == ir.ExternalLinkage {
		c.emit(&ir.Result{Address: true, TypeID: idPInt32, Position: position(n)})
		c.emit(&ir.Const32{TypeID: idInt32, Position: position(n)})
		c.emit(&ir.Store{TypeID: idInt32, Position: position(n)})
		c.emit(&ir.Drop{TypeID: idInt32, Position: position(n)})
	}
	switch n.Case {
	case 0: // CompoundStatement
		c.compoundStatement(&labels{-1, -1, -1}, n.CompoundStatement, 0)
	case 1: // AssemblerStatement ';'  // Case 1
		TODO(position(n))
	default:
		panic("internal error")
	}
}

func (c *c) fnArgNames(d *cc.Declarator) []ir.NameID {
	p, _ := d.Type.Parameters()
	var args []ir.NameID
	if len(p) != 0 && p[0].Name != 0 {
		args = make([]ir.NameID, len(p))
		for i, v := range p {
			args[i] = ir.NameID(v.Name)
		}
	}
	return args
}

func (c *c) functionDefinition(n *cc.FunctionDefinition) {
	switch n.Case {
	case
		0, // DeclarationSpecifiers Declarator DeclarationListOpt FunctionBody
		1: // Declarator DeclarationListOpt FunctionBody                        // Case 1

		d := n.Declarator
		t := c.typ(d.Type)
		nm := c.nm(d)
		ln := c.linkage(d.Linkage)
		if ln == ir.ExternalLinkage && nm == idMain && len(t.(*ir.FunctionType).Results) == 0 {
			t = c.types.MustType(ir.TypeID(dict.SID(string(dict.S(int(t.ID()))) + "int32")))
		}
		c.newFData(d.Type, ir.NewFunctionDefinition(position(n), nm, c.tnm(d), t.ID(), ln, c.fnArgNames(d), nil))
		c.f.index = len(c.out)
		c.out = append(c.out, c.f.f)
		c.functionBody(n.FunctionBody)
		c.f = fdata{}
	default:
		panic("internal error")
	}
}

func (c *c) externalDeclaration(n *cc.ExternalDeclaration) {
	switch n.Case {
	case 0: // FunctionDefinition
		c.functionDefinition(n.FunctionDefinition)
	case 1: // Declaration                  // Case 1
		c.declaration(n.Declaration, false)
	case 2: // BasicAssemblerStatement ';'  // Case 2
		TODO(position(n))
	case 3: // ';'                          // Case 3
		// nop
	default:
		panic("internal error")
	}
}

func (c *c) gen() {
	for l := c.ast; l != nil; l = l.TranslationUnit {
		c.externalDeclaration(l.ExternalDeclaration)
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
				err = fmt.Errorf("ccir.New: PANIC: %v", x)
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
