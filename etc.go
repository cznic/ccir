// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package ccir

import (
	"go/token"

	"github.com/cznic/cc"
	"github.com/cznic/xc"
)

var (
	dict = xc.Dict

	idFloat64 = dict.SID("float64")
	idInt32   = dict.SID("int32")
	idInt64   = dict.SID("int64")
	idMain    = dict.SID("main")
	idUint32  = dict.SID("uint32")
	idUint64  = dict.SID("uint64")
)

func position(n cc.Node) token.Position { return xc.FileSet.Position(n.Pos()) }
