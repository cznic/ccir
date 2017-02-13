// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package ccir

import (
	"bytes"
	"fmt"
	"go/scanner"
	"io/ioutil"
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
	"github.com/cznic/virtual"
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
	virtual.Testing = true
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

	ast, err := cc.Parse(`
#define __STDC_HOSTED__ 1
#define __STDC_VERSION__ 199901L
#define __STDC__ 1
`,
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
			t.Fatal(match, errStr(err))
		}

		objs, err := New(modelName, ast)
		if err != nil {
			t.Fatal(match, err)
		}

		var b bytes.Buffer
		for i, v := range objs {
			switch x := v.(type) {
			case *ir.DataDefinition:
				fmt.Fprintf(&b, "# [%v]: %T %v %v\n", i, x, x.ObjectBase, x.Value)
			case *ir.FunctionDefinition:
				fmt.Fprintf(&b, "# [%v]: %T %v %v\n", i, x, x.ObjectBase, x.Arguments)
				for i, v := range x.Body {
					fmt.Fprintf(&b, "%#05x\t%v\n", i, v)
				}
			default:
				t.Fatalf("[%v] %T %v", i, x, x)
			}
		}
		t.Logf("ccir.New: %v objects\n%s", len(objs), b.Bytes())
		for i, v := range objs {
			if err := v.Verify(); err != nil {
				switch x := v.(type) {
				case *ir.FunctionDefinition:
					t.Logf("# [%v]: %T %v %v\n", i, x, x.ObjectBase, x.Arguments)
					for i, v := range x.Body {
						t.Logf("%#05x\t%v\n", i, v)
					}
					t.Fatal(err)
				default:
					t.Fatalf("[%v] %T %v: %v", i, x, x, err)
				}
			}
		}

		if objs, err = ir.LinkMain(objs); err != nil {
			t.Fatal(match, err)
		}

		b.Reset()
		for i, v := range objs {
			switch x := v.(type) {
			case *ir.DataDefinition:
				fmt.Fprintf(&b, "# [%v]: %T %v %v\n", i, x, x.ObjectBase, x.Value)
			case *ir.FunctionDefinition:
				fmt.Fprintf(&b, "# [%v]: %T %v %v\n", i, x, x.ObjectBase, x.Arguments)
				for i, v := range x.Body {
					fmt.Fprintf(&b, "%#05x\t%v\n", i, v)
				}
			default:
				t.Fatalf("[%v] %T %v", i, x, x)
			}
		}
		t.Logf("ir.LinkMain: %v objects\n%s", len(objs), b.Bytes())
		for i, v := range objs {
			if err := v.Verify(); err != nil {
				t.Fatalf("[%v] %v: %v", i, v, err)
			}
		}

		bin, err := virtual.Load(modelName, objs)
		if err != nil {
			t.Fatal(match, err)
		}

		s := virtual.DumpCodeStr(bin.Code, 0)
		t.Logf(
			"virtual.Load: code %#05x, text %#05x, data %05x, bss %#05x, functions %v, lines %v\n%s",
			len(bin.Code), len(bin.Text), len(bin.Data), bin.BSS, len(bin.Functions), len(bin.Lines), s.Bytes(),
		)
		s.Close()

		var stdin, stdout, stderr bytes.Buffer
		func() {
			defer func() {
				if err := recover(); err != nil {
					t.Fatalf("PANIC: %s", err)
				}
			}()

			var args []string
			switch filepath.Base(match) {
			case "31_args.c":
				args = []string{"./test", "-", "arg1", "arg2", "arg3", "arg4"}
			case "32_led.c":
				t.Fatal("TODO")
			default:
				args = []string{match}
			}
			es, err := virtual.Exec(bin, args, &stdin, &stdout, &stderr, 1<<16, 1<<16)
			if es != 0 || err != nil {
				t.Fatalf("exit status %v\n%s", es, err)
			}
		}()

		expect := match[:len(match)-len(filepath.Ext(match))] + ".expect"
		if _, err := os.Stat(expect); err != nil {
			if os.IsNotExist(err) {
				continue
			}

			t.Fatal(err)
		}

		buf, err := ioutil.ReadFile(expect)
		if err != nil {
			t.Fatal(err)
		}

		if g, e := stdout.Bytes(), buf; !bytes.Equal(g, e) {
			t.Fatalf("==== %v\n==== got\n%s==== exp\n%s", match, g, e)
			continue
		}

		t.Logf("%s: OK\n%s", match, bytes.TrimRight(stdout.Bytes(), "\n\t "))
	}
}
