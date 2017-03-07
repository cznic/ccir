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
	"regexp"
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

	cpp    = flag.Bool("cpp", false, "")
	filter = flag.String("re", "", "")
	trace  = flag.Bool("trc", false, "")
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
	if *trace {
		fmt.Println(src)
	}

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
#define __CHAR_BIT__ 8
#define __FUNCTION__ __func__
#define __INT16_TYPE__ short
#define __INT32_TYPE__ int
#define __LONG_LONG_MAX__ LLONG_MAX
#define __PTRDIFF_TYPE__ long
#define __SIZEOF_INT__ 4
#define __SIZE_TYPE__ unsigned long
#define __UINT32_TYPE__ unsigned
#define __attribute__(x)
#define __builtin_abort abort
#define __builtin_expect(exp, c) (exp)
#define __builtin_malloc(n) malloc(n)
#define __builtin_memcmp memcmp
#define __builtin_memcpy(dest, src, n) memcpy(dest, src, n)
#define __builtin_memset(s, c, n) memset(s, c, n)
#define __builtin_printf(...) printf(__VA_ARGS__)
#define __builtin_strcmp(s1, s2) strcmp(s1, s2)
#define __builtin_strcpy(dest, src) strcpy(dest, src)
#define __builtin_strlen(s) strlen(s)
#define __builtin_trap abort
#define __builtin_va_list char*
#define __complex _Complex
#define __complex__ _Complex
#define __const const
#define __extension__
#define __inline inline
#define __restrict restrict

#if defined __MODEL_32__
#define __SIZEOF_LONG__ 4
#define __SIZEOF_POINTER__ 4
#elif defined __MODEL_64__
#define __SIZEOF_LONG__ 8
#define __SIZEOF_POINTER__ 8
#else
#error
#endif

#include <ctype.h>
#include <limits.h>
#include <math.h>
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
						//fmt.Printf("# %d %q\n", p.Line, p.Filename)
						fmt.Fprintf(&cppb, "# %d %q\n", p.Line, p.Filename)
					}
					lpos = p
				}
				for _, v := range toks {
					//fmt.Print(cc.TokSrc(v))
					cppb.WriteString(cc.TokSrc(v))
				}
				//fmt.Println()
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
			es, err := virtual.Exec(bin, args, &stdin, &stdout, &stderr, 1<<20, 1<<20)
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

	var re *regexp.Regexp
	if s := *filter; s != "" {
		re = regexp.MustCompile(s)
	}

	dir := filepath.Join(testdata, filepath.FromSlash("tcc-0.9.26/tests/tests2/"))
	expect(
		t,
		dir,
		func(match string) bool {
			if re != nil && !re.MatchString(filepath.Base(match)) {
				return true
			}

			return false
		},
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
		"20000703-1.c":      {}, // ({ ... });
		"20000914-1.c":      {}, //TODO
		"20000917-1.c":      {}, // ({ ... });
		"20001009-2.c":      {}, // asm
		"20001203-2.c":      {}, // ({ ... });
		"20010122-1.c":      {}, // alloca
		"20010209-1.c":      {}, // nested fn
		"20010605-1.c":      {}, // nested fn
		"20010605-2.c":      {}, // __real__
		"20010904-1.c":      {}, // __attribute__((aligned(32)))
		"20010904-2.c":      {}, // __attribute__((aligned(32)))
		"20020107-1.c":      {}, // asm
		"20020206-1.c":      {}, // ({ ... });
		"20020314-1.c":      {}, // alloca
		"20020320-1.c":      {}, // ({ ... });
		"20020411-1.c":      {}, // __real__
		"20020412-1.c":      {}, // VLA in struct
		"20021113-1.c":      {}, // alloca
		"20021127-1.c":      {}, // https://goo.gl/XDxJEL
		"20030222-1.c":      {}, // asm
		"20030323-1.c":      {}, // __builtin_return_address
		"20030330-1.c":      {}, // __builtin_constant_p
		"20030408-1.c":      {}, // const struct foo X = { a : 'A', c : 'C', e : 'E', g : 'G', i : 'I' };
		"20030501-1.c":      {}, // nested fn
		"20030714-1.c":      {}, // implicit selector (TODO check the specs)
		"20030811-1.c":      {}, // __builtin_return_address
		"20030910-1.c":      {}, // __real
		"20031003-1.c":      {}, //TODO https://github.com/golang/go/issues/19405
		"20040223-1.c":      {}, // alloca
		"20040302-1.c":      {}, // &&label
		"20040308-1.c":      {}, // VLA in struct
		"20040411-1.c":      {}, //TODO VLA
		"20040423-1.c":      {}, //TODO VLA
		"20040520-1.c":      {}, // nested fn
		"20040709-1.c":      {}, // __builtin_classify_type
		"20040709-2.c":      {}, // __builtin_classify_type
		"20040811-1.c":      {}, //TODO VLA
		"20041124-1.c":      {}, // _Complex integer;
		"20041201-1.c":      {}, // _Complex integer;
		"20041214-1.c":      {}, // &&label
		"20041218-2.c":      {}, //TODO VLA
		"20050121-1.c":      {}, // _Complex integer;
		"20050203-1.c":      {}, // asm
		"20050316-1.c":      {}, // __attribute__ ((vector_size (x)))
		"20050316-2.c":      {}, // __attribute__ ((vector_size (x)))
		"20050316-3.c":      {}, // __attribute__ ((vector_size (x)))
		"20050604-1.c":      {}, // __attribute__ ((vector_size (x)))
		"20050607-1.c":      {}, // __attribute__ ((vector_size (x)))
		"20050613-1.c":      {}, //TODO { .i.j = expr }
		"20050929-1.c":      {}, //TODO struct C e = { &(struct B) { &(struct A) { 1, 2 }, &(struct A) { 3, 4 } }, &(struct A) { 5, 6 } };
		"20051110-1.c":      {}, //TODO
		"20051110-2.c":      {}, //TODO
		"20060910-1.c":      {}, //TODO
		"20060930-2.c":      {}, //TODO
		"20061031-1.c":      {}, // asm
		"20061220-1.c":      {}, // nested fn
		"20070614-1.c":      {}, //TODO complex literal not handled?
		"20070824-1.c":      {}, // __builtin_alloca
		"20070919-1.c":      {}, // VLA in struct
		"20071029-1.c":      {}, //TODO
		"20071210-1.c":      {}, // &&label
		"20071211-1.c":      {}, // asm
		"20071219-1.c":      {}, //TODO
		"20071220-1.c":      {}, // asm
		"20071220-2.c":      {}, // asm
		"20080122-1.c":      {}, // asm
		"20080424-1.c":      {}, //TODO internal error
		"20080502-1.c":      {}, //TODO signbit
		"20080519-1.c":      {}, //TODO
		"20080522-1.c":      {}, //TODO
		"20081117-1.c":      {}, //TODO
		"20090113-1.c":      {}, //TODO
		"20090219-1.c":      {}, // nested fn
		"20090814-1.c":      {}, //TODO
		"20101011-1.c":      {}, //TODO
		"20101025-1.c":      {}, //TODO
		"20120919-1.c":      {}, //TODO
		"920302-1.c":        {}, // &&label
		"920415-1.c":        {}, // &&label
		"920428-1.c":        {}, //TODO
		"920429-1.c":        {}, //TODO
		"920501-3.c":        {}, // &&label
		"920501-4.c":        {}, // &&label
		"920501-5.c":        {}, // &&label
		"920501-6.c":        {}, //TODO
		"920603-1.c":        {}, //TODO
		"920612-2.c":        {}, // nested fn
		"920721-3.c":        {}, // nested fn
		"920721-4.c":        {}, // &&label
		"920728-1.c":        {}, //TODO
		"920731-1.c":        {}, //TODO
		"920909-1.c":        {}, //TODO
		"920929-1.c":        {}, //TODO VLA
		"921017-1.c":        {}, //TODO
		"921019-1.c":        {}, //TODO
		"921110-1.c":        {}, //TODO
		"921124-1.c":        {}, //TODO
		"930406-1.c":        {}, // ({ ... });
		"930429-2.c":        {}, //TODO
		"930513-1.c":        {}, //TODO
		"930513-2.c":        {}, //TODO
		"930603-1.c":        {}, //TODO
		"930603-3.c":        {}, //TODO
		"930608-1.c":        {}, //TODO
		"930622-1.c":        {}, //TODO
		"930628-1.c":        {}, //TODO
		"930719-1.c":        {}, //TODO
		"930930-2.c":        {}, //TODO
		"931009-1.c":        {}, //TODO
		"931228-1.c":        {}, //TODO
		"941202-1.c":        {}, //TODO
		"950512-1.c":        {}, //TODO
		"950628-1.c":        {}, //TODO
		"950906-1.c":        {}, // ({ ... });
		"950929-1.c":        {}, //TODO
		"951003-1.c":        {}, //TODO
		"960116-1.c":        {}, //TODO
		"960218-1.c":        {}, //TODO
		"960301-1.c":        {}, //TODO
		"960312-1.c":        {}, //TODO
		"960405-1.c":        {}, //TODO
		"960416-1.c":        {}, //TODO
		"960512-1.c":        {}, //TODO
		"961112-1.c":        {}, //TODO
		"970217-1.c":        {}, //TODO
		"980223.c":          {}, //TODO
		"980506-3.c":        {}, //TODO
		"980526-1.c":        {}, // &&label
		"980605-1.c":        {}, //TODO
		"990130-1.c":        {}, // asm
		"990208-1.c":        {}, // &&label
		"990413-2.c":        {}, // asm
		"990524-1.c":        {}, //TODO
		"991030-1.c":        {}, //TODO
		"991228-1.c":        {}, // __extension__ union { double d; int i[2]; } u = { d: -0.25 };
		"alias-2.c":         {}, // extern int b[10] __attribute__ ((alias("a")));
		"alias-3.c":         {}, // extern int b[10] __attribute__ ((alias("a")));
		"alias-4.c":         {}, // extern int b[10] __attribute__ ((alias("a")));
		"align-3.c":         {}, // __alignof__(non-type-name)
		"align-nest.c":      {}, // VLA in struct
		"alloca-1.c":        {}, // __builtin_alloca
		"anon-1.c":          {}, //TODO
		"bcp-1.c":           {}, // __builtin_constant_p
		"bf-sign-2.c":       {}, //TODO
		"bitfld-1.c":        {}, //TODO
		"bitfld-3.c":        {}, //TODO
		"bitfld-5.c":        {}, // asm
		"bitfld-6.c":        {}, //TODO
		"bitfld-7.c":        {}, //TODO
		"bswap-1.c":         {}, // __builtin_bswap64
		"bswap-2.c":         {}, //TODO
		"built-in-setjmp.c": {}, //TODO
	}
	wd, err := os.Getwd()
	if err != nil {
		t.Fatal(err)
	}

	testdata, err := filepath.Rel(wd, ccTestdata)
	if err != nil {
		t.Fatal(err)
	}

	var re *regexp.Regexp
	if s := *filter; s != "" {
		re = regexp.MustCompile(s)
	}

	dir := filepath.Join(testdata, filepath.FromSlash("gcc-6.3.0/gcc/testsuite/gcc.c-torture/execute/"))
	expect(
		t,
		dir,
		func(match string) bool {
			base := filepath.Base(match)
			_, skip := blacklist[base]
			if re != nil && !re.MatchString(base) {
				skip = true
			}
			return skip
		},
		func(wd, match string) []string {
			return []string{match}
		},
		cc.AllowCompatibleTypedefRedefinitions(),
		cc.EnableAlignOf(),
		cc.EnableAlternateKeywords(),
		cc.EnableAnonymousStructFields(),
		cc.EnableDefineOmitCommaBeforeDDD(),
		cc.EnableEmptyDeclarations(),
		cc.EnableEmptyStructs(),
		cc.EnableImplicitFuncDef(),
		cc.EnableOmitFuncRetType(),
		cc.EnableTypeOf(),
		cc.EnableWideBitFieldTypes(),
		cc.ErrLimit(-1),
		cc.SysIncludePaths([]string{"testdata/include/"}),
	)
}
