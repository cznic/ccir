// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Package ccir translates cc[0] ASTs to intermediate representation. (Work In Progress)
//
//  [0]: https://github.com/cznic/cc
package ccir

import (
	"bytes"
	"fmt"
	"go/token"
	"math"
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
	label      int
	result     ir.TypeID
	static     int
	variable   int
	variables  map[*cc.Declarator]varInfo
}

type c struct {
	ast    *cc.TranslationUnit
	ctypes map[cc.Type]ir.Type
	f      fdata
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
		dst.Close()
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
	case cc.None:
		return ir.Linkage(-1)
	default:
		panic("internal error")
	}
}

func (c *c) addressInitializer(n *cc.Expression) ir.Value {
	switch n.Case {
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

func (c *c) initializerList(n *cc.InitializerList) ir.Value {
	r := &ir.CompositeValue{}
	for ; n != nil; n = n.InitializerList {
		v, _ := c.initializer(n.Initializer)
		if v == nil {
			return nil
		}

		if o := n.DesignationOpt; o != nil {
			TODO(position(n))
		}

		r.Values = append(r.Values, v)
	}
	return r
}

func (c *c) initializer(n *cc.Initializer) (ir.Value, *cc.Expression) {
	if n == nil {
		return nil, nil
	}

	switch n.Case {
	case 0: // Expression
		switch x := n.Expression.Value.(type) {
		case nil:
			if v := c.addressInitializer(n.Expression); v != nil {
				return v, nil
			}

			return nil, n.Expression
		case cc.StringLitID:
			return &ir.StringValue{StringID: ir.StringID(x)}, nil
		case int32:
			return &ir.Int32Value{Value: x}, nil
		case float64:
			return &ir.Float64Value{Value: x}, nil
		default:
			TODO(position(n), fmt.Sprintf("%T", x))
		}
	case 1: // '{' InitializerList CommaOpt '}'  // Case 1
		if v := c.initializerList(n.InitializerList); v != nil {
			return v, nil
		}

		return nil, n.Expression
	}
	panic("internal error")
}

func (c *c) initDeclarator(n *cc.InitDeclarator) (p token.Position, nm, tnm ir.NameID, typ ir.TypeID, l ir.Linkage, v ir.Value, x *cc.Expression) {
	d := n.Declarator
	v, x = c.initializer(n.Initializer)
	return position(n), c.nm(d), c.tnm(d), c.typ(d.Type).ID(), c.linkage(d.Linkage), v, x
}

func (c *c) declaration(n *cc.Declaration) {
	switch n.Case {
	case 0: // DeclarationSpecifiers InitDeclaratorListOpt ';'
		if n.DeclarationSpecifiers.IsTypedef() {
			return
		}

		if o := n.InitDeclaratorListOpt; o != nil {
			for l := o.InitDeclaratorList; l != nil; l = l.InitDeclaratorList {
				d := l.InitDeclarator.Declarator
				id, _ := d.Identifier()
				isFunc := d.Type.Kind() == cc.Function
				isBuiltin := bytes.HasPrefix(dict.S(id), dict.S(idBuiltinPrefix))
				if isFunc && isBuiltin {
					f := ir.NewFunctionDefinition(position(d), c.nm(d), c.tnm(d), c.typ(d.Type).ID(), c.linkage(d.Linkage), c.fnArgNames(d), nil)
					f.Body = []ir.Operation{&ir.Panic{Position: position(d)}}
					c.out = append(c.out, f)
					continue
				}

				if d.Type.Specifier().IsExtern() || isFunc {
					continue
				}

				switch p, nm, tnm, typ, ln, v, expr := c.initDeclarator(l.InitDeclarator); {
				case ln < 0: // linkage none
					switch {
					case d.RawSpecifier().IsStatic():
						var b buffer.Bytes
						// func\x00varname\x00index
						b.Write(dict.S(int(c.f.f.NameID)))
						b.WriteByte(0)
						b.Write(dict.S(int(nm)))
						b.WriteByte(0)
						fmt.Fprintf(&b, "%v", c.f.static)
						snm := ir.NameID(dict.ID(b.Bytes()))
						b.Close()
						c.f.variables[d] = varInfo{index: c.f.static, static: true, typ: typ, staticName: snm}
						c.out = append(c.out, ir.NewDataDefinition(p, snm, tnm, typ, ir.InternalLinkage, v))
						c.f.static++
						if expr != nil {
							TODO(position(expr))
						}
					default:
						c.f.variables[d] = varInfo{index: c.f.variable, typ: typ}
						c.emit(&ir.VariableDeclaration{Index: c.f.variable, NameID: nm, TypeID: typ, TypeName: tnm, Value: v, Position: position(d)})
						if expr != nil {
							pt := c.types.MustType(typ).Pointer().ID()
							c.emit(&ir.Variable{Address: true, Index: c.f.variable, TypeID: pt, Position: position(n)})
							c.expression(d.Type, expr)
							c.emit(&ir.Store{TypeID: typ, Position: position(n.Token)})
							c.emit(&ir.Drop{TypeID: typ, Position: position(n)})
						}
						c.f.variable++
					}
				default: // external, internal
					c.out = append(c.out, ir.NewDataDefinition(p, nm, tnm, typ, ln, v))
					if expr != nil {
						TODO(position(expr))
					}
				}
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
	if cResult.Kind() == cc.Void && f.NameID == ir.NameID(idMain) && f.Linkage == ir.ExternalLinkage {
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

func (c *c) call(f cc.Type, n *cc.ArgumentExpressionListOpt) int {
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
			switch l.Expression.Type.Kind() {
			case cc.Char, cc.SChar, cc.UChar, cc.Short, cc.UShort:
				t = c.ast.Model.IntType
			case cc.Float:
				t = c.ast.Model.DoubleType
			}
			c.expression(t, l.Expression)
			i++
		}
	}
	return args
}

func (c *c) normalize(n *cc.Expression) cc.Node {
	for {
		switch n.Case {
		case 7: // '(' ExpressionList ')'
			l := n.ExpressionList
			if l.Len() != 1 {
				return l
			}

			n = l.Expression
		default:
			return n
		}
	}
}

func (c *c) field(n cc.Node, st cc.Type, nm int) (index int, t cc.Type) {
	ms, incomplete := st.Members()
	if incomplete {
		TODO(position(n))
	}

	for _, v := range ms {
		if v.Name == nm {
			if v.Bits != 0 {
				TODO(position(n))
			}

			return index, v.Type
		}

		if v.Bits != 0 && v.BitOffsetOf != 0 {
			continue
		}

		index++
	}
	panic("internal error")
}

func (c *c) addr(n *cc.Expression) {
	switch x := c.normalize(n).(type) {
	case *cc.Expression:
		n = x
	default:
		panic("internal error")
	}
	if n.Value != nil {
		TODO(position(n))
		return
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
				panic("internal error")
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
				t := c.types.MustType(at).Pointer()
				c.emit(&ir.Argument{Address: true, Index: vi.index, TypeID: t.ID(), Position: position(n)})
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
		return
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
		return
	case 9: // Expression '(' ArgumentExpressionListOpt ')'       // Case 9
		TODO(position(n))
	case 10: // Expression '.' IDENTIFIER                          // Case 10
		c.addr(n.Expression)
		fi, _ := c.field(n, n.Expression.Type, n.Token2.Val)
		c.emit(&ir.Field{Address: true, Index: fi, TypeID: c.typ(n.Expression.Type.Pointer()).ID(), Position: position(n)})
		return
	case 11: // Expression "->" IDENTIFIER                         // Case 11
		TODO(position(n))
	case 12: // Expression "++"                                    // Case 12
		TODO(position(n))
	case 13: // Expression "--"                                    // Case 13
		TODO(position(n))
	case 14: // '(' TypeName ')' '{' InitializerList CommaOpt '}'  // Case 14
		TODO(position(n))
	case 15: // "++" Expression                                    // Case 15
		TODO(position(n))
	case 16: // "--" Expression                                    // Case 16
		TODO(position(n))
	case 17: // '&' Expression                                     // Case 17
		TODO(position(n))
	case 18: // '*' Expression                                     // Case 18
		c.expression(nil, n.Expression)
		return
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
		TODO(position(n))
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
	}
	panic(fmt.Errorf("internal error: %v", position(n)))
}

func (c *c) convert(n cc.Node, from, to cc.Type) {
	c.emit(&ir.Convert{TypeID: c.typ(from).ID(), Result: c.typ(to).ID(), Position: position(n)})
}

func (c *c) constant(t cc.Type, v interface{}, n cc.Node) {
	switch x := v.(type) {
	case int32:
		c.emit(&ir.Const32{TypeID: ir.TypeID(idInt32), Value: x, Position: position(n)})
		c.convert(n, c.ast.Model.IntType, t)
		return
	case int64:
		c.emit(&ir.Const64{TypeID: ir.TypeID(idInt64), Value: x, Position: position(n)})
		c.convert(n, c.ast.Model.LongLongType, t)
		return
	case uint64:
		c.emit(&ir.Const64{TypeID: ir.TypeID(idUint64), Value: int64(x), Position: position(n)})
		c.convert(n, c.ast.Model.ULongLongType, t)
		return
	case float64:
		c.emit(&ir.Const64{TypeID: ir.TypeID(idFloat64), Value: int64(math.Float64bits(x)), Position: position(n)})
		c.convert(n, c.ast.Model.DoubleType, t)
		return
	case cc.StringLitID:
		c.emit(&ir.StringConst{Value: ir.StringID(x), Position: position(n)})
		return
	case uintptr:
		switch {
		case x == 0:
			c.emit(&ir.Nil{TypeID: c.typ(t).ID(), Position: position(n)})
		default:
			TODO(fmt.Errorf("%s: %T", position(n), x))
		}
		return
	}
}

func (c *c) binopType(n *cc.Expression) cc.Type {
	if t := n.BinOpType; t != nil {
		return t
	}

	return n.Expression.Type
}

func (c *c) binop(n *cc.Expression, op ir.Operation) {
	t := c.binopType(n)
	c.expression(t, n.Expression)
	c.expression(t, n.Expression2)
	c.emit(op)
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

func (c *c) asop(n *cc.Expression, op ir.Operation) {
	evalType := c.asopType(n)
	c.addr(n.Expression)
	pt := c.typ(n.Expression.Type.Pointer()).ID()
	c.emit(&ir.Dup{TypeID: pt, Position: position(n.ExpressionList)})
	c.emit(&ir.Load{TypeID: pt, Position: position(n)})
	at := c.typ(n.Expression.Type).ID()
	c.convert(n, n.Expression.Type, evalType)
	switch {
	case n.Expression.Type.Kind() == cc.Ptr:
		c.expression(nil, n.Expression2)
	default:
		c.expression(evalType, n.Expression2)
	}
	c.emit(op)
	c.convert(n, evalType, n.Expression.Type)
	c.emit(&ir.Store{TypeID: at.ID(), Position: position(n)})
}

func (c *c) expression(ot cc.Type, n *cc.Expression) { // rvalue
	switch x := c.normalize(n).(type) {
	case *cc.ExpressionList:
		c.expressionList(ot, x)
	case *cc.Expression:
		n = x
	default:
		panic("internal error")
	}

	if v := n.Value; v != nil {
		t := n.Type
		if ot != nil {
			t = ot
		}
		c.constant(t, v, n)
		return
	}

	t := n.Type
	switch t.Kind() {
	case cc.Function:
		c.addr(n)
		return
	}

out:
	switch {
	case ot != nil && ot.Kind() != t.Kind():
		switch ot.Kind() {
		case cc.Void:
			c.expression(nil, n)
			if n.Type.Kind() != cc.Void {
				c.emit(&ir.Drop{TypeID: c.typ(n.Type).ID(), Position: position(n)})
			}
		default:
			switch {
			case cc.IsArithmeticType(ot) && cc.IsArithmeticType(t):
				c.expression(nil, n)
				c.convert(n, t, ot)
			case ot.Kind() == cc.Ptr && t.Kind() == cc.Array:
				break out
			default:
				TODO(position(n), ot, t)
			}
		}
		return
	}

	switch t.Kind() {
	case cc.Array:
		if n.Case != 45 { // Expression '=' Expression                          // Case 45
			c.addr(n)
			return
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
				panic("internal error")
			case vi.static:
				t, _ := c.types.Type(vi.typ)
				switch {
				case t.Kind() == ir.Array:
					t = t.(*ir.ArrayType).Item.Pointer()
				default:
					t = t.Pointer()
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
		TODO(position(n))
	case 8: // Expression '[' ExpressionList ']'                  // Case 8
		t := n.Expression.Type
		if t.Kind() == cc.Array {
			t = t.Element().Pointer()
		}
		c.expression(nil, n.Expression)
		c.expressionList(nil, n.ExpressionList)
		c.emit(&ir.Element{IndexType: c.typ(n.ExpressionList.Type).ID(), TypeID: c.typ(t).ID(), Position: position(n)})
	case 9: // Expression '(' ArgumentExpressionListOpt ')'       // Case 9
		switch t := n.Expression.Type; t.Kind() {
		case cc.Function:
			if r := t.Result(); r.Kind() != cc.Void {
				c.emit(&ir.AllocResult{TypeID: c.typ(r).ID(), TypeName: 0, Position: position(n)})
			}
			c.expression(t.Pointer(), n.Expression)
			args := c.call(t, n.ArgumentExpressionListOpt)
			c.emit(&ir.CallFP{Arguments: args, TypeID: c.typ(t.Pointer()).ID(), Position: position(n)})
		case cc.Ptr:
			TODO(position(n))
			// ft := t.Element()
			// if ft.Kind() != cc.Function {
			// 	panic("internal error")
			// }

			// c.call(ft, n.ArgumentExpressionListOpt)
			// c.expression(t, n.Expression)
			// c.f.Emit(ir.Call, c.typ(t), nil, position(n))
		default:
			TODO(position(n), t.Kind())
		}
	case 10: // Expression '.' IDENTIFIER                          // Case 10
		c.addr(n.Expression)
		fi, _ := c.field(n, n.Expression.Type, n.Token2.Val)
		c.emit(&ir.Field{Index: fi, TypeID: c.typ(n.Expression.Type.Pointer()).ID(), Position: position(n)})
	case 11: // Expression "->" IDENTIFIER                         // Case 11
		c.expression(nil, n.Expression)
		fi, _ := c.field(n, n.Expression.Type.Element(), n.Token2.Val)
		c.emit(&ir.Field{Index: fi, TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
	case 12: // Expression "++"                                    // Case 12
		c.addr(n.Expression)
		delta := 1
		if t := n.Expression.Type; t.Kind() == cc.Ptr {
			delta = t.Element().SizeOf()
		}
		c.emit(&ir.PostIncrement{Delta: delta, TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
	case 13: // Expression "--"                                    // Case 13
		c.addr(n.Expression)
		delta := 1
		if t := n.Expression.Type; t.Kind() == cc.Ptr {
			delta = t.Element().SizeOf()
		}
		c.emit(&ir.PostIncrement{Delta: -delta, TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
	case 14: // '(' TypeName ')' '{' InitializerList CommaOpt '}'  // Case 14
		TODO(position(n))
	case 15: // "++" Expression                                    // Case 15
		c.addr(n.Expression)
		delta := 1
		if t := n.Expression.Type; t.Kind() == cc.Ptr {
			delta = t.Element().SizeOf()
		}
		c.emit(&ir.PreIncrement{Delta: delta, TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
	case 16: // "--" Expression                                    // Case 16
		c.addr(n.Expression)
		delta := 1
		if t := n.Expression.Type; t.Kind() == cc.Ptr {
			delta = t.Element().SizeOf()
		}
		c.emit(&ir.PreIncrement{Delta: -delta, TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
	case 17: // '&' Expression                                     // Case 17
		if n.Expression.Type.Kind() == cc.Array {
			TODO(position(n))
			break
		}

		c.addr(n.Expression)
	case 18: // '*' Expression                                     // Case 18
		c.expression(nil, n.Expression)
		c.emit(&ir.Load{TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
	case 19: // '+' Expression                                     // Case 19
		TODO(position(n))
	case 20: // '-' Expression                                     // Case 20
		TODO(position(n))
	case 21: // '~' Expression                                     // Case 21
		TODO(position(n))
	case 22: // '!' Expression                                     // Case 22
		c.expression(nil, n.Expression)
		c.emit(&ir.Bool{TypeID: c.typ(n.Expression.Type).ID(), Position: position(n.Expression)})
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
		c.expression(n.TypeName.Type, n.Expression)
	case 26: // Expression '*' Expression                          // Case 26
		c.binop(n, &ir.Mul{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 27: // Expression '/' Expression                          // Case 27
		c.binop(n, &ir.Div{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 28: // Expression '%' Expression                          // Case 28
		c.binop(n, &ir.Rem{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 29: // Expression '+' Expression                          // Case 29
		if n.Expression.Type.Kind() == cc.Ptr || n.Expression2.Type.Kind() == cc.Ptr {
			TODO(position(n))
			break
		}

		c.binop(n, &ir.Add{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 30: // Expression '-' Expression                          // Case 30
		if n.Expression.Type.Kind() == cc.Ptr || n.Expression2.Type.Kind() == cc.Ptr {
			c.expression(nil, n.Expression)
			c.expression(nil, n.Expression2)
			c.emit(&ir.PtrDiff{TypeID: c.typ(n.Type).ID(), Position: position(n)})
			break
		}

		c.binop(n, &ir.Sub{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 31: // Expression "<<" Expression                         // Case 31
		TODO(position(n))
	case 32: // Expression ">>" Expression                         // Case 32
		TODO(position(n))
	case 33: // Expression '<' Expression                          // Case 33
		c.binop(n, &ir.Lt{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 34: // Expression '>' Expression                          // Case 34
		c.binop(n, &ir.Gt{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 35: // Expression "<=" Expression                         // Case 35
		c.binop(n, &ir.Leq{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 36: // Expression ">=" Expression                         // Case 36
		c.binop(n, &ir.Geq{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 37: // Expression "==" Expression                         // Case 37
		c.binop(n, &ir.Eq{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 38: // Expression "!=" Expression                         // Case 38
		c.binop(n, &ir.Neq{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 39: // Expression '&' Expression                          // Case 39
		c.binop(n, &ir.And{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 40: // Expression '^' Expression                          // Case 40
		c.binop(n, &ir.Xor{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
	case 41: // Expression '|' Expression                          // Case 41
		c.binop(n, &ir.Or{TypeID: c.typ(c.binopType(n)).ID(), Position: position(n)})
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
		c.emit(&ir.Const32{TypeID: ir.TypeID(idInt32), Position: position(n)})
		c.expression(nil, n.Expression)
		if n.Expression.Type.Kind() != cc.Int {
			c.emit(&ir.Bool{TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
		}
		a := c.label()
		c.emit(&ir.Jz{Number: a, Position: position(n.Expression)})
		c.expression(nil, n.Expression2)
		if n.Expression2.Type.Kind() != cc.Int {
			c.emit(&ir.Bool{TypeID: c.typ(n.Expression2.Type).ID(), Position: position(n)})
		}
		c.emit(&ir.Jz{Number: a, Position: position(n.Expression)})
		c.emit(&ir.Drop{TypeID: ir.TypeID(idInt32), Position: position(n)})
		c.emit(&ir.Const32{TypeID: ir.TypeID(idInt32), Value: 1, Position: position(n)})
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
		c.emit(&ir.Const32{TypeID: ir.TypeID(idInt32), Value: 1, Position: position(n)})
		c.expression(nil, n.Expression)
		if n.Expression.Type.Kind() != cc.Int {
			c.emit(&ir.Bool{TypeID: c.typ(n.Expression.Type).ID(), Position: position(n)})
		}
		a := c.label()
		c.emit(&ir.Jnz{Number: a, Position: position(n.Expression)})
		c.expression(nil, n.Expression2)
		if n.Expression2.Type.Kind() != cc.Int {
			c.emit(&ir.Bool{TypeID: c.typ(n.Expression2.Type).ID(), Position: position(n)})
		}
		c.emit(&ir.Jnz{Number: a, Position: position(n.Expression)})
		c.emit(&ir.Drop{TypeID: ir.TypeID(idInt32), Position: position(n)})
		c.emit(&ir.Const32{TypeID: ir.TypeID(idInt32), Position: position(n)})
		c.emit(&ir.Label{Number: a, Position: position(n)})
	case 44: // Expression '?' ExpressionList ':' Expression       // Case 44
		// eval expr
		// convert to bool if necessary
		// jz 1
		// eval exprlist
		// jmp 2
		// 1: eval expr2
		// 2:
		c.expression(nil, n.Expression)
		if n.Expression2.Type.Kind() != cc.Int {
			c.emit(&ir.Bool{TypeID: c.typ(n.Expression2.Type).ID(), Position: position(n)})
		}
		l1 := c.label()
		c.emit(&ir.Jz{Number: l1, Position: position(n.Expression)})
		c.expressionList(nil, n.ExpressionList)
		l2 := c.label()
		c.emit(&ir.Jmp{Number: l2, Position: position(n)})
		c.emit(&ir.Label{Number: l1, Position: position(n)})
		c.expression(n.ExpressionList.Type, n.Expression2)
		c.emit(&ir.Label{Number: l2, Position: position(n)})
	case 45: // Expression '=' Expression                          // Case 45
		c.addr(n.Expression)
		c.expression(n.Expression.Type, n.Expression2)
		switch t := n.Expression.Type; t.Kind() {
		case cc.Array:
			c.emit(&ir.Copy{TypeID: c.typ(n.Expression2.Type).ID(), Position: position(n)})
		default:
			c.emit(&ir.Store{TypeID: c.typ(n.Expression.Type).ID(), Position: position(n.Token)})
		}
	case 46: // Expression "*=" Expression                         // Case 46
		c.asop(n, &ir.Mul{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)})
	case 47: // Expression "/=" Expression                         // Case 47
		c.asop(n, &ir.Div{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)})
	case 48: // Expression "%=" Expression                         // Case 48
		TODO(position(n))
	case 49: // Expression "+=" Expression                         // Case 49
		if t := n.Expression.Type; t.Kind() == cc.Ptr {
			c.asop(n, &ir.Element{Address: true, TypeID: c.typ(t).ID(), IndexType: c.typ(n.Expression2.Type).ID(), Position: position(n)})
			break
		}

		c.asop(n, &ir.Add{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)})
	case 50: // Expression "-=" Expression                         // Case 50
		if n.Expression.Type.Kind() == cc.Ptr {
			c.emit(&ir.Neg{TypeID: c.typ(n.Expression2.Type).ID(), Position: position(n)})
			c.asop(n, &ir.Element{Address: true, TypeID: c.typ(t).ID(), IndexType: c.typ(n.Expression2.Type).ID(), Position: position(n)})
			break
		}

		c.asop(n, &ir.Sub{TypeID: c.typ(c.asopType(n)).ID(), Position: position(n)})
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
	default:
		panic("internal error")
	}
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

func (c *c) expressionListOpt(ot cc.Type, n *cc.ExpressionListOpt) {
	if n == nil {
		return
	}

	c.expressionList(ot, n.ExpressionList)
}

func (c *c) expressionStatement(n *cc.ExpressionStatement) {
	c.expressionListOpt(c.ast.Model.VoidType, n.ExpressionListOpt)
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
			r := c.f.result
			c.emit(&ir.Result{Address: true, TypeID: c.types.MustType(r).Pointer().ID(), Position: position(n)})
			l := o.ExpressionList
			c.expressionList(c.f.cResult, l)
			c.emit(&ir.Store{TypeID: r, Position: position(n)})
			c.emit(&ir.Drop{TypeID: r, Position: position(n)})
		}
		c.emit(&ir.Return{Position: position(n)})
	default:
		panic("internal error")
	}
}

func (c *c) label() int {
	r := c.f.label
	c.f.label++
	return r
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
		if el.Type.Kind() != cc.Int {
			c.emit(&ir.Bool{TypeID: c.typ(el.Type).ID(), Position: position(n)})
		}
		c.emit(&ir.Jz{Number: end, Position: position(n)})
		breakLabel := labels.setBreak(end)
		c.statement(labels, n.Statement)
		labels.setBreak(breakLabel)
		labels.setContinue(cl)
		c.emit(&ir.Jmp{Number: begin, Position: position(n)})
		c.emit(&ir.Label{Number: end, Position: position(n)})
	case 1: // "do" Statement "while" '(' ExpressionList ')' ';'                                      // Case 1
		begin := c.label()
		c.emit(&ir.Label{Number: begin, Position: position(n)})
		breakLabel := labels.setBreak(-1)
		cl := labels.setContinue(begin)
		c.statement(labels, n.Statement)
		el := n.ExpressionList
		c.expressionList(el.Type, el)
		if el.Type.Kind() != cc.Int {
			c.emit(&ir.Bool{TypeID: c.typ(el.Type).ID(), Position: position(n)})
		}
		c.emit(&ir.Jnz{Number: begin, Position: position(n.ExpressionList)})
		if e := labels.breakLabel; e >= 0 {
			c.emit(&ir.Label{Number: e, Position: position(n)})
		}
		labels.setBreak(breakLabel)
		labels.setContinue(cl)
	case 2: // "for" '(' ExpressionListOpt ';' ExpressionListOpt ';' ExpressionListOpt ')' Statement  // Case 2
		c.expressionListOpt(c.ast.Model.VoidType, n.ExpressionListOpt)
		test := c.label()
		cl := labels.setContinue(test)
		c.emit(&ir.Label{Number: test, Position: position(n)})
		end := c.label()
		if o := n.ExpressionListOpt2; o != nil {
			el := o.ExpressionList
			c.expressionList(el.Type, el)
			end = c.label()
			if el.Type.Kind() != cc.Int {
				c.emit(&ir.Bool{TypeID: c.typ(el.Type).ID(), Position: position(n)})
			}
			c.emit(&ir.Jz{Number: end, Position: position(n)})
		}
		breakLabel := labels.setBreak(end)
		c.statement(labels, n.Statement)
		labels.setBreak(breakLabel)
		labels.setContinue(cl)
		c.expressionListOpt(c.ast.Model.VoidType, n.ExpressionListOpt3)
		c.emit(&ir.Jmp{Number: test, Position: position(n)})
		c.emit(&ir.Label{Number: end, Position: position(n)})
	case 3: // "for" '(' Declaration ExpressionListOpt ';' ExpressionListOpt ')' Statement            // Case 3
		TODO(position(n))
	default:
		panic("internal error")
	}
}

func (c *c) switchStatement(n *cc.SelectionStatement) {
	// "switch" '(' ExpressionList ')' Statement               // Case 2
	t := n.ExpressionList.Type
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
		c.constant(v.Type, v.Value, v)
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
	default:
		c.emit(&ir.Jmp{Number: defaultCase, Position: position(n)})
	}
	c.statement(&labels, n.Statement)
	if labels.breakLabel >= 0 {
		c.emit(&ir.Label{Number: labels.breakLabel, Position: position(n.ExpressionList)})
	}
}

func (c *c) selectionStatement(labels *labels, n *cc.SelectionStatement) {
	switch n.Case {
	case 0: // "if" '(' ExpressionList ')' Statement
		// expr; jz 1; stmt; 1:
		c.expressionList(nil, n.ExpressionList)
		if n.ExpressionList.Type.Kind() != cc.Int {
			c.emit(&ir.Bool{TypeID: c.typ(n.ExpressionList.Type).ID(), Position: position(n)})
		}
		l1 := c.label()
		c.emit(&ir.Jz{Number: l1, Position: position(n)})
		c.statement(labels, n.Statement)
		c.emit(&ir.Label{Number: l1, Position: position(n)})
	case 1: // "if" '(' ExpressionList ')' Statement "else" Statement  // Case 1
		// expr; jz 1; stmt; jmp 2; 1: stmt2; 2:
		c.expressionList(nil, n.ExpressionList)
		if n.ExpressionList.Type.Kind() != cc.Int {
			c.emit(&ir.Bool{TypeID: c.typ(n.ExpressionList.Type).ID(), Position: position(n)})
		}
		l1 := c.label()
		c.emit(&ir.Jz{Number: l1, Position: position(n)})
		c.statement(labels, n.Statement)
		l2 := c.label()
		c.emit(&ir.Jmp{Number: l2, Position: position(n)})
		c.emit(&ir.Label{Number: l1, Position: position(n)})
		c.statement(labels, n.Statement2)
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
	c.statement(labels, n.Statement)
}

func (c *c) statement(labels *labels, n *cc.Statement) {
	switch n.Case {
	case 0: // LabeledStatement
		c.labeledStatement(labels, n.LabeledStatement)
	case 1: // CompoundStatement    // Case 1
		c.compoundStatement(labels, n.CompoundStatement)
	case 2: // ExpressionStatement  // Case 2
		c.expressionStatement(n.ExpressionStatement)
	case 3: // SelectionStatement   // Case 3
		c.selectionStatement(labels, n.SelectionStatement)
	case 4: // IterationStatement   // Case 4
		c.iterationStatement(labels, n.IterationStatement)
	case 5: // JumpStatement        // Case 5
		c.jumpStatement(labels, n.JumpStatement)
	case 6: // AssemblerStatement   // Case 6
		TODO(position(n))
	default:
		panic("internal error")
	}
}

func (c *c) blockItem(labels *labels, n *cc.BlockItem) {
	switch n.Case {
	case 0: // Declaration
		c.declaration(n.Declaration)
	case 1: // Statement    // Case 1
		c.statement(labels, n.Statement)
	default:
		panic("internal error")
	}
}

func (c *c) compoundStatement(labels *labels, n *cc.CompoundStatement) {
	c.f.blockLevel++
	c.emit(&ir.BeginScope{Position: position(n)})
	if o := n.BlockItemListOpt; o != nil {
		for l := o.BlockItemList; l != nil; l = l.BlockItemList {
			c.blockItem(labels, l.BlockItem)
		}
	}
	c.f.blockLevel--
	if c.f.blockLevel == 0 {
		b := c.f.f.Body
		if _, ok := b[len(b)-1].(*ir.Return); !ok {
			c.emit(&ir.Return{Position: position(n.Token2)})
		}
	}
	c.emit(&ir.EndScope{Position: position(n.Token2)})
}

func (c *c) functionBody(n *cc.FunctionBody) {
	switch n.Case {
	case 0: // CompoundStatement
		c.compoundStatement(&labels{-1, -1, -1}, n.CompoundStatement)
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
	case 0: // DeclarationSpecifiers Declarator DeclarationListOpt FunctionBody
		d := n.Declarator
		t := c.typ(d.Type)
		nm := c.nm(d)
		ln := c.linkage(d.Linkage)
		if ln == ir.ExternalLinkage && int(nm) == idMain && len(t.(*ir.FunctionType).Results) == 0 {
			t = c.types.MustType(ir.TypeID(dict.SID(string(dict.S(int(t.ID()))) + "int32")))
		}
		c.newFData(d.Type, ir.NewFunctionDefinition(position(n), nm, c.tnm(d), t.ID(), ln, c.fnArgNames(d), nil))
		c.out = append(c.out, c.f.f)
		c.functionBody(n.FunctionBody)
		c.f = fdata{}
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
		c.declaration(n.Declaration)
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
