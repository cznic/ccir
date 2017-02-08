// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package ccir

import (
	"bytes"
	"fmt"
	"go/scanner"
	"os"
	"path"
	"path/filepath"
	"runtime"
	"strings"
	"testing"

	"github.com/cznic/cc"
	"github.com/cznic/ir"
	"github.com/cznic/mathutil"
	"github.com/cznic/strutil"
)

func caller(s string, va ...interface{}) {
	if s == "" {
		s = strings.Repeat("%v ", len(va))
	}
	_, fn, fl, _ := runtime.Caller(2)
	fmt.Fprintf(os.Stderr, "# caller: %s:%d: ", path.Base(fn), fl)
	fmt.Fprintf(os.Stderr, s, va...)
	fmt.Fprintln(os.Stderr)
	_, fn, fl, _ = runtime.Caller(1)
	fmt.Fprintf(os.Stderr, "# \tcallee: %s:%d: ", path.Base(fn), fl)
	fmt.Fprintln(os.Stderr)
	os.Stderr.Sync()
}

func dbg(s string, va ...interface{}) {
	if s == "" {
		s = strings.Repeat("%v ", len(va))
	}
	_, fn, fl, _ := runtime.Caller(1)
	fmt.Fprintf(os.Stderr, "# dbg %s:%d ", path.Base(fn), fl)
	fmt.Fprintf(os.Stderr, s, va...)
	fmt.Fprintln(os.Stderr)
	os.Stderr.Sync()
}

func use(...interface{}) {}

func init() {
	use(caller, dbg, TODO) //TODOOK
	Testing = true
	ir.Testing = true
}

// ============================================================================

const (
	crt0Path = "testdata/include/crt0.c"
)

var (
	ccTestdata string
)

func init() {
	ip, err := cc.ImportPath()
	if err != nil {
		panic(err)
	}

	for _, v := range filepath.SplitList(strutil.Gopath()) {
		p := filepath.Join(v, "src", ip, "testdata")
		fi, err := os.Stat(p)
		if err != nil {
			continue
		}

		if fi.IsDir() {
			ccTestdata = p
			break
		}
	}
	if ccTestdata == "" {
		panic("cannot find cc/testdata/")
	}
}

func errStr(err error) string {
	switch x := err.(type) {
	case scanner.ErrorList:
		var b bytes.Buffer
		for i, v := range x {
			if i != 0 {
				b.WriteByte('\n')
			}
			b.WriteString(v.Error())
			if i == 9 {
				fmt.Fprintf(&b, "\n\t... and %v more errors", len(x)-10)
				break
			}
		}
		return b.String()
	default:
		return err.Error()
	}
}

func parse(src []string, opts ...cc.Opt) (string, *cc.TranslationUnit, error) {
	modelName := fmt.Sprint(mathutil.UintPtrBits)
	model, err := Model(modelName)
	if err != nil {
		return "", nil, err
	}

	ast, err := cc.Parse(
		fmt.Sprintf(`
#define __STDC_HOSTED__ 1
#define __STDC_VERSION__ 199901L
#define __STDC__ 1
`),
		src,
		model,
		opts...,
	)
	return modelName, ast, err
}

func TestTCC(t *testing.T) {
	wd, err := os.Getwd()
	if err != nil {
		t.Fatal(err)
	}

	testdata, err := filepath.Rel(wd, ccTestdata)
	if err != nil {
		t.Fatal(err)
	}

	dir := filepath.Join(testdata, filepath.FromSlash("tcc-0.9.26/tests/tests2/"))
	matches, err := filepath.Glob(filepath.Join(dir, "*.c"))
	if err != nil {
		t.Fatal(err)
	}

	for _, match := range matches {
		modelName, ast, err := parse(
			[]string{crt0Path, match},
			cc.EnableDefineOmitCommaBeforeDDD(),
			cc.ErrLimit(-1),
			cc.SysIncludePaths([]string{"testdata/include/"}),
		)
		if err != nil {
			t.Fatal(errStr(err))
		}

		objs, err := New(modelName, ast)
		if err != nil {
			t.Fatal(err)
		}

		var b bytes.Buffer
		for i, v := range objs {
			switch x := v.(type) {
			case *ir.FunctionDefinition:
				fmt.Fprintf(&b, "# [%v]: %v %v\n", i, x.ObjectBase, x.Arguments)
				for i, v := range x.Body {
					fmt.Fprintf(&b, "%#05x\t%v\n", i, v)
				}
			}
			if err := v.Verify(); err != nil {
				t.Fatal(err)
			}
		}
		t.Logf("\n%s", b.Bytes())

		if objs, err = ir.LinkMain(objs); err != nil {
			t.Fatal(err)
		}

		b.Reset()
		for i, v := range objs {
			switch x := v.(type) {
			case *ir.FunctionDefinition:
				fmt.Fprintf(&b, "# [%v]: %v %v\n", i, x.ObjectBase, x.Arguments)
				for i, v := range x.Body {
					fmt.Fprintf(&b, "%#05x\t%v\n", i, v)
				}
			}
			if err := v.Verify(); err != nil {
				t.Fatal(err)
			}
		}
		t.Logf("\n%s", b.Bytes())

		TODO(match)
	}
}
