// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package ccir

import (
	"bytes"
	"encoding/hex"
	"flag"
	"fmt"
	"go/scanner"
	"go/token"
	"io/ioutil"
	"os"
	"path"
	"path/filepath"
	"runtime"
	"runtime/debug"
	"strings"
	"testing"

	"github.com/cznic/cc"
	"github.com/cznic/internal/buffer"
	"github.com/cznic/ir"
	"github.com/cznic/mathutil"
	"github.com/cznic/strutil"
	"github.com/cznic/virtual"
	"github.com/cznic/xc"
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

	cpp = flag.Bool("cpp", false, "")
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

func parse(src []string, opts ...cc.Opt) (_ string, _ *cc.TranslationUnit, err error) {
	defer func() {
		if e := recover(); e != nil && err == nil {
			err = fmt.Errorf("PANIC: %v\n%s", e, debug.Stack())
		}
	}()

	modelName := fmt.Sprint(mathutil.UintPtrBits)
	model, err := Model(modelName)
	if err != nil {
		return "", nil, err
	}

	ast, err := cc.Parse(fmt.Sprintf(`
#define __STDC_HOSTED__ 1
#define __STDC_VERSION__ 199901L
#define __STDC__ 1
#define __MODEL_%s__

#define NO_TRAMPOLINES 1
#define __FUNCTION__ __func__
#define __SIZE_TYPE__ unsigned long
#define __attribute__(x)
#define __builtin_memset(s, c, n) memset(s, c, n)
#define __complex__ _Complex
#define __restrict restrict

#include <string.h>
#include <wchar.h>
`, strings.ToUpper(modelName)),
		src,
		model,
		opts...,
	)
	return modelName, ast, err
}

func expect(t *testing.T, dir string, skip func(string) bool, hook func(string, string) []string, opts ...cc.Opt) {
	wd, err := os.Getwd()
	if err != nil {
		t.Fatal(err)
	}

	matches, err := filepath.Glob(filepath.Join(dir, "*.c"))
	if err != nil {
		t.Fatal(err)
	}

	seq := 0
	okSeq := 0
	opts0 := opts
	for _, match := range matches {
		if skip(match) {
			t.Logf("%s: skipped", match)
			continue
		}

		seq++
		var lpos token.Position
		var cppb buffer.Bytes
		if *cpp {
			opts = append(opts0, cc.Cpp(func(toks []xc.Token) {
				if len(toks) != 0 {
					p := toks[0].Position()
					if p.Filename != lpos.Filename {
						fmt.Fprintf(&cppb, "# %d %q\n", p.Line, p.Filename)
					}
					lpos = p
				}
				for _, v := range toks {
					cppb.WriteString(cc.TokSrc(v))
				}
				cppb.WriteByte('\n')
			}))
		}
		modelName, ast, err := parse([]string{crt0Path, match}, opts...)
		if err != nil {
			t.Fatal(match, errStr(err))
		}

		if cppb.Len() != 0 {
			t.Logf("\n%s", cppb.Bytes())
			cppb.Close()
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

		bin, err := virtual.LoadMain(modelName, objs)
		if err != nil {
			t.Fatal(match, err)
		}

		s := virtual.DumpCodeStr(bin.Code, 0)
		t.Logf(
			"virtual.LoadMain: code %#05x, text %#05x, data %05x, bss %#05x, functions %v, lines %v\n%s",
			len(bin.Code)*2*mathutil.IntBits/8, len(bin.Text), len(bin.Data), bin.BSS, len(bin.Functions), len(bin.Lines), s.Bytes(),
		)
		s.Close()
		if len(bin.Text) != 0 {
			t.Logf("Text segment\n%s", hex.Dump(bin.Text))
		}
		if len(bin.Data) != 0 {
			t.Logf("Data segment\n%s", hex.Dump(bin.Data))
		}
		if len(bin.TSRelative) != 0 {
			t.Logf("TS relative bitvector\n%s", hex.Dump(bin.TSRelative))
		}
		if len(bin.DSRelative) != 0 {
			t.Logf("DS relative bitvector\n%s", hex.Dump(bin.DSRelative))
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
				t.Logf("%s: OK #%v\nexit status 0, no respective .expect file exists", match, seq)
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

		okSeq++
		t.Logf("%s: OK #%v\n%s", match, okSeq, bytes.TrimRight(stdout.Bytes(), "\n\t "))
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
	expect(
		t,
		dir,
		func(string) bool { return false },
		func(wd, match string) []string {
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
	blacklist := map[string]struct{}{
		"20000703-1.c": {}, // ({ ... });
		"20000917-1.c": {}, // ({ ... });
		"20001009-2.c": {}, // asm
		"20001203-2.c": {}, // ({ ... });
		"20010122-1.c": {}, // alloca
		"20010209-1.c": {}, // nested fn
		"20010605-1.c": {}, // nested fn
		"20010605-2.c": {}, // __real__
		"20010904-1.c": {}, // __attribute__((aligned(32)))
		"20010904-2.c": {}, // __attribute__((aligned(32)))
	}
	wd, err := os.Getwd()
	if err != nil {
		t.Fatal(err)
	}

	testdata, err := filepath.Rel(wd, ccTestdata)
	if err != nil {
		t.Fatal(err)
	}

	dir := filepath.Join(testdata, filepath.FromSlash("gcc-6.3.0/gcc/testsuite/gcc.c-torture/execute/"))
	expect(
		t,
		dir,
		func(match string) bool {
			_, ok := blacklist[filepath.Base(match)]
			return ok
		},
		func(wd, match string) []string {
			return []string{match}
		},
		cc.AllowCompatibleTypedefRedefinitions(),
		cc.EnableAlignOf(),
		cc.EnableAlternateKeywords(),
		cc.EnableDefineOmitCommaBeforeDDD(),
		cc.EnableEmptyStructs(),
		cc.EnableImplicitFuncDef(),
		cc.EnableOmitFuncRetType(),
		cc.ErrLimit(-1),
		cc.SysIncludePaths([]string{"testdata/include/"}),
	)
}
