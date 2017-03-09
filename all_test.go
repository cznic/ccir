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
}

// ============================================================================

const (
	crt0Path = "testdata/include/crt0.c"
)

var (
	ccTestdata string

	cpp    = flag.Bool("cpp", false, "")
	filter = flag.String("re", "", "")
	noexec = flag.Bool("noexec", false, "")
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
	defer func() {
		if e := recover(); e != nil && err == nil {
			err = fmt.Errorf("%v", e)
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
	return modelName, ast, err
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
	modelName, ast, err := parse([]string{crt0Path, match}, opts...)
	if err != nil {
		return log, -1, err
	}

	objs, err := New(modelName, ast)
	if err != nil {
		return log, -1, err
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
		return log, -1, err
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
		return log, -1, err
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
				err = fmt.Errorf("virtual.Exec: PANIC: %v", err)
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
			if b := stdout.Bytes(); b != nil {
				fmt.Fprintf(&log, "stdout:\n%s\n", b)
			}
			if b := stderr.Bytes(); b != nil {
				fmt.Fprintf(&log, "stderr:\n%s\n", b)
			}
			return err
		}

		return nil
	}(); err != nil {
		return log, exitStatus, err
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
		log, exitStatus, err := expect1(wd, match, hook, opts...)
		switch {
		case exitStatus <= 0 && err == nil:
			okSeq++
		default:
			if seq-okSeq == 1 {
				t.Logf("%s: FAIL\n%s\n%s", match, errStr(err), log.Bytes())
			}
		}
		log.Close()
	}
	if okSeq != seq {
		t.Errorf("%v/%v ok", okSeq, seq)
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
		cc.EnableImplicitFuncDef(),
		cc.ErrLimit(-1),
		cc.SysIncludePaths([]string{"testdata/include/"}),
	)
}

func TestGCCExec(t *testing.T) {
	blacklist := map[string]struct{}{
		"pr33382.c": {}, //TODO
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
