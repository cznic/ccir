// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package ccir

import (
	"go/scanner"
	"go/token"
	"strings"

	"github.com/cznic/cc"
	"github.com/cznic/ir"
	"github.com/cznic/xc"
)

var (
	dict = xc.Dict

	idBuiltinPrefix = dict.SID("__builtin_")
	idComplex128    = ir.TypeID(dict.SID("complex128"))
	idComplex64     = ir.TypeID(dict.SID("complex64"))
	idEmptyString   = dict.SID(`""`)
	idFloat32       = ir.TypeID(dict.SID("float32"))
	idFloat64       = ir.TypeID(dict.SID("float64"))
	idInt16         = ir.TypeID(dict.SID("int16"))
	idInt32         = ir.TypeID(dict.SID("int32"))
	idInt64         = ir.TypeID(dict.SID("int64"))
	idInt8          = ir.TypeID(dict.SID("int8"))
	idMain          = ir.NameID(dict.SID("main"))
	idPInt32        = ir.TypeID(dict.SID("*int32"))
	idUint16        = ir.TypeID(dict.SID("uint16"))
	idUint32        = ir.TypeID(dict.SID("uint32"))
	idUint64        = ir.TypeID(dict.SID("uint64"))
	idUint8         = ir.TypeID(dict.SID("uint8"))
	idVoidPtr       = ir.TypeID(dict.SID("*struct{}"))
)

func position(n cc.Node) token.Position {
	if n != nil {
		return xc.FileSet.Position(n.Pos())
	}

	return token.Position{}
}

func isUnsigned(t cc.Type) bool {
	switch t.Kind() {
	case cc.Bool, cc.UChar, cc.UShort, cc.UInt, cc.ULong, cc.ULongLong:
		return true
	default:
		return false
	}
}

func isOpenMDArray(t cc.Type) bool {
	if t.Kind() != cc.Ptr {
		return false
	}

	et := t.Element()
	if et.Kind() != cc.Array {
		return false
	}

	ts := t.String()
	es := et.String()
	r := 1
	for ts[len(ts)-r] == es[len(es)-r] {
		r++
	}
	n := len(es) - r + 1
	return ts[n:n+2] == "[]"
}

func tidyComment(s string) string {
	switch {
	case strings.HasPrefix(s, "/*"):
		a := strings.Split(" "+s[1:len(s)-1], "\n")
		for i, v := range a {
			a[i] = "//  " + v
		}
		return "// C comment\n" + strings.Join(a, "\n") + "\n"
	case strings.HasPrefix(s, "//"):
		return "//  " + s[2:] + "\n"
	default:
		panic("internal error")
	}
}

func tidyComments(b []byte) string {
	var s scanner.Scanner
	s.Init(token.NewFileSet().AddFile("", -1, len(b)), b, nil, scanner.ScanComments)
	var a []string
	for {
		_, tok, lit := s.Scan()
		if tok == token.EOF {
			return strings.Join(a, "\n")
		}

		a = append(a, tidyComment(lit))
	}
}
