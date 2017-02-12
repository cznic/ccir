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

	idBuiltinPrefix = dict.SID("__builtin_")
	idFloat64       = dict.SID("float64")
	idInt32         = dict.SID("int32")
	idMain          = dict.SID("main")
)

func position(n cc.Node) token.Position { return xc.FileSet.Position(n.Pos()) }
