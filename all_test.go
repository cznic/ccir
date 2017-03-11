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
	flag.BoolVar(&virtual.Testing, "virtualTesting", false, "")
	flag.BoolVar(&Testing, "testing", false, "")
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
			err = fmt.Errorf("cc.Parse: PANIC: %v", e)
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
		return modelName, nil, fmt.Errorf("cc.Parse: %v", err)
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
				fmt.Fprintf(&log, "# [%v]: %T %v %v\n", i, x, x.ObjectBase, x.Arguments)
				for i, v := range x.Body {
					fmt.Fprintf(&log, "%#05x\t%v\n", i, v)
				}
				return log, -1, err
			default:
				return log, -1, fmt.Errorf("[%v] %T %v: %v", i, x, x, err)
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
			return log, -1, fmt.Errorf("[%v] %T %v", i, x, x)
		}
	}
	for i, v := range objs {
		if err := v.Verify(); err != nil {
			return log, -1, fmt.Errorf("[%v]: %v", i, err)
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
			return fmt.Errorf("virtual.Exec: exist status %v, err %v", exitStatus, err)
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

		// Nested function.
		"20010209-1.c": {},
		"20010605-1.c": {},

		// __real__ and friends.
		"20010605-2.c": {},
		"20020411-1.c": {},

		// Depends on __attribute__((aligned(N)))
		"20010904-1.c": {},
		"20010904-2.c": {},

		// https://goo.gl/XDxJEL
		"20021127-1.c": {},

		// asm
		"20001009-2.c": {},
		"20020107-1.c": {},
		"20030222-1.c": {},
		"960312-1.c":   {},
		"pr38533.c":    {},
		"pr43385.c":    {},
		"pr45695.c":    {},
		"pr52286.c":    {},
		"pr65053-1.c":  {},
		"pr65053-2.c":  {},
	}
	todolist := map[string]struct{}{
		"20030408-1.c":                 {},
		"20030501-1.c":                 {},
		"20030714-1.c":                 {},
		"20030910-1.c":                 {},
		"20031003-1.c":                 {},
		"20040302-1.c":                 {},
		"20040308-1.c":                 {},
		"20040411-1.c":                 {},
		"20040423-1.c":                 {},
		"20040520-1.c":                 {},
		"20040709-1.c":                 {},
		"20040709-2.c":                 {},
		"20040811-1.c":                 {},
		"20041124-1.c":                 {},
		"20041201-1.c":                 {},
		"20041214-1.c":                 {},
		"20041218-2.c":                 {},
		"20050121-1.c":                 {},
		"20050316-1.c":                 {},
		"20050316-2.c":                 {},
		"20050316-3.c":                 {},
		"20050604-1.c":                 {},
		"20050607-1.c":                 {},
		"20050613-1.c":                 {},
		"20050929-1.c":                 {},
		"20051110-1.c":                 {},
		"20051110-2.c":                 {},
		"20060910-1.c":                 {},
		"20061220-1.c":                 {},
		"20070614-1.c":                 {},
		"20070919-1.c":                 {},
		"20071029-1.c":                 {},
		"20071210-1.c":                 {},
		"20071211-1.c":                 {},
		"20071219-1.c":                 {},
		"20071220-1.c":                 {},
		"20071220-2.c":                 {},
		"20080502-1.c":                 {},
		"20080519-1.c":                 {},
		"20080522-1.c":                 {},
		"20090113-1.c":                 {},
		"20090219-1.c":                 {},
		"20090814-1.c":                 {},
		"20101011-1.c":                 {},
		"20101025-1.c":                 {},
		"20120919-1.c":                 {},
		"920302-1.c":                   {},
		"920415-1.c":                   {},
		"920428-1.c":                   {},
		"920429-1.c":                   {},
		"920501-3.c":                   {},
		"920501-4.c":                   {},
		"920501-5.c":                   {},
		"920501-6.c":                   {},
		"920603-1.c":                   {},
		"920612-2.c":                   {},
		"920721-3.c":                   {},
		"920721-4.c":                   {},
		"920728-1.c":                   {},
		"920731-1.c":                   {},
		"920908-2.c":                   {},
		"920909-1.c":                   {},
		"920929-1.c":                   {},
		"921017-1.c":                   {},
		"921019-1.c":                   {},
		"921124-1.c":                   {},
		"930406-1.c":                   {},
		"930429-2.c":                   {},
		"930513-1.c":                   {},
		"930513-2.c":                   {},
		"930603-1.c":                   {},
		"930603-3.c":                   {},
		"930608-1.c":                   {},
		"930621-1.c":                   {},
		"930622-1.c":                   {},
		"930630-1.c":                   {},
		"930719-1.c":                   {},
		"930930-2.c":                   {},
		"931009-1.c":                   {},
		"931228-1.c":                   {},
		"941202-1.c":                   {},
		"950512-1.c":                   {},
		"950628-1.c":                   {},
		"950929-1.c":                   {},
		"951003-1.c":                   {},
		"960116-1.c":                   {},
		"960218-1.c":                   {},
		"960301-1.c":                   {},
		"960405-1.c":                   {},
		"960416-1.c":                   {},
		"960512-1.c":                   {},
		"961112-1.c":                   {},
		"970217-1.c":                   {},
		"980223.c":                     {},
		"980506-3.c":                   {},
		"980526-1.c":                   {},
		"980605-1.c":                   {},
		"990130-1.c":                   {},
		"990208-1.c":                   {},
		"990326-1.c":                   {},
		"990413-2.c":                   {},
		"990524-1.c":                   {},
		"991030-1.c":                   {},
		"991118-1.c":                   {},
		"991228-1.c":                   {},
		"alias-2.c":                    {},
		"alias-3.c":                    {},
		"alias-4.c":                    {},
		"align-3.c":                    {},
		"align-nest.c":                 {},
		"anon-1.c":                     {},
		"bcp-1.c":                      {},
		"bf-sign-1.c":                  {},
		"bf-sign-2.c":                  {},
		"bf64-1.c":                     {},
		"bitfld-1.c":                   {},
		"bitfld-3.c":                   {},
		"bitfld-4.c":                   {},
		"bitfld-5.c":                   {},
		"bitfld-6.c":                   {},
		"bitfld-7.c":                   {},
		"bswap-1.c":                    {},
		"bswap-2.c":                    {},
		"built-in-setjmp.c":            {},
		"builtin-constant.c":           {},
		"builtin-prefetch-2.c":         {},
		"builtin-prefetch-3.c":         {},
		"builtin-prefetch-4.c":         {},
		"builtin-prefetch-5.c":         {},
		"builtin-types-compatible-p.c": {},
		"comp-goto-1.c":                {},
		"complex-1.c":                  {},
		"complex-2.c":                  {},
		"complex-5.c":                  {},
		"complex-6.c":                  {},
		"complex-7.c":                  {},
		"compndlit-1.c":                {},
		"const-addr-expr-1.c":          {},
		"eeprof-1.c":                   {},
		"frame-address.c":              {},
		"inst-check.c":                 {},
		"int-compare.c":                {},
		"longlong.c":                   {},
		"loop-2.c":                     {},
		"loop-2d.c":                    {},
		"loop-2f.c":                    {},
		"loop-2g.c":                    {},
		"loop-3.c":                     {},
		"loop-3b.c":                    {},
		"loop-3c.c":                    {},
		"lto-tbaa-1.c":                 {},
		"medce-1.c":                    {},
		"mod-1.c":                      {},
		"nest-align-1.c":               {},
		"nest-stdar-1.c":               {},
		"nestfunc-7.c":                 {},
		"pr19005.c":                    {},
		"pr19449.c":                    {},
		"pr19689.c":                    {},
		"pr22061-1.c":                  {},
		"pr22061-3.c":                  {},
		"pr22061-4.c":                  {},
		"pr22098-1.c":                  {},
		"pr22098-2.c":                  {},
		"pr22098-3.c":                  {},
		"pr23135.c":                    {},
		"pr23324.c":                    {},
		"pr23467.c":                    {},
		"pr28289.c":                    {},
		"pr28982b.c":                   {},
		"pr30185.c":                    {},
		"pr31448-2.c":                  {},
		"pr31448.c":                    {},
		"pr32244-1.c":                  {},
		"pr33382.c":                    {}, //TODO SIGSEV
		"pr33631.c":                    {},
		"pr34154.c":                    {},
		"pr34176.c":                    {},
		"pr34456.c":                    {},
		"pr34768-1.c":                  {},
		"pr34768-2.c":                  {},
		"pr34971.c":                    {},
		"pr35456.c":                    {},
		"pr37573.c":                    {},
		"pr37924.c":                    {},
		"pr38051.c":                    {},
		"pr38151.c":                    {},
		"pr38212.c":                    {},
		"pr38969.c":                    {},
		"pr39100.c":                    {},
		"pr39240.c":                    {},
		"pr39339.c":                    {},
		"pr40022.c":                    {},
		"pr40657.c":                    {},
		"pr41239.c":                    {},
		"pr41919.c":                    {},
		"pr41935.c":                    {},
		"pr42231.c":                    {},
		"pr42248.c":                    {},
		"pr42512.c":                    {},
		"pr42691.c":                    {},
		"pr42833.c":                    {},
		"pr43220.c":                    {},
		"pr43438.c":                    {},
		"pr43560.c":                    {},
		"pr43784.c":                    {},
		"pr43987.c":                    {},
		"pr44164.c":                    {},
		"pr44555.c":                    {},
		"pr44683.c":                    {},
		"pr45034.c":                    {},
		"pr46309.c":                    {},
		"pr47237.c":                    {},
		"pr47337.c":                    {},
		"pr47538.c":                    {},
		"pr49218.c":                    {},
		"pr49279.c":                    {},
		"pr49390.c":                    {},
		"pr49644.c":                    {},
		"pr49768.c":                    {},
		"pr51447.c":                    {},
		"pr51877.c":                    {},
		"pr51933.c":                    {},
		"pr52979-1.c":                  {},
		"pr52979-2.c":                  {},
		"pr53084.c":                    {},
		"pr53645-2.c":                  {},
		"pr53645.c":                    {},
		"pr54937.c":                    {},
		"pr56205.c":                    {},
		"pr56837.c":                    {},
		"pr56982.c":                    {},
		"pr57344-1.c":                  {},
		"pr57344-2.c":                  {},
		"pr57344-3.c":                  {},
		"pr57344-4.c":                  {},
		"pr57568.c":                    {},
		"pr57861.c":                    {},
		"pr57875.c":                    {},
		"pr58277-1.c":                  {},
		"pr58277-2.c":                  {},
		"pr58419.c":                    {},
		"pr58431.c":                    {},
		"pr58570.c":                    {},
		"pr58726.c":                    {},
		"pr58831.c":                    {},
		"pr58943.c":                    {},
		"pr58984.c":                    {},
		"pr59221.c":                    {},
		"pr59643.c":                    {},
		"pr60003.c":                    {},
		"pr60960.c":                    {},
		"pr61306-3.c":                  {},
		"pr61682.c":                    {},
		"pr62151.c":                    {},
		"pr63209.c":                    {},
		"pr63641.c":                    {},
		"pr63659.c":                    {},
		"pr64006.c":                    {},
		"pr64756.c":                    {},
		"pr65215-5.c":                  {},
		"pr65401.c":                    {},
		"pr65427.c":                    {},
		"pr65648.c":                    {},
		"pr65956.c":                    {},
		"pr67714.c":                    {},
		"pr68249.c":                    {},
		"pr68328.c":                    {},
		"pr68381.c":                    {},
		"pr68532.c":                    {},
		"pr68648.c":                    {},
		"pr69320-1.c":                  {},
		"pr69320-2.c":                  {},
		"pr69447.c":                    {},
		"pr69691.c":                    {},
		"pr70127.c":                    {},
		"pr70460.c":                    {},
		"pr71494.c":                    {},
		"pr71554.c":                    {},
		"pr71626-1.c":                  {},
		"pr71626-2.c":                  {},
		"pushpop_macro.c":              {},
		"scal-to-vec1.c":               {},
		"scal-to-vec2.c":               {},
		"scal-to-vec3.c":               {},
		"scope-1.c":                    {},
		"simd-1.c":                     {},
		"simd-2.c":                     {},
		"simd-4.c":                     {},
		"simd-5.c":                     {},
		"simd-6.c":                     {},
		"stdarg-1.c":                   {},
		"stkalign.c":                   {},
		"string-opt-18.c":              {},
		"string-opt-5.c":               {},
		"struct-cpy-1.c":               {},
		"struct-ini-1.c":               {},
		"struct-ini-2.c":               {},
		"struct-ini-4.c":               {},
		"struct-ret-1.c":               {},
		"va-arg-10.c":                  {},
		"va-arg-14.c":                  {},
		"va-arg-pack-1.c":              {},
		"vla-dealloc-1.c":              {},
		"wchar_t-1.c":                  {},
		"widechar-2.c":                 {},
		"zero-struct-1.c":              {},
		"zero-struct-2.c":              {},
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
		cc.EnableBuiltinConstantP(),
		cc.EnableDefineOmitCommaBeforeDDD(),
		cc.EnableEmptyDeclarations(),
		cc.EnableEmptyStructs(),
		cc.EnableImplicitFuncDef(),
		cc.EnableOmitFuncRetType(),
		cc.EnableParenthesizedCompoundStatemen(),
		cc.EnableTypeOf(),
		cc.EnableWideBitFieldTypes(),
		cc.ErrLimit(-1),
		cc.SysIncludePaths([]string{"testdata/include/"}),
	)
}
