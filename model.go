// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package ccir

import (
	"fmt"
	"github.com/cznic/cc"
	"github.com/cznic/ir"
)

// Model returns a *cc.Model associated with name or an error, if any.
func Model(name string) (*cc.Model, error) {
	if _, ok := ir.MemoryModels[name]; !ok {
		return nil, fmt.Errorf("unknown ir memory model %q", name)
	}

	switch name {
	case "32":
		return &cc.Model{
			Items: map[cc.Kind]cc.ModelItem{
				cc.Void:              {Size: 0, Align: 1, StructAlign: 1},
				cc.Ptr:               {Size: 4, Align: 4, StructAlign: 4},
				cc.UintPtr:           {Size: 4, Align: 4, StructAlign: 4},
				cc.Char:              {Size: 1, Align: 1, StructAlign: 1},
				cc.SChar:             {Size: 1, Align: 1, StructAlign: 1},
				cc.UChar:             {Size: 1, Align: 1, StructAlign: 1},
				cc.Short:             {Size: 2, Align: 2, StructAlign: 2},
				cc.UShort:            {Size: 2, Align: 2, StructAlign: 2},
				cc.Int:               {Size: 4, Align: 4, StructAlign: 4},
				cc.UInt:              {Size: 4, Align: 4, StructAlign: 4},
				cc.Long:              {Size: 4, Align: 4, StructAlign: 4},
				cc.ULong:             {Size: 4, Align: 4, StructAlign: 4},
				cc.LongLong:          {Size: 8, Align: 4, StructAlign: 4},
				cc.ULongLong:         {Size: 8, Align: 4, StructAlign: 4},
				cc.Float:             {Size: 4, Align: 4, StructAlign: 4},
				cc.Double:            {Size: 8, Align: 4, StructAlign: 4},
				cc.LongDouble:        {Size: 16, Align: 4, StructAlign: 4},
				cc.Bool:              {Size: 1, Align: 1, StructAlign: 1},
				cc.FloatComplex:      {Size: 8, Align: 4, StructAlign: 4},
				cc.DoubleComplex:     {Size: 16, Align: 4, StructAlign: 4},
				cc.LongDoubleComplex: {Size: 32, Align: 4, StructAlign: 4},
			},
		}, nil
	case "64":
		return &cc.Model{
			Items: map[cc.Kind]cc.ModelItem{
				cc.Void:              {Size: 0, Align: 1, StructAlign: 1},
				cc.Ptr:               {Size: 8, Align: 8, StructAlign: 8},
				cc.UintPtr:           {Size: 8, Align: 8, StructAlign: 8},
				cc.Char:              {Size: 1, Align: 1, StructAlign: 1},
				cc.SChar:             {Size: 1, Align: 1, StructAlign: 1},
				cc.UChar:             {Size: 1, Align: 1, StructAlign: 1},
				cc.Short:             {Size: 2, Align: 2, StructAlign: 2},
				cc.UShort:            {Size: 2, Align: 2, StructAlign: 2},
				cc.Int:               {Size: 4, Align: 4, StructAlign: 4},
				cc.UInt:              {Size: 4, Align: 4, StructAlign: 4},
				cc.Long:              {Size: 8, Align: 8, StructAlign: 8},
				cc.ULong:             {Size: 8, Align: 8, StructAlign: 8},
				cc.LongLong:          {Size: 8, Align: 8, StructAlign: 8},
				cc.ULongLong:         {Size: 8, Align: 8, StructAlign: 8},
				cc.Float:             {Size: 4, Align: 4, StructAlign: 4},
				cc.Double:            {Size: 8, Align: 8, StructAlign: 8},
				cc.LongDouble:        {Size: 16, Align: 8, StructAlign: 8},
				cc.Bool:              {Size: 1, Align: 1, StructAlign: 1},
				cc.FloatComplex:      {Size: 8, Align: 8, StructAlign: 8},
				cc.DoubleComplex:     {Size: 16, Align: 8, StructAlign: 8},
				cc.LongDoubleComplex: {Size: 32, Align: 8, StructAlign: 8},
			},
		}, nil
	default:
		return nil, fmt.Errorf("unknown ccir memory model %q", name)
	}
}
