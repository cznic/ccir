// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package ccir

import (
	"bytes"
	"encoding/hex"
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

func expect(t *testing.T, dir string, hook func(string, string) []string, opts ...cc.Opt) {
	wd, err := os.Getwd()
	if err != nil {
		t.Fatal(err)
	}

	matches, err := filepath.Glob(filepath.Join(dir, "*.c"))
	if err != nil {
		t.Fatal(err)
	}

	for _, match := range matches {
		modelName, ast, err := parse([]string{crt0Path, match}, opts...)
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
				t.Fatalf("[%v]: %v", i, err)
			}
		}

		bin, err := virtual.Load(modelName, objs)
		if err != nil {
			t.Fatal(match, err)
		}

		s := virtual.DumpCodeStr(bin.Code, 0)
		t.Logf(
			"virtual.Load: code %#05x, text %#05x, data %05x, bss %#05x, functions %v, lines %v\n%s",
			len(bin.Code)*2*mathutil.IntBits/8, len(bin.Text), len(bin.Data), bin.BSS, len(bin.Functions), len(bin.Lines), s.Bytes(),
		)
		s.Close()
		if len(bin.Text) != 0 {
			t.Logf("Text segment\n%s", hex.Dump(bin.Text))
		}
		if len(bin.Data) != 0 {
			t.Logf("Data segment\n%s", hex.Dump(bin.Data))
		}

		var stdin, stdout, stderr bytes.Buffer
		func() {
			vwd, err := ioutil.TempDir("", "ccir-test-tcc-")
			if err != nil {
				t.Fatal(err)
			}

			if err := os.Chdir(vwd); err != nil {
				t.Fatal(err)
			}

			defer func() {
				os.Chdir(wd)
				os.RemoveAll(vwd)
				if err := recover(); err != nil {
					t.Fatalf("PANIC: %s", err)
				}
			}()

			args := hook(vwd, match)
			es, err := virtual.Exec(bin, args, &stdin, &stdout, &stderr, 1<<16, 1<<16)
			if es != 0 || err != nil {
				if b := stdout.Bytes(); b != nil {
					t.Logf("stdout:\n%s", b)
				}
				if b := stderr.Bytes(); b != nil {
					t.Logf("stderr:\n%s", b)
				}
				t.Fatalf("exit status %v, err %v", es, err)
			}
		}()

		expect := match[:len(match)-len(filepath.Ext(match))] + ".expect"
		if _, err := os.Stat(expect); err != nil {
			if os.IsNotExist(err) {
				if b := stdout.Bytes(); b != nil {
					t.Logf("stdout:\n%s", b)
				}
				if b := stderr.Bytes(); b != nil {
					t.Logf("stderr:\n%s", b)
				}
				t.Logf("%s: exit status 0, no respective .expect file exists", match)
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
	expect(t, dir, func(wd, match string) []string {
		switch filepath.Base(match) {
		case "31_args.c":
			return []string{"./test", "-", "arg1", "arg2", "arg3", "arg4"}
		case "46_grep.c":
			ioutil.WriteFile(filepath.Join(wd, "test"), []byte("abc\ndef\nghi\n"), 0600)
			return []string{"./grep", ".", "test"}
		default:
			return []string{match}
		}
	},
		cc.EnableDefineOmitCommaBeforeDDD(),
		cc.ErrLimit(-1),
		cc.SysIncludePaths([]string{"testdata/include/"}),
	)
}

func TestGCCExec(t *testing.T) {
	wd, err := os.Getwd()
	if err != nil {
		t.Fatal(err)
	}

	testdata, err := filepath.Rel(wd, ccTestdata)
	if err != nil {
		t.Fatal(err)
	}

	dir := filepath.Join(testdata, filepath.FromSlash("gcc-6.3.0/gcc/testsuite/gcc.c-torture/execute/"))
	expect(t, dir, func(wd, match string) []string { return []string{match} },
		cc.EnableOmitFuncRetType(),
		cc.ErrLimit(-1),
		cc.SysIncludePaths([]string{"testdata/include/"}),
	)
}
