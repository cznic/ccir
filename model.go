// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package ccir

import (
	"fmt"
	"runtime"

	"github.com/cznic/cc"
)

func longSize() cc.ModelItem {
	s := 8
	if runtime.GOOS == "windows" {
		s = 4
	}
	return cc.ModelItem{Size: s, Align: s, StructAlign: s}
}

// NewModel returns a *cc.Model for the current architecture and platform.
func NewModel() (*cc.Model, error) {
	switch arch := runtime.GOARCH; arch {
	case "386", "arm", "armbe", "mips", "mipsle", "ppc", "ppc64le", "s390", "s390x", "sparc":
		return &cc.Model{
			Items: map[cc.Kind]cc.ModelItem{
				cc.Void:              {Align: 1, Size: 0, StructAlign: 1},
				cc.Ptr:               {Align: 4, Size: 4, StructAlign: 4},
				cc.UintPtr:           {Align: 4, Size: 4, StructAlign: 4},
				cc.Char:              {Align: 1, Size: 1, StructAlign: 1},
				cc.SChar:             {Align: 1, Size: 1, StructAlign: 1},
				cc.UChar:             {Align: 1, Size: 1, StructAlign: 1},
				cc.Short:             {Align: 2, Size: 2, StructAlign: 2},
				cc.UShort:            {Align: 2, Size: 2, StructAlign: 2},
				cc.Int:               {Align: 4, Size: 4, StructAlign: 4},
				cc.UInt:              {Align: 4, Size: 4, StructAlign: 4},
				cc.Long:              {Align: 4, Size: 4, StructAlign: 4},
				cc.ULong:             {Align: 4, Size: 4, StructAlign: 4},
				cc.LongLong:          {Align: 8, Size: 8, StructAlign: 4},
				cc.ULongLong:         {Align: 8, Size: 8, StructAlign: 4},
				cc.Float:             {Align: 4, Size: 4, StructAlign: 4},
				cc.Double:            {Align: 8, Size: 8, StructAlign: 4},
				cc.LongDouble:        {Align: 8, Size: 8, StructAlign: 4},
				cc.Bool:              {Align: 1, Size: 1, StructAlign: 1},
				cc.FloatComplex:      {Align: 8, Size: 8, StructAlign: 4},
				cc.DoubleComplex:     {Align: 8, Size: 16, StructAlign: 4},
				cc.LongDoubleComplex: {Align: 8, Size: 16, StructAlign: 4},
			},
		}, nil
	case "amd64p32", "mips64p32", "mips64p32le":
		return &cc.Model{
			Items: map[cc.Kind]cc.ModelItem{
				cc.Void:              {Align: 1, Size: 0, StructAlign: 1},
				cc.Ptr:               {Align: 4, Size: 4, StructAlign: 4},
				cc.UintPtr:           {Align: 4, Size: 4, StructAlign: 4},
				cc.Char:              {Align: 1, Size: 1, StructAlign: 1},
				cc.SChar:             {Align: 1, Size: 1, StructAlign: 1},
				cc.UChar:             {Align: 1, Size: 1, StructAlign: 1},
				cc.Short:             {Align: 2, Size: 2, StructAlign: 2},
				cc.UShort:            {Align: 2, Size: 2, StructAlign: 2},
				cc.Int:               {Align: 4, Size: 4, StructAlign: 4},
				cc.UInt:              {Align: 4, Size: 4, StructAlign: 4},
				cc.Long:              {Align: 8, Size: 8, StructAlign: 8},
				cc.ULong:             {Align: 8, Size: 8, StructAlign: 8},
				cc.LongLong:          {Align: 8, Size: 8, StructAlign: 8},
				cc.ULongLong:         {Align: 8, Size: 8, StructAlign: 8},
				cc.Float:             {Align: 4, Size: 4, StructAlign: 4},
				cc.Double:            {Align: 8, Size: 8, StructAlign: 8},
				cc.LongDouble:        {Align: 8, Size: 8, StructAlign: 8},
				cc.Bool:              {Align: 1, Size: 1, StructAlign: 1},
				cc.FloatComplex:      {Align: 8, Size: 8, StructAlign: 4},
				cc.DoubleComplex:     {Align: 8, Size: 16, StructAlign: 8},
				cc.LongDoubleComplex: {Align: 8, Size: 16, StructAlign: 8},
			},
		}, nil
	case "amd64", "arm64", "arm64be", "mips64", "mips64le", "ppc64", "sparc64":
		return &cc.Model{
			Items: map[cc.Kind]cc.ModelItem{
				cc.Void:              {Align: 1, Size: 0, StructAlign: 1},
				cc.Ptr:               {Align: 8, Size: 8, StructAlign: 8},
				cc.UintPtr:           {Align: 8, Size: 8, StructAlign: 8},
				cc.Char:              {Align: 1, Size: 1, StructAlign: 1},
				cc.SChar:             {Align: 1, Size: 1, StructAlign: 1},
				cc.UChar:             {Align: 1, Size: 1, StructAlign: 1},
				cc.Short:             {Align: 2, Size: 2, StructAlign: 2},
				cc.UShort:            {Align: 2, Size: 2, StructAlign: 2},
				cc.Int:               {Align: 4, Size: 4, StructAlign: 4},
				cc.UInt:              {Align: 4, Size: 4, StructAlign: 4},
				cc.Long:              longSize(),
				cc.ULong:             longSize(),
				cc.LongLong:          {Align: 8, Size: 8, StructAlign: 8},
				cc.ULongLong:         {Align: 8, Size: 8, StructAlign: 8},
				cc.Float:             {Align: 4, Size: 4, StructAlign: 4},
				cc.Double:            {Align: 8, Size: 8, StructAlign: 8},
				cc.LongDouble:        {Align: 8, Size: 8, StructAlign: 8},
				cc.Bool:              {Align: 1, Size: 1, StructAlign: 1},
				cc.FloatComplex:      {Align: 8, Size: 8, StructAlign: 4},
				cc.DoubleComplex:     {Align: 8, Size: 16, StructAlign: 8},
				cc.LongDoubleComplex: {Align: 8, Size: 16, StructAlign: 8},
			},
		}, nil
	default:
		return nil, fmt.Errorf("unknown/unsupported architecture %s", arch)
	}
}
