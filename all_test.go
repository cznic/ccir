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
	flag.BoolVar(&Testing, "testing", false, "")
	flag.BoolVar(&ir.Testing, "irTesting", false, "")
	flag.BoolVar(&virtual.Testing, "virtualTesting", false, "")
}

// ============================================================================

const (
	crt0Path = "testdata/include/crt0.c"
)

var (
	ccTestdata string

	cpp     = flag.Bool("cpp", false, "")
	filter  = flag.String("re", "", "")
	noexec  = flag.Bool("noexec", false, "")
	oLog    = flag.Bool("log", false, "")
	trace   = flag.Bool("trc", false, "")
	yydebug = flag.Int("yydebug", 0, "")
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

func parse(src []string, opts ...cc.Opt) (_ string, _ *cc.TranslationUnit, err error) {
	defer func() {
		if e := recover(); e != nil && err == nil {
			err = fmt.Errorf("cc.Parse: PANIC: %v\n%s", e, debug.Stack())
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

#include <builtin.h>
`, strings.ToUpper(modelName)),
		src,
		model,
		opts...,
	)
	if err != nil {
		return modelName, nil, fmt.Errorf("cc.Parse: %v", errStr(err))
	}

	return modelName, ast, nil
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
	modelName, ast, err := parse([]string{crt0Path, match}, opts...)
	if err != nil {
		return log, -1, err
	}

	objs, err := New(modelName, ast)
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
				return log, -1, fmt.Errorf("# [%v]: Verify (A): %v", i, err)
			default:
				return log, -1, fmt.Errorf("[%v]: %T %v: %v", i, x, x, err)
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
			fmt.Fprintf(&log, "# [%v, err]: %T %v %v\n", i, x, x.ObjectBase, x.Value)
		case *ir.FunctionDefinition:
			fmt.Fprintf(&log, "# [%v, err]: %T %v %v\n", i, x, x.ObjectBase, x.Arguments)
			for i, v := range x.Body {
				fmt.Fprintf(&log, "%#05x\t%v\n", i, v)
			}
		default:
			return log, -1, fmt.Errorf("[%v]: %T %v", i, x, x)
		}
	}
	for i, v := range objs {
		if err := v.Verify(); err != nil {
			return log, -1, fmt.Errorf("# [%v]: Verify (B): %v", i, err)
		}
	}

	bin, err := virtual.LoadMain(modelName, objs)
	if err != nil {
		return log, -1, fmt.Errorf("virtual.LoadMain: %v", err)
	}

	s := virtual.DumpCodeStr(bin.Code, 0)
	fmt.Fprintf(&log, "%s: virtual.LoadMain: code %#05x, text %#05x, data %05x, bss %#05x, functions %v, lines %v\n%s\n",
		match, len(bin.Code)*2*mathutil.IntBits/8, len(bin.Text), len(bin.Data), bin.BSS, len(bin.Functions), len(bin.Lines), s.Bytes(),
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
		if exitStatus, err = virtual.Exec(bin, args, &stdin, &stdout, &stderr, 1<<20, 1<<20); exitStatus != 0 || err != nil {
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
			//dbg("", match)
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
		cc.EnableDefineOmitCommaBeforeDDD(),
		cc.EnableImplicitFuncDef(),
		cc.ErrLimit(-1),
		cc.SysIncludePaths([]string{"testdata/include/"}),
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
		"990130-1.c":   {},
		"990413-2.c":   {},
		"pr38533.c":    {},
		"pr40022.c":    {},
		"pr40657.c":    {},
		"pr43385.c":    {},
		"pr43560.c":    {},
		"pr45695.c":    {},
		"pr49279.c":    {},
		"pr49390.c":    {},
		"pr51877.c":    {},
		"pr51933.c":    {},
		"pr52286.c":    {},
		"pr56205.c":    {},
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
	}
	todolist := map[string]struct{}{
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
		"pr43220.c":       {},
		"vla-dealloc-1.c": {},

		// Initializer
		"20050613-1.c":         {},
		"20050929-1.c":         {},
		"20071029-1.c":         {},
		"20080522-1.c":         {},
		"20090113-1.c":         {},
		"20101025-1.c":         {},
		"20120919-1.c":         {},
		"921019-1.c":           {},
		"960416-1.c":           {},
		"980223.c":             {},
		"991228-1.c":           {},
		"bcp-1.c":              {},
		"bitfld-6.c":           {}, //TODO + __BYTE_ORDER__
		"bitfld-7.c":           {}, //TODO + __BYTE_ORDER__
		"builtin-prefetch-2.c": {},
		"builtin-prefetch-3.c": {},
		"builtin-prefetch-4.c": {},
		"builtin-prefetch-5.c": {},
		"compndlit-1.c":        {},
		"const-addr-expr-1.c":  {},
		"longlong.c":           {},
		"lto-tbaa-1.c":         {},
		"pr22098-1.c":          {},
		"pr22098-2.c":          {},
		"pr22098-3.c":          {},
		"pr23324.c":            {},
		"pr28982b.c":           {},
		"pr33382.c":            {},
		"pr33631.c":            {},
		"pr34176.c":            {},
		"pr39100.c":            {},
		"pr43438.c":            {},
		"pr43784.c":            {},
		"pr44164.c":            {},
		"pr47337.c":            {},
		"pr53084.c":            {},
		"pr53645-2.c":          {},
		"pr53645.c":            {},
		"pr57568.c":            {},
		"pr58277-1.c":          {},
		"pr58277-2.c":          {},
		"pr58419.c":            {},
		"pr61682.c":            {},
		"pr64756.c":            {},
		"pr69320-1.c":          {},
		"pr69691.c":            {},
		"pr70460.c":            {},
		"pr70602.c":            {},
		"struct-ini-1.c":       {},
		"va-arg-pack-1.c":      {},
		"zero-struct-1.c":      {},

		// signal.h
		"20101011-1.c": {},

		// mmap.h
		"loop-2f.c": {},
		"loop-2g.c": {},

		// &&label expr
		"920302-1.c":    {},
		"920501-3.c":    {},
		"920501-5.c":    {},
		"990208-1.c":    {},
		"comp-goto-1.c": {},

		// &func
		"930513-1.c": {},
		"930608-1.c": {},

		// invalid floating point constant
		"960405-1.c": {},

		// jmp
		"built-in-setjmp.c": {},
		"pr41239.c":         {},
		"pr56982.c":         {},
		"pr60003.c":         {},

		// qsort
		"pr34456.c": {}, // qsort

		// cc.Parse later
		"pr22061-1.c": {},
		"pr46309.c":   {}, // expr ? void : int
		"pr68249.c":   {}, // m = b || c < 0 || c > 1 ? : c;

		// bitfields
		"bf-sign-2.c": {},
		"bitfld-1.c":  {},
		"bitfld-3.c":  {},
		"bitfld-5.c":  {},
		"bswap-2.c":   {},
		"pr31448-2.c": {},
		"pr31448.c":   {},
		"pr32244-1.c": {},
		"pr34971.c":   {},

		// builtins
		"builtin-types-compatible-p.c": {}, // https://www.daemon-systems.org/man/__builtin_types_compatible_p.3.html
		"eeprof-1.c":                   {},
		"frame-address.c":              {},
		"pr47237.c":                    {},
		"pr64006.c":                    {},
		"pr68381.c":                    {},
		"pr71554.c":                    {},

		// complex arithmetic
		"pr49644.c": {},

		// ir.Link
		"pr54937.c":       {},
		"string-opt-18.c": {},

		// ir.Verify
		"pr58431.c": {},
		"pr58726.c": {},

		// evaluation order and side effects
		"pr58943.c": {},

		// #pragma
		"pushpop_macro.c": {},

		// Shifts
		"20020226-1.c": {},
		"20020508-1.c": {},
		"20020508-2.c": {},
		"20020508-3.c": {},
		"pr40386.c":    {},

		// 32-bits
		"20040709-1.c":       {},
		"20040709-2.c":       {},
		"20080424-1.c":       {},
		"20081117-1.c":       {},
		"930126-1.c":         {},
		"930628-1.c":         {},
		"991118-1.c":         {},
		"bf-pack-1.c":        {},
		"bf64-1.c":           {},
		"bswap-1.c":          {},
		"builtin-bitops-1.c": {},
		"complex-2.c":        {},
		"pr42248.c":          {},
		"pr58570.c":          {},
		"pr65215-3.c":        {},
		"pr65215-4.c":        {},
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
		cc.EnableOmitFuncArgTypes(),
		cc.EnableOmitFuncRetType(),
		cc.EnableParenthesizedCompoundStatemen(),
		cc.EnableTypeOf(),
		cc.EnableUnsignedEnums(),
		cc.EnableWideBitFieldTypes(),
		cc.ErrLimit(-1),
		cc.SysIncludePaths([]string{"testdata/include/"}),
	)
}

func TestSelfie(t *testing.T) {
	const src = "testdata/selfie/selfie.c"

	modelName := fmt.Sprint(mathutil.UintPtrBits)
	model, err := Model(modelName)
	if err != nil {
		t.Fatal(err)
	}

	ast, err := cc.Parse(
		fmt.Sprintf(`
#define __STDC_HOSTED__ 1
#define __STDC_VERSION__ 199901L
#define __STDC__ 1
#define __MODEL_%s__

#include <builtin.h>
`, strings.ToUpper(modelName)),
		[]string{crt0Path, src},
		model,
		cc.SysIncludePaths([]string{"testdata/include/"}),
	)
	if err != nil {
		t.Fatal(errStr(err))
	}

	objs, err := New(modelName, ast)
	if err != nil {
		t.Fatal(err)
	}

	for _, v := range objs {
		if err := v.Verify(); err != nil {
			t.Fatal(err)
		}
	}

	if objs, err = ir.LinkMain(objs); err != nil {
		t.Fatal(err)
	}

	for _, v := range objs {
		if err := v.Verify(); err != nil {
			t.Fatal(err)
		}
	}

	bin, err := virtual.LoadMain(modelName, objs)
	if err != nil {
		t.Fatal(err)
	}

	if modelName != "32" {
		return
	}

	var exitStatus int
	var log buffer.Bytes
	if err := func() (err error) {
		defer func() {
			if e := recover(); e != nil && err == nil {
				err = fmt.Errorf("virtual.Exec: PANIC: %v", e)
			}
		}()

		var (
			stdin          bytes.Buffer
			stdout, stderr buffer.Bytes
		)
		exitStatus, err = virtual.Exec(bin, []string{"./selfie"}, &stdin, &stdout, &stderr, 1<<27, 1<<20)
		if b := stdout.Bytes(); b != nil {
			fmt.Fprintf(&log, "stdout:\n%s\n", b)
		}
		if b := stderr.Bytes(); b != nil {
			fmt.Fprintf(&log, "stderr:\n%s\n", b)
		}
		if exitStatus != 0 || err != nil {
			t.Fatalf("exit status %v, err %v\n%s", exitStatus, err, log.Bytes())
		}

		return nil
	}(); err != nil {
		t.Fatalf("exit status %v, err %v\n%s", exitStatus, err, log.Bytes())
	}
}
