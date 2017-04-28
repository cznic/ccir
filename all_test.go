// Copyright 2017 The CCIR Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package ccir

import (
	"bytes"
	"compress/gzip"
	"encoding/gob"
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
	"time"

	"github.com/cznic/cc"
	"github.com/cznic/internal/buffer"
	"github.com/cznic/ir"
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
	isTesting = true
	flag.BoolVar(&Testing, "testing", false, "")
	flag.BoolVar(&ir.Testing, "irTesting", false, "")
	flag.BoolVar(&virtual.Testing, "virtualTesting", false, "")
}

// ============================================================================

var (
	cpp      = flag.Bool("cpp", false, "")
	errLimit = flag.Int("errlimit", 10, "")
	filter   = flag.String("re", "", "")
	ndebug   = flag.Bool("ndebug", false, "")
	noexec   = flag.Bool("noexec", false, "")
	oLog     = flag.Bool("log", false, "")
	trace    = flag.Bool("trc", false, "")
	yydebug  = flag.Int("yydebug", 0, "")
)

func errStr(err error) string {
	switch x := err.(type) {
	case scanner.ErrorList:
		if len(x) != 1 {
			x.RemoveMultiples()
		}
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

func parse(src []string, opts ...cc.Opt) (_ *cc.TranslationUnit, err error) {
	defer func() {
		if e := recover(); e != nil && err == nil {
			err = fmt.Errorf("cc.Parse: PANIC: %v\n%s", e, debug.Stack())
		}
	}()

	model, err := NewModel()
	if err != nil {
		return nil, err
	}

	ast, err := cc.Parse(fmt.Sprintf(`
#define __arch__ %s
#define __os__ %s
#include <builtin.h>

#define NO_TRAMPOLINES 1
`, runtime.GOARCH, runtime.GOOS),
		src,
		model,
		opts...,
	)
	if err != nil {
		return nil, fmt.Errorf("cc.Parse: %v", errStr(err))
	}

	return ast, nil
}

func expect1(wd, match string, hook func(string, string) []string, opts ...cc.Opt) (log buffer.Bytes, exitStatus int, err error) {
	var lpos token.Position
	if *cpp {
		opts = append(opts, cc.Cpp(func(toks []xc.Token) {
			if len(toks) != 0 {
				p := toks[0].Position()
				if p.Filename != lpos.Filename {
					fmt.Fprintf(&log, "# %d %q\n", p.Line, p.Filename)
				}
				lpos = p
			}
			for _, v := range toks {
				log.WriteString(cc.TokSrc(v))
			}
			log.WriteByte('\n')
		}))
	}
	if n := *yydebug; n != 0 {
		opts = append(opts, cc.YyDebug(n))
	}
	ast, err := parse([]string{CRT0Path, match}, opts...)
	if err != nil {
		return log, -1, err
	}

	objs, err := New(ast)
	if err != nil {
		return log, -1, fmt.Errorf("New: %v", err)
	}

	fmt.Fprintf(&log, "# ccir.New\n")
	for i, v := range objs {
		switch x := v.(type) {
		case *ir.DataDefinition:
			fmt.Fprintf(&log, "# [%v]: %T %v %v\n", i, x, x.ObjectBase, x.Value)
		case *ir.FunctionDefinition:
			fmt.Fprintf(&log, "# [%v]: %T %v %v\n", i, x, x.ObjectBase, x.Arguments)
			for i, v := range x.Body {
				fmt.Fprintf(&log, "%#05x\t%v\n", i, v)
			}
		default:
			return log, -1, fmt.Errorf("[%v] %T %v", i, x, x)
		}
	}
	for i, v := range objs {
		if err := v.Verify(); err != nil {
			switch x := v.(type) {
			case *ir.FunctionDefinition:
				fmt.Fprintf(&log, "# [%v, err]: %T %v %v\n", i, x, x.ObjectBase, x.Arguments)
				for i, v := range x.Body {
					fmt.Fprintf(&log, "%#05x\t%v\n", i, v)
				}
				return log, -1, fmt.Errorf("# [%v, err]: Verify (A): %v", i, err)
			default:
				return log, -1, fmt.Errorf("[%v, err]: %T %v: %v", i, x, x, err)
			}
		}
	}

	if objs, err = ir.LinkMain(objs); err != nil {
		return log, -1, fmt.Errorf("ir.LinkMain: %v", err)
	}

	fmt.Fprintf(&log, "# ir.LinkMain\n")
	for i, v := range objs {
		switch x := v.(type) {
		case *ir.DataDefinition:
			fmt.Fprintf(&log, "# [%v]: %T %v %v\n", i, x, x.ObjectBase, x.Value)
		case *ir.FunctionDefinition:
			fmt.Fprintf(&log, "# [%v]: %T %v %v\n", i, x, x.ObjectBase, x.Arguments)
			for i, v := range x.Body {
				fmt.Fprintf(&log, "%#05x\t%v\n", i, v)
			}
		default:
			return log, -1, fmt.Errorf("[%v]: %T %v", i, x, x)
		}
	}
	for i, v := range objs {
		if err := v.Verify(); err != nil {
			return log, -1, fmt.Errorf("# [%v, err]: Verify (B): %v", i, err)
		}
	}

	bin, err := virtual.LoadMain(objs)
	if err != nil {
		return log, -1, fmt.Errorf("virtual.LoadMain: %v", err)
	}

	var gz bytes.Buffer
	zw := gzip.NewWriter(&gz)
	enc := gob.NewEncoder(zw)
	if err := enc.Encode(bin); err != nil {
		return log, -1, fmt.Errorf("gob encode: %v", err)
	}

	if err := zw.Close(); err != nil {
		return log, -1, fmt.Errorf("gzip close: %v", err)
	}

	s := virtual.DumpCodeStr(bin.Code, 0, bin.Functions, bin.Lines)
	fmt.Fprintf(&log, "%s: virtual.LoadMain: code %#05x, text %#05x, data %#05x, bss %#05x, pc2func %v, pc2line %v, gz %v\n%s\n",
		match, len(bin.Code), len(bin.Text), len(bin.Data), bin.BSS, len(bin.Functions), len(bin.Lines), len(gz.Bytes()), s.Bytes(),
	)
	s.Close()
	if len(bin.Text) != 0 {
		fmt.Fprintf(&log, "Text segment\n%s\n", hex.Dump(bin.Text))
	}
	if len(bin.Data) != 0 {
		fmt.Fprintf(&log, "Data segment\n%s\n", hex.Dump(bin.Data))
	}
	if len(bin.TSRelative) != 0 {
		fmt.Fprintf(&log, "TS relative bitvector\n%s\n", hex.Dump(bin.TSRelative))
	}
	if len(bin.DSRelative) != 0 {
		fmt.Fprintf(&log, "DS relative bitvector\n%s\n", hex.Dump(bin.DSRelative))
	}

	if *noexec {
		return log, 0, nil
	}

	var stdin bytes.Buffer
	var stdout, stderr buffer.Bytes

	defer func() {
		stdout.Close()
		stderr.Close()
	}()

	if err := func() (err error) {
		defer func() {
			if e := recover(); e != nil && err == nil {
				err = fmt.Errorf("virtual.Exec: PANIC: %v", e)
			}
		}()

		vwd, err := ioutil.TempDir("", "ccir-test-")
		if err != nil {
			return err
		}

		if err := os.Chdir(vwd); err != nil {
			return err
		}

		defer func() {
			os.Chdir(wd)
			os.RemoveAll(vwd)
		}()

		args := hook(vwd, match)
		if exitStatus, err = virtual.Exec(bin, args, &stdin, &stdout, &stderr, 1<<20, 1<<20, wd); exitStatus != 0 || err != nil {
			if b := stdout.Bytes(); b != nil {
				fmt.Fprintf(&log, "stdout:\n%s\n", b)
			}
			if b := stderr.Bytes(); b != nil {
				fmt.Fprintf(&log, "stderr:\n%s\n", b)
			}
			return fmt.Errorf("virtual.Exec: exit status %v, err %v", exitStatus, err)
		}

		return nil
	}(); err != nil {
		return log, exitStatus, err
	}

	if b := stdout.Bytes(); b != nil {
		fmt.Fprintf(&log, "stdout:\n%s\n", b)
	}
	if b := stderr.Bytes(); b != nil {
		fmt.Fprintf(&log, "stderr:\n%s\n", b)
	}

	expect := match[:len(match)-len(filepath.Ext(match))] + ".expect"
	if _, err := os.Stat(expect); err != nil {
		if !os.IsNotExist(err) {
			return log, 0, err
		}

		return log, 0, nil
	}

	buf, err := ioutil.ReadFile(expect)
	if err != nil {
		return log, 0, err
	}

	if g, e := stdout.Bytes(), buf; !bytes.Equal(g, e) {
		return log, 0, fmt.Errorf("==== %v\n==== got\n%s==== exp\n%s", match, g, e)
	}
	return log, 0, nil
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
	for _, match := range matches {
		if skip(match) {
			continue
		}

		if *trace {
			fmt.Println(match)
		}
		seq++
		doLog := *oLog
		log, exitStatus, err := expect1(wd, match, hook, opts...)
		switch {
		case exitStatus <= 0 && err == nil:
			okSeq++
		default:
			//dbg("%v\n%v", match, err)
			if seq-okSeq == 1 {
				t.Logf("%s: FAIL\n%s\n%s", match, errStr(err), log.Bytes())
				doLog = false
			}
		}
		if doLog {
			t.Logf("%s:\n%s", match, log.Bytes())
		}
		log.Close()
	}
	t.Logf("%v/%v ok", okSeq, seq)
	if okSeq != seq {
		t.Errorf("failures: %v", seq-okSeq)
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
				return []string{"./grep", "[ea]", "test"}
			default:
				return []string{match}
			}
		},
		cc.AllowCompatibleTypedefRedefinitions(),
		cc.EnableAnonymousStructFields(),
		cc.EnableDefineOmitCommaBeforeDDD(),
		cc.EnableImplicitFuncDef(),
		cc.ErrLimit(-1),
		cc.SysIncludePaths([]string{LibcIncludePath}),
	)
}

func TestGCCExec(t *testing.T) {
	blacklist := map[string]struct{}{
		// VLA struct field.
		"20020412-1.c": {},
		"20040308-1.c": {},
		"align-nest.c": {},
		"pr41935.c":    {},

		// Nested function.
		"20010209-1.c":   {},
		"20010605-1.c":   {},
		"20030501-1.c":   {},
		"20040520-1.c":   {},
		"20061220-1.c":   {},
		"20090219-1.c":   {},
		"920612-2.c":     {},
		"921017-1.c":     {},
		"nest-align-1.c": {},
		"nest-stdar-1.c": {},
		"nestfunc-7.c":   {},
		"pr22061-3.c":    {},
		"pr22061-4.c":    {},
		"pr71494.c":      {},

		// __real__, complex integers and and friends.
		"20010605-2.c": {},
		"20020411-1.c": {},
		"20030910-1.c": {},
		"20041124-1.c": {},
		"20041201-1.c": {},
		"20050121-1.c": {},
		"complex-1.c":  {},
		"complex-6.c":  {},
		"pr38151.c":    {},
		"pr38969.c":    {},
		"pr56837.c":    {},

		// Depends on __attribute__((aligned(N)))
		"20010904-1.c": {},
		"20010904-2.c": {},
		"align-3.c":    {},
		"pr23467.c":    {},

		// Depends on __attribute__ ((vector_size (N)))
		"20050316-1.c":   {},
		"20050316-2.c":   {},
		"20050316-3.c":   {},
		"20050604-1.c":   {},
		"20050607-1.c":   {},
		"pr23135.c":      {},
		"pr53645-2.c":    {},
		"pr53645.c":      {},
		"pr60960.c":      {},
		"pr65427.c":      {},
		"pr71626-1.c":    {},
		"pr71626-2.c":    {},
		"scal-to-vec1.c": {},
		"scal-to-vec2.c": {},
		"scal-to-vec3.c": {},
		"simd-1.c":       {},
		"simd-2.c":       {},
		"simd-4.c":       {},
		"simd-5.c":       {},
		"simd-6.c":       {},

		// https://goo.gl/XDxJEL
		"20021127-1.c": {},

		// asm
		"20001009-2.c": {},
		"20020107-1.c": {},
		"20030222-1.c": {},
		"20071211-1.c": {},
		"20071220-1.c": {},
		"20071220-2.c": {},
		"960312-1.c":   {},
		"960830-1.c":   {},
		"990130-1.c":   {},
		"990413-2.c":   {},
		"pr38533.c":    {},
		"pr40022.c":    {},
		"pr40657.c":    {},
		"pr41239.c":    {},
		"pr43385.c":    {},
		"pr43560.c":    {},
		"pr45695.c":    {},
		"pr46309.c":    {},
		"pr49279.c":    {},
		"pr49390.c":    {},
		"pr51877.c":    {},
		"pr51933.c":    {},
		"pr52286.c":    {},
		"pr56205.c":    {},
		"pr56866.c":    {},
		"pr56982.c":    {},
		"pr57344-1.c":  {},
		"pr57344-2.c":  {},
		"pr57344-3.c":  {},
		"pr57344-4.c":  {},
		"pr63641.c":    {},
		"pr65053-1.c":  {},
		"pr65053-2.c":  {},
		"pr65648.c":    {},
		"pr65956.c":    {},
		"pr68328.c":    {},
		"pr69320-2.c":  {},
		"stkalign.c":   {},

		// __label__
		"920415-1.c": {},
		"920721-4.c": {},
		"930406-1.c": {},
		"980526-1.c": {},
		"pr51447.c":  {},

		// attribute alias
		"alias-2.c": {},
		"alias-3.c": {},
		"alias-4.c": {},

		// _Alignas
		"pr68532.c": {},

		// Profiling
		"eeprof-1.c": {},

		// 6.5.16/4: The order of evaluation of the operands is unspecified.
		"pr58943.c": {},
	}
	todolist := map[string]struct{}{
		// long double constant out of range for double.
		"960405-1.c": {},

		// case range
		"pr34154.c": {},

		// VLA. Need to resolve https://github.com/cznic/cc/issues/91 first.
		"20040411-1.c":    {},
		"20040423-1.c":    {},
		"20040811-1.c":    {},
		"20041218-2.c":    {},
		"20070919-1.c":    {},
		"920929-1.c":      {},
		"970217-1.c":      {},
		"pr22061-1.c":     {},
		"pr43220.c":       {},
		"vla-dealloc-1.c": {},

		// Initializer
		"20050613-1.c":        {}, // struct B b = { .a.j = 5 };
		"20050929-1.c":        {}, // struct C e = { &(struct B) { &(struct A) { 1, 2 }, &(struct A) { 3, 4 } }, &(struct A) { 5, 6 } };
		"20071029-1.c":        {}, // t = (T) { { ++i, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
		"921019-1.c":          {}, // void *foo[]={(void *)&("X"[0])};
		"991228-1.c":          {}, // cc.Parse: ../cc/testdata/gcc-6.3.0/gcc/testsuite/gcc.c-torture/execute/991228-1.c:1:51: invalid designator for type double
		"compndlit-1.c":       {}, // x = (struct S) {b:0, a:0, c:({ struct S o = x; o.a == 1 ? 10 : 20;})};
		"const-addr-expr-1.c": {}, // int *Upgd_minor_ID = (int *) &((Upgrade_items + 1)->uaattrid);
		"pr22098-1.c":         {}, // b = (uintptr_t)(p = &(int []){0, 1, 2}[++a]);
		"pr22098-2.c":         {}, // b = (uintptr_t)(p = &(int []){0, 1, 2}[1]);
		"pr22098-3.c":         {}, // b = (uintptr_t)(p = &(int []){0, f(), 2}[1]);
		"pr33631.c":           {}, // struct { int c; pthread_mutex_t m; } r = { .m = 0 };
		"pr70460.c":           {}, // static int b[] = { &&lab1 - &&lab0, &&lab2 - &&lab0 };

		// signal.h
		"20101011-1.c": {},

		// mmap.h
		"loop-2f.c": {},
		"loop-2g.c": {},

		// &&label expr
		"comp-goto-1.c": {}, // # [100]: Verify (A): mismatched operand type, got int32, expected uint32; simulator_kernel:0x64: 	lsh             	uint32	; ../cc/testdata/gcc-6.3.0/gcc/testsuite/gcc.c-torture/execute/comp-goto-1.c:83:40

		// builtins
		"pr47237.c":       {}, // __builtin_apply, __builtin_apply_args
		"pr64006.c":       {}, // __builtin_mul_overflow
		"pr68381.c":       {}, // __builtin_mul_overflow
		"pr71554.c":       {}, // __builtin_mul_overflow
		"va-arg-pack-1.c": {}, // __builtin_va_arg_pack

		// long double
		"pr39228.c": {},

		// un-flatten (wips wrt cc.0506a942f3efa9b7a0a4b98dbe45bf7e8d06a542)
		"20030714-1.c": {}, // cc.Parse: ../cc/testdata/gcc-6.3.0/gcc/testsuite/gcc.c-torture/execute/20030714-1.c:102:11: assignment from incompatible type ('unsigned' = '<undefined>')
		"anon-1.c":     {}, // cc.Parse: ../cc/testdata/gcc-6.3.0/gcc/testsuite/gcc.c-torture/execute/anon-1.c:22:7: struct{int; ;} has no member named b
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
			if _, skip2 := todolist[base]; skip2 {
				skip = true
			}
			if re != nil {
				skip = !re.MatchString(base)
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
		cc.EnableAsm(),
		cc.EnableBuiltinClassifyType(),
		cc.EnableBuiltinConstantP(),
		cc.EnableComputedGotos(),
		cc.EnableDefineOmitCommaBeforeDDD(),
		cc.EnableEmptyDeclarations(),
		cc.EnableEmptyStructs(),
		cc.EnableImaginarySuffix(),
		cc.EnableImplicitFuncDef(),
		cc.EnableImplicitIntType(),
		cc.EnableLegacyDesignators(),
		cc.EnableNonConstStaticInitExpressions(),
		cc.EnableOmitConditionalOperand(),
		cc.EnableOmitFuncArgTypes(),
		cc.EnableOmitFuncRetType(),
		cc.EnableParenthesizedCompoundStatemen(),
		cc.EnableTypeOf(),
		cc.EnableUnsignedEnums(),
		cc.EnableWideBitFieldTypes(),
		cc.ErrLimit(-1),
		cc.SysIncludePaths([]string{LibcIncludePath}),
	)
}

type file struct {
	name string
	data []byte
}

func (f file) String() string { return fmt.Sprintf("%v %v", len(f.data), f.name) }

func exec(t *testing.T, bin *virtual.Binary, argv []string, inputFiles []file) (output []byte, resultFiles []file, duration time.Duration) {
	dir, err := ioutil.TempDir("", "ccir-test-")
	if err != nil {
		t.Fatal(err)
	}

	defer os.RemoveAll(dir)

	cwd, err := os.Getwd()
	if err != nil {
		t.Fatal(err)
	}

	defer os.Chdir(cwd)

	if err := os.Chdir(dir); err != nil {
		t.Fatal(err)
	}

	for _, v := range inputFiles {
		if err := ioutil.WriteFile(v.name, v.data, 0600); err != nil {
			t.Fatal(err)
		}
	}

	defer func() {
		if e := recover(); e != nil && err == nil {
			t.Fatal(fmt.Errorf("virtual.Exec: PANIC: %v", e))
		}
	}()

	var stdin, stdout, stderr bytes.Buffer
	t0 := time.Now()
	exitStatus, err := virtual.Exec(bin, argv, &stdin, &stdout, &stderr, 1<<25, 1<<20, cwd)
	duration = time.Since(t0)
	if err != nil {
		var log bytes.Buffer
		if b := stdout.Bytes(); b != nil {
			fmt.Fprintf(&log, "stdout:\n%s\n", b)
		}
		if b := stderr.Bytes(); b != nil {
			fmt.Fprintf(&log, "stderr:\n%s\n", b)
		}
		t.Fatalf("exit status %v, err %v\n%s", exitStatus, err, log.Bytes())
	}

	glob, err := filepath.Glob("*")
	if err != nil {
		t.Fatal(err)
	}

	for _, m := range glob {
		data, err := ioutil.ReadFile(m)
		if err != nil {
			t.Fatal(err)
		}

		resultFiles = append(resultFiles, file{m, data})
	}

	return bytes.TrimSpace(append(stdout.Bytes(), stderr.Bytes()...)), resultFiles, duration
}

func build(t *testing.T, predef string, tus [][]string, opts ...cc.Opt) *virtual.Binary {
	var log buffer.Bytes
	var lpos token.Position
	if *cpp {
		opts = append(opts, cc.Cpp(func(toks []xc.Token) {
			if len(toks) != 0 {
				p := toks[0].Position()
				if p.Filename != lpos.Filename {
					fmt.Fprintf(&log, "# %d %q\n", p.Line, p.Filename)
				}
				lpos = p
			}
			for _, v := range toks {
				log.WriteString(cc.TokSrc(v))
			}
			log.WriteByte('\n')
		}))
	}

	ndbg := ""
	if *ndebug {
		ndbg = "#define NDEBUG 1"
	}
	var build [][]ir.Object
	tus = append(tus, []string{CRT0Path})
	for _, src := range tus {
		model, err := NewModel()
		if err != nil {
			t.Fatal(err)
		}

		ast, err := cc.Parse(
			fmt.Sprintf(`
%s
#define __arch__ %s
#define __os__ %s
#include <builtin.h>
%s
`, ndbg, runtime.GOARCH, runtime.GOOS, predef),
			src,
			model,
			append([]cc.Opt{
				cc.AllowCompatibleTypedefRedefinitions(),
				cc.EnableImplicitFuncDef(),
				cc.EnableNonConstStaticInitExpressions(),
				cc.ErrLimit(*errLimit),
				cc.SysIncludePaths([]string{LibcIncludePath}),
			}, opts...)...,
		)
		if s := log.Bytes(); len(s) != 0 {
			t.Logf("\n%s", s)
			log.Close()
		}
		if err != nil {
			t.Fatal(errStr(err))
		}

		objs, err := New(ast)
		if err != nil {
			t.Fatal(err)
		}

		if *oLog {
			for i, v := range objs {
				switch x := v.(type) {
				case *ir.DataDefinition:
					fmt.Fprintf(&log, "# [%v]: %T %v %v\n", i, x, x.ObjectBase, x.Value)
				case *ir.FunctionDefinition:
					fmt.Fprintf(&log, "# [%v]: %T %v %v\n", i, x, x.ObjectBase, x.Arguments)
					for i, v := range x.Body {
						fmt.Fprintf(&log, "%#05x\t%v\n", i, v)
					}
				default:
					t.Fatalf("[%v]: %T %v: %v", i, x, x, err)
				}
			}
		}
		for i, v := range objs {
			if err := v.Verify(); err != nil {
				switch x := v.(type) {
				case *ir.FunctionDefinition:
					fmt.Fprintf(&log, "# [%v, err]: %T %v %v\n", i, x, x.ObjectBase, x.Arguments)
					for i, v := range x.Body {
						fmt.Fprintf(&log, "%#05x\t%v\n", i, v)
					}
					t.Fatalf("# [%v]: Verify (A): %v\n%s", i, err, log.Bytes())
				default:
					t.Fatalf("[%v]: %T %v: %v", i, x, x, err)
				}
			}
		}
		build = append(build, objs)
	}

	linked, err := ir.LinkMain(build...)
	if err != nil {
		t.Fatalf("ir.LinkMain: %s\n%s", err, log.Bytes())
	}

	for _, v := range linked {
		if err := v.Verify(); err != nil {
			t.Fatal(err)
		}
	}

	bin, err := virtual.LoadMain(linked)
	if err != nil {
		t.Fatal(err)
	}

	return bin
}

func findRepo(t *testing.T, s string) string {
	s = filepath.FromSlash(s)
	for _, v := range strings.Split(strutil.Gopath(), string(os.PathListSeparator)) {
		p := filepath.Join(v, "src", s)
		fi, err := os.Lstat(p)
		if err != nil {
			continue
		}

		if fi.IsDir() {
			wd, err := os.Getwd()
			if err != nil {
				t.Fatal(err)
			}

			if p, err = filepath.Rel(wd, p); err != nil {
				t.Fatal(err)
			}

			return p
		}
	}
	return ""
}

func TestSelfie(t *testing.T) {
	const repo = "github.com/cksystemsteaching/selfie"
	pth := findRepo(t, repo)
	if pth == "" {
		t.Logf("repository not found, skipping: %v", repo)
		return
	}

	bin := build(t, "", [][]string{{filepath.Join(pth, "selfie.c")}})
	if m, _ := NewModel(); m.Items[cc.Ptr].Size != 4 {
		return
	}

	args := []string{"./selfie"}
	out, _, d := exec(t, bin, args, nil)
	if g, e := out, []byte("./selfie: usage: selfie { -c { source } | -o binary | -s assembly | -l binary } [ ( -m | -d | -y | -min | -mob ) size ... ]"); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	t.Logf("%s\n%s\n%v", args, out, d)

	args = []string{"./selfie", "-c", "hello.c", "-m", "1"}
	out, _, d = exec(t, bin, args, []file{{"hello.c", []byte(`
int *foo;

int main() {
	foo = "Hello world!";
	while (*foo!=0) { 
		write(1, foo, 4);
		foo = foo + 1;
	}
	*foo = 10;
	write(1, foo, 1);
}
`)}})
	if g, e := out, []byte(`./selfie: this is selfie's starc compiling hello.c
./selfie: 141 characters read in 12 lines and 0 comments
./selfie: with 102(72.46%) characters in 52 actual symbols
./selfie: 1 global variables, 1 procedures, 1 string literals
./selfie: 2 calls, 3 assignments, 1 while, 0 if, 0 return
./selfie: 660 bytes generated with 159 instructions and 24 bytes of data
./selfie: this is selfie's mipster executing hello.c with 1MB of physical memory
Hello world!
hello.c: exiting with exit code 0 and 0.00MB of mallocated memory
./selfie: this is selfie's mipster terminating hello.c with exit code 0 and 0.01MB of mapped memory
./selfie: profile: total,max(ratio%)@addr(line#),2max(ratio%)@addr(line#),3max(ratio%)@addr(line#)
./selfie: calls: 5,4(80.00%)@0x88(~1),1(20.00%)@0x17C(~5),0(0.00%)
./selfie: loops: 3,3(100.00%)@0x198(~6),0(0.00%),0(0.00%)
./selfie: loads: 32,4(12.50%)@0x88(~1),3(9.38%)@0x1D4(~7),1(3.12%)@0x24(~1)
./selfie: stores: 20,3(15.01%)@0x1D0(~7),1(5.00%)@0x4C(~1),0(0.00%)`); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	t.Logf("%s\n%s\n%v", args, out, d)

	selfie, err := ioutil.ReadFile(filepath.Join(pth, "selfie.c"))
	if err != nil {
		t.Fatal(err)
	}

	args = []string{"./selfie", "-c", "selfie.c"}
	out, _, d = exec(t, bin, args, []file{{"selfie.c", selfie}})
	if g, e := out, []byte(`./selfie: this is selfie's starc compiling selfie.c
./selfie: 176362 characters read in 7086 lines and 970 comments
./selfie: with 97764(55.55%) characters in 28916 actual symbols
./selfie: 260 global variables, 290 procedures, 450 string literals
./selfie: 1960 calls, 722 assignments, 57 while, 571 if, 241 return
./selfie: 121676 bytes generated with 28783 instructions and 6544 bytes of data`); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	t.Logf("%s\n%s\n%v", args, out, d)
}

func TestC4(t *testing.T) {
	bin := build(t, "", [][]string{{"testdata/github.com/rswier/c4/c4.c"}})

	args := []string{"./c4"}
	out, _, d := exec(t, bin, args, nil)
	if g, e := out, []byte("usage: c4 [-s] [-d] file ..."); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	t.Logf("%s\n%s\n%v", args, out, d)

	hello, err := ioutil.ReadFile("testdata/github.com/rswier/c4/hello.c")
	if err != nil {
		t.Fatal(err)
	}

	args = []string{"./c4", "hello.c"}
	out, _, d = exec(t, bin, args, []file{{"hello.c", hello}})
	if g, e := out, []byte(`hello, world
exit(0) cycle = 9`); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	t.Logf("%s\n%s\n%v", args, out, d)

	args = []string{"./c4", "-s", "hello.c"}
	out, _, d = exec(t, bin, args, []file{{"hello.c", hello}})
	t.Logf("%s\n%s\n%v", args, out, d)

	c4, err := ioutil.ReadFile("testdata/github.com/rswier/c4/c4.c")
	if err != nil {
		t.Fatal(err)
	}

	args = []string{"./c4", "c4.c", "hello.c"}
	out, _, d = exec(t, bin, args, []file{{"c4.c", c4}, {"hello.c", hello}})
	if g, e := out, []byte(`hello, world
exit(0) cycle = 9
exit(0) cycle = 26012`); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	t.Logf("%s\n%s\n%v", args, out, d)
}

func TestSqlite(t *testing.T) {
	const repo = "sqlite.org/sqlite-amalgamation-3180000/"
	pth := findRepo(t, repo)
	if pth == "" {
		t.Logf("repository not found, skipping: %v", repo)
		return
	}

	bin := build(
		t,
		`#define SQLITE_DEBUG 1
		#define SQLITE_ENABLE_MEMSYS5 1`,
		[][]string{
			{"testdata/sqlite/test.c"},
			{filepath.Join(pth, "sqlite3.c")},
		},
		cc.EnableAnonymousStructFields(),
		cc.EnableWideBitFieldTypes(),
		cc.IncludePaths([]string{pth}),
	)
	var gz bytes.Buffer
	zw := gzip.NewWriter(&gz)
	enc := gob.NewEncoder(zw)
	if err := enc.Encode(bin); err != nil {
		t.Fatal(err)
	}

	if err := zw.Close(); err != nil {
		t.Fatal(err)
	}

	t.Logf("code %#08x, text %#08x, data %#08x, bss %#08x, pc2func %v, pc2line %v, gz %v\n",
		len(bin.Code), len(bin.Text), len(bin.Data), bin.BSS, len(bin.Functions), len(bin.Lines), len(gz.Bytes()),
	)

	args := []string{"./test"}
	out, f, d := exec(t, bin, args, nil)
	t.Logf("%q\n%s\n%v\n%v", args, out, d, f)
	if g, e := out, []byte("Usage: ./test DATABASE SQL-STATEMENT"); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	args = []string{"./test", "foo"}
	out, f, d = exec(t, bin, args, nil)
	t.Logf("%q\n%s\n%v\n%v", args, out, d, f)
	if g, e := out, []byte("Usage: ./test DATABASE SQL-STATEMENT"); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	args = []string{"./test", "foo", "bar"}
	out, f, d = exec(t, bin, args, nil)
	t.Logf("%q\n%s\n%v\n%v", args, out, d, f)
	if g, e := out, []byte(`FAIL (1) near "bar": syntax error
SQL error: near "bar": syntax error`); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	args = []string{"./test", "foo", "select * from t"}
	out, f, d = exec(t, bin, args, nil)
	t.Logf("%q\n%s\n%v\n%v", args, out, d, f)
	if g, e := out, []byte(`FAIL (1) no such table: t
SQL error: no such table: t`); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	args = []string{"./test", "foo", "select name from sqlite_master where type='table'"}
	out, f, d = exec(t, bin, args, nil)
	t.Logf("%q\n%s\n%v\n%v", args, out, d, f)
	if g, e := out, []byte(""); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	args = []string{"./test", "foo", "create table t(i int)"}
	out, f, d = exec(t, bin, args, nil)
	t.Logf("%q\n%s\n%v\n%v", args, out, d, f)
	if g, e := out, []byte(""); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	args = []string{"./test", "foo", `
	create table t(i int);
	select name from sqlite_master where type='table';
	`}
	out, f, d = exec(t, bin, args, nil)
	t.Logf("%q\n%s\n%v\n%v", args, out, d, f)
	if g, e := out, []byte("name = t"); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}

	args = []string{"./test", "foo", `
	create table t(i int);
	select name from sqlite_master where type='table';
	insert into t values(42), (314);
	select * from t order by i asc;
	select * from t order by i desc;
	`}
	out, f, d = exec(t, bin, args, nil)
	t.Logf("%q\n%s\n%v\n%v", args, out, d, f)
	if g, e := out, []byte(`name = t
i = 42
i = 314
i = 314
i = 42`); !bytes.Equal(g, e) {
		t.Fatalf("\ngot\n%s\nexp\n%s", g, e)
	}
}

func TestOther(t *testing.T) {
	var re *regexp.Regexp
	if s := *filter; s != "" {
		re = regexp.MustCompile(s)
	}

	expect(
		t,
		"testdata",
		func(match string) bool {
			if re != nil && !re.MatchString(filepath.Base(match)) {
				return true
			}

			return false
		},
		func(wd, match string) []string {
			return []string{match}
		},
		cc.EnableImplicitFuncDef(),
		cc.ErrLimit(-1),
		cc.SysIncludePaths([]string{LibcIncludePath}),
	)
}
