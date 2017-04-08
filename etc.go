// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package ccir

import (
	"go/token"

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

func position(n cc.Node) token.Position { return xc.FileSet.Position(n.Pos()) }

func isUnsigned(t cc.Type) bool {
	switch t.Kind() {
	case cc.Bool, cc.UChar, cc.UShort, cc.UInt, cc.ULong, cc.ULongLong:
		return true
	default:
		return false
	}
}
