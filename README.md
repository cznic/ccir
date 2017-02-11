# ccir
Package ccir translates [cc](https://github.com/cznic/cc) ASTs to internal representation. (Work In Progress)

Installation

    $ go get github.com/cznic/ccir

Documentation: [godoc.org/github.com/cznic/ccir](http://godoc.org/github.com/cznic/ccir)

----

# What's this all about?

Not much yet. Consider this an early technology preview, it can now handle only C programs of complexity comparable to `helloworld.c`. Nonetheless, you should be hopefully able, using today's (2017-02-11) commits of [ir](https://github.com/cznic/ir), [virtual](https://github.com/cznic/virtual) and this package, reproduce the results, annotated excerpts of which follow, issuing


```bash
$ go test github.com/cznic/ccir
        ... lot of output
```

----

There's a test helper in [`all_test.go`](https://github.com/cznic/ccir/blob/fd070780c1a293d80513a231ebe97c9afd1cb854/all_test.go#L113)

```go
func parse(src []string, opts ...cc.Opt) (string, *cc.TranslationUnit, error) {
	modelName := fmt.Sprint(mathutil.UintPtrBits)
	model, err := Model(modelName)
	if err != nil {
		return "", nil, err
	}

	ast, err := cc.Parse(
		`
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
```

It get's called like [this](https://github.com/cznic/ccir/blob/fd070780c1a293d80513a231ebe97c9afd1cb854/all_test.go#L151)

```go
...
modelName, ast, err := parse(
	[]string{crt0Path, match},
	cc.EnableDefineOmitCommaBeforeDDD(),
	cc.ErrLimit(-1),
	cc.SysIncludePaths([]string{"testdata/include/"}),
)
...
```

For `crt0Path` [pointing to](https://github.com/cznic/ccir/blob/fd070780c1a293d80513a231ebe97c9afd1cb854/testdata/include/crt0.c)

```c
#include <stdlib.h>

int main();

void _start(int argc, char **argv)
{
	exit(main(argc, argv));
}
```

and `match` [pointing to](https://github.com/cznic/cc/blob/9604c5ca5ff2a70e0e4e82ee5a3653219e34954b/testdata/tcc-0.9.26/tests/tests2/10_pointer.c) for example (from [TCC](https://en.wikipedia.org/wiki/Tiny_C_Compiler) tests)

```c
#include <stdio.h>

struct ziggy
{
   int a;
   int b;
   int c;
} bolshevic;

int main()
{
   int a;
   int *b;
   int c;

   a = 42;
   b = &a;
   printf("a = %d\n", *b);

   bolshevic.a = 12;
   bolshevic.b = 34;
   bolshevic.c = 56;

   printf("bolshevic.a = %d\n", bolshevic.a);
   printf("bolshevic.b = %d\n", bolshevic.b);
   printf("bolshevic.c = %d\n", bolshevic.c);

   struct ziggy *tsar = &bolshevic;

   printf("tsar->a = %d\n", tsar->a);
   printf("tsar->b = %d\n", tsar->b);
   printf("tsar->c = %d\n", tsar->c);

   b = &(bolshevic.b);
   printf("bolshevic.b = %d\n", *b);

   return 0;
}

// vim: set expandtab ts=4 sw=3 sts=3 tw=80 :
```

`ccir.New` produces this intermediate representation:

```
all_test.go:180: ccir.New: 18 objects
	# [0]: *ir.FunctionDefinition {testdata/include/stdlib.h:12:6 __builtin_abort func() ExternalLinkage } []
	0x00000		panic           		; testdata/include/stdlib.h:12:6
	# [1]: *ir.FunctionDefinition {testdata/include/stdlib.h:13:6 __builtin_exit func(int32) ExternalLinkage } [status]
	0x00000		panic           		; testdata/include/stdlib.h:13:6
	# [2]: *ir.FunctionDefinition {testdata/include/crt0.c:5:1 _start func(int32,**int8) ExternalLinkage } [argc argv]
	0x00000		beginScope      		; testdata/include/crt0.c:6:1
	0x00001	extern	&__builtin_exit 	*func(int32)	;  testdata/include/crt0.c:7:2
	0x00002		arguments       		; testdata/include/crt0.c:7:7
	0x00003		allocResult     	int32	;  testdata/include/crt0.c:7:7
	0x00004	extern	&main           	*func()int32	;  testdata/include/crt0.c:7:7
	0x00005		arguments       		; testdata/include/crt0.c:7:12
	0x00006		argument        	0, int32	; testdata/include/crt0.c:7:12
	0x00007		argument        	1, **int8	; testdata/include/crt0.c:7:18
	0x00008		call            	2, *func()int32	; testdata/include/crt0.c:7:7
	0x00009		call            	1, *func(int32)	; testdata/include/crt0.c:7:2
	0x0000a		return          		; testdata/include/crt0.c:8:1
	0x0000b		endScope        		; testdata/include/crt0.c:8:1
	# [3]: *ir.DataDefinition {- _start^@__func__^@0 [7]int8 InternalLinkage } "_start"
	# [4]: *ir.DataDefinition {testdata/include/stdio.h:26:6 __stdstreams [3]struct{int32} ExternalLinkage FILE} <nil>
	# [5]: *ir.FunctionDefinition {testdata/include/stdio.h:28:6 __builtin_fopen func(*int8,*int8)*struct{int32} ExternalLinkage FILE} [path mode]
	0x00000		panic           		; testdata/include/stdio.h:28:6
	# [6]: *ir.FunctionDefinition {testdata/include/stdio.h:29:6 __builtin_fgets func(*int8,int32,*struct{int32})*int8 ExternalLinkage } [s size stream]
	0x00000		panic           		; testdata/include/stdio.h:29:6
	# [7]: *ir.FunctionDefinition {testdata/include/stdio.h:30:5 __builtin_fclose func(*struct{int32})int32 ExternalLinkage } [stream]
	0x00000		panic           		; testdata/include/stdio.h:30:5
	# [8]: *ir.FunctionDefinition {testdata/include/stdio.h:31:5 __builtin_fgetc func(*struct{int32})int32 ExternalLinkage } [stream]
	0x00000		panic           		; testdata/include/stdio.h:31:5
	# [9]: *ir.FunctionDefinition {testdata/include/stdio.h:32:5 __builtin_fprintf func(*struct{int32},*int8...)int32 ExternalLinkage } [stream format]
	0x00000		panic           		; testdata/include/stdio.h:32:5
	# [10]: *ir.FunctionDefinition {testdata/include/stdio.h:33:5 __builtin_getc func(*struct{int32})int32 ExternalLinkage } [stream]
	0x00000		panic           		; testdata/include/stdio.h:33:5
	# [11]: *ir.FunctionDefinition {testdata/include/stdio.h:34:5 __builtin_printf func(*int8...)int32 ExternalLinkage } [format]
	0x00000		panic           		; testdata/include/stdio.h:34:5
	# [12]: *ir.FunctionDefinition {testdata/include/stdio.h:35:5 __builtin_sprintf func(*int8,*int8...)int32 ExternalLinkage } [str format]
	0x00000		panic           		; testdata/include/stdio.h:35:5
	# [13]: *ir.FunctionDefinition {testdata/include/stdio.h:36:8 __builtin_fread func(*struct{},uint64,uint64,*struct{int32})uint64 ExternalLinkage size_t} [ptr size nmemb stream]
	0x00000		panic           		; testdata/include/stdio.h:36:8
	# [14]: *ir.FunctionDefinition {testdata/include/stdio.h:37:8 __builtin_fwrite func(*struct{},uint64,uint64,*struct{int32})uint64 ExternalLinkage size_t} [ptr size nmemb stream]
	0x00000		panic           		; testdata/include/stdio.h:37:8
	# [15]: *ir.DataDefinition {../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:8:3 bolshevic struct{int32,int32,int32} ExternalLinkage } <nil>
	# [16]: *ir.FunctionDefinition {../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:10:1 main func()int32 ExternalLinkage } []
	0x00000		beginScope      		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:11:1
	0x00001		varDecl         	0, a, int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:12:8
	0x00002		varDecl         	1, b, *int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:13:8
	0x00003		varDecl         	2, c, int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:14:8
	0x00004		variable        	&0, *int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:16:4
	0x00005		const           	42, int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:16:8
	0x00006		store           	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:16:6
	0x00007		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:16:4
	0x00008		variable        	&1, **int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:17:4
	0x00009		variable        	&0, *int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:17:9
	0x0000a		store           	*int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:17:6
	0x0000b		drop            	*int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:17:4
	0x0000c		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:4
	0x0000d	extern	&__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:4
	0x0000e		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:11
	0x0000f		const           	"a = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:11
	0x00010		variable        	1, *int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:24
	0x00011		load            	*int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:23
	0x00012		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:4
	0x00013		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:4
	0x00014	extern	&bolshevic      	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:20:4
	0x00015		field           	&0, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:20:4
	0x00016		const           	12, int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:20:18
	0x00017		store           	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:20:16
	0x00018		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:20:4
	0x00019	extern	&bolshevic      	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:21:4
	0x0001a		field           	&1, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:21:4
	0x0001b		const           	34, int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:21:18
	0x0001c		store           	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:21:16
	0x0001d		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:21:4
	0x0001e	extern	&bolshevic      	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:22:4
	0x0001f		field           	&2, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:22:4
	0x00020		const           	56, int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:22:18
	0x00021		store           	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:22:16
	0x00022		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:22:4
	0x00023		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:4
	0x00024	extern	&__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:4
	0x00025		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:11
	0x00026		const           	"bolshevic.a = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:11
	0x00027	extern	&bolshevic      	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:33
	0x00028		field           	0, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:33
	0x00029		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:4
	0x0002a		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:4
	0x0002b		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:4
	0x0002c	extern	&__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:4
	0x0002d		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:11
	0x0002e		const           	"bolshevic.b = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:11
	0x0002f	extern	&bolshevic      	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:33
	0x00030		field           	1, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:33
	0x00031		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:4
	0x00032		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:4
	0x00033		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:4
	0x00034	extern	&__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:4
	0x00035		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:11
	0x00036		const           	"bolshevic.c = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:11
	0x00037	extern	&bolshevic      	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:33
	0x00038		field           	2, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:33
	0x00039		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:4
	0x0003a		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:4
	0x0003b		varDecl         	3, tsar, *struct{int32,int32,int32}(extern -1, &bolshevic)	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:28:17
	0x0003c		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:4
	0x0003d	extern	&__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:4
	0x0003e		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:11
	0x0003f		const           	"tsar->a = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:11
	0x00040		variable        	3, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:29
	0x00041		field           	0, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:29
	0x00042		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:4
	0x00043		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:4
	0x00044		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:4
	0x00045	extern	&__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:4
	0x00046		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:11
	0x00047		const           	"tsar->b = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:11
	0x00048		variable        	3, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:29
	0x00049		field           	1, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:29
	0x0004a		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:4
	0x0004b		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:4
	0x0004c		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:4
	0x0004d	extern	&__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:4
	0x0004e		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:11
	0x0004f		const           	"tsar->c = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:11
	0x00050		variable        	3, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:29
	0x00051		field           	2, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:29
	0x00052		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:4
	0x00053		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:4
	0x00054		variable        	&1, **int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:34:4
	0x00055	extern	&bolshevic      	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:34:10
	0x00056		field           	&1, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:34:10
	0x00057		store           	*int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:34:6
	0x00058		drop            	*int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:34:4
	0x00059		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:4
	0x0005a	extern	&__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:4
	0x0005b		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:11
	0x0005c		const           	"bolshevic.b = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:11
	0x0005d		variable        	1, *int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:34
	0x0005e		load            	*int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:33
	0x0005f		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:4
	0x00060		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:4
	0x00061		result          	&0, *int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:37:4
	0x00062		const           	0, int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:37:11
	0x00063		store           	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:37:4
	0x00064		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:37:4
	0x00065		return          		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:37:4
	0x00066		endScope        		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:38:1
	# [17]: *ir.DataDefinition {- main^@__func__^@0 [5]int8 InternalLinkage } "main"
```

`ir.LinkMain ` puts together the parts transitively referenced from `_start`:

```
all_test.go:214: ir.LinkMain: 5 objects
	# [0]: *ir.FunctionDefinition {testdata/include/crt0.c:5:1 _start func(int32,**int8) ExternalLinkage } [argc argv]
	0x00000		beginScope      		; testdata/include/crt0.c:6:1
	0x00001	extern	1, &__builtin_exit	*func(int32)	;  testdata/include/crt0.c:7:2
	0x00002		arguments       		; testdata/include/crt0.c:7:7
	0x00003		allocResult     	int32	;  testdata/include/crt0.c:7:7
	0x00004	extern	2, &main        	*func()int32	;  testdata/include/crt0.c:7:7
	0x00005		arguments       		; testdata/include/crt0.c:7:12
	0x00006		argument        	0, int32	; testdata/include/crt0.c:7:12
	0x00007		argument        	1, **int8	; testdata/include/crt0.c:7:18
	0x00008		call            	2, *func()int32	; testdata/include/crt0.c:7:7
	0x00009		call            	1, *func(int32)	; testdata/include/crt0.c:7:2
	0x0000a		return          		; testdata/include/crt0.c:8:1
	0x0000b		endScope        		; testdata/include/crt0.c:8:1
	# [1]: *ir.FunctionDefinition {testdata/include/stdlib.h:13:6 __builtin_exit func(int32) ExternalLinkage } [status]
	0x00000		panic           		; testdata/include/stdlib.h:13:6
	# [2]: *ir.FunctionDefinition {../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:10:1 main func()int32 ExternalLinkage } []
	0x00000		beginScope      		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:11:1
	0x00001		varDecl         	0, a, int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:12:8
	0x00002		varDecl         	1, b, *int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:13:8
	0x00003		varDecl         	2, c, int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:14:8
	0x00004		variable        	&0, *int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:16:4
	0x00005		const           	42, int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:16:8
	0x00006		store           	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:16:6
	0x00007		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:16:4
	0x00008		variable        	&1, **int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:17:4
	0x00009		variable        	&0, *int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:17:9
	0x0000a		store           	*int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:17:6
	0x0000b		drop            	*int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:17:4
	0x0000c		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:4
	0x0000d	extern	3, &__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:4
	0x0000e		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:11
	0x0000f		const           	"a = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:11
	0x00010		variable        	1, *int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:24
	0x00011		load            	*int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:23
	0x00012		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:4
	0x00013		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:18:4
	0x00014	extern	4, &bolshevic   	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:20:4
	0x00015		field           	&0, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:20:4
	0x00016		const           	12, int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:20:18
	0x00017		store           	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:20:16
	0x00018		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:20:4
	0x00019	extern	4, &bolshevic   	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:21:4
	0x0001a		field           	&1, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:21:4
	0x0001b		const           	34, int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:21:18
	0x0001c		store           	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:21:16
	0x0001d		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:21:4
	0x0001e	extern	4, &bolshevic   	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:22:4
	0x0001f		field           	&2, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:22:4
	0x00020		const           	56, int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:22:18
	0x00021		store           	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:22:16
	0x00022		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:22:4
	0x00023		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:4
	0x00024	extern	3, &__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:4
	0x00025		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:11
	0x00026		const           	"bolshevic.a = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:11
	0x00027	extern	4, &bolshevic   	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:33
	0x00028		field           	0, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:33
	0x00029		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:4
	0x0002a		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:24:4
	0x0002b		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:4
	0x0002c	extern	3, &__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:4
	0x0002d		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:11
	0x0002e		const           	"bolshevic.b = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:11
	0x0002f	extern	4, &bolshevic   	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:33
	0x00030		field           	1, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:33
	0x00031		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:4
	0x00032		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:25:4
	0x00033		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:4
	0x00034	extern	3, &__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:4
	0x00035		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:11
	0x00036		const           	"bolshevic.c = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:11
	0x00037	extern	4, &bolshevic   	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:33
	0x00038		field           	2, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:33
	0x00039		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:4
	0x0003a		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:26:4
	0x0003b		varDecl         	3, tsar, *struct{int32,int32,int32}(extern 4, &bolshevic)	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:28:17
	0x0003c		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:4
	0x0003d	extern	3, &__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:4
	0x0003e		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:11
	0x0003f		const           	"tsar->a = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:11
	0x00040		variable        	3, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:29
	0x00041		field           	0, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:29
	0x00042		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:4
	0x00043		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:30:4
	0x00044		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:4
	0x00045	extern	3, &__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:4
	0x00046		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:11
	0x00047		const           	"tsar->b = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:11
	0x00048		variable        	3, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:29
	0x00049		field           	1, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:29
	0x0004a		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:4
	0x0004b		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:31:4
	0x0004c		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:4
	0x0004d	extern	3, &__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:4
	0x0004e		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:11
	0x0004f		const           	"tsar->c = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:11
	0x00050		variable        	3, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:29
	0x00051		field           	2, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:29
	0x00052		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:4
	0x00053		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:32:4
	0x00054		variable        	&1, **int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:34:4
	0x00055	extern	4, &bolshevic   	*struct{int32,int32,int32}	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:34:10
	0x00056		field           	&1, *struct{int32,int32,int32}	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:34:10
	0x00057		store           	*int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:34:6
	0x00058		drop            	*int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:34:4
	0x00059		allocResult     	int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:4
	0x0005a	extern	3, &__builtin_printf	*func(*int8...)int32	;  ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:4
	0x0005b		arguments       		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:11
	0x0005c		const           	"bolshevic.b = %d\n", *int8	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:11
	0x0005d		variable        	1, *int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:34
	0x0005e		load            	*int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:33
	0x0005f		call            	2, *func(*int8...)int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:4
	0x00060		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:35:4
	0x00061		result          	&0, *int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:37:4
	0x00062		const           	0, int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:37:11
	0x00063		store           	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:37:4
	0x00064		drop            	int32	; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:37:4
	0x00065		return          		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:37:4
	0x00066		endScope        		; ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:38:1
	# [3]: *ir.FunctionDefinition {testdata/include/stdio.h:34:5 __builtin_printf func(*int8...)int32 ExternalLinkage } [format]
	0x00000		panic           		; testdata/include/stdio.h:34:5
	# [4]: *ir.DataDefinition {../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c:8:3 bolshevic struct{int32,int32,int32} ExternalLinkage } <nil>
```

# And now for something completely back-end


`virtual.Load` translates the above intermediate representation into sub optimal code for a particular (virtual) machine backend


```
all_test.go:227: virtual.Load: code 0x00056, text 0x00080, data 00000, bss 0x00010
	0x00000	func
	0x00001		arguments   
	0x00002		sub         sp, 0x8
	0x00003		arguments   
	0x00004		push32      (ap-0x8)
	0x00005		push64      (ap-0x10)
	0x00006		call        0x8
	0x00007		exit        
	
	0x00008	func	variables   [0x20]byte
	0x00009		push        bp-0x8
	0x0000a		push32      0x2a
	0x0000b		store32     
	0x0000c		add         sp, 0x8
	0x0000d		push        bp-0x10
	0x0000e		push        bp-0x8
	0x0000f		store64     
	0x00010		arguments   
	0x00011		push        ts+0x0
	0x00012		push64      (bp-0x10)
	0x00013		load32      0x0
	0x00014		printf      
	0x00015		add         sp, 0x8
	0x00016		push        bss
	0x00017		addptr      0x0
	0x00018		push32      0xc
	0x00019		store32     
	0x0001a		add         sp, 0x8
	0x0001b		push        bss
	0x0001c		addptr      0x4
	0x0001d		push32      0x22
	0x0001e		store32     
	0x0001f		add         sp, 0x8
	0x00020		push        bss
	0x00021		addptr      0x8
	0x00022		push32      0x38
	0x00023		store32     
	0x00024		arguments   
	0x00025		push        ts+0x8
	0x00026		push        bss
	0x00027		load32      0x0
	0x00028		printf      
	0x00029		arguments   
	0x0002a		push        ts+0x20
	0x0002b		push        bss
	0x0002c		load32      0x4
	0x0002d		printf      
	0x0002e		arguments   
	0x0002f		push        ts+0x38
	0x00030		push        bss
	0x00031		load32      0x8
	0x00032		printf      
	0x00033		add         sp, 0x8
	0x00034		push        bp-0x20
	0x00035		push        bss
	0x00036		store64     
	0x00037		sub         sp, 0x8
	0x00038		arguments   
	0x00039		push        ts+0x50
	0x0003a		push64      (bp-0x20)
	0x0003b		load32      0x0
	0x0003c		printf      
	0x0003d		arguments   
	0x0003e		push        ts+0x60
	0x0003f		push64      (bp-0x20)
	0x00040		load32      0x4
	0x00041		printf      
	0x00042		arguments   
	0x00043		push        ts+0x70
	0x00044		push64      (bp-0x20)
	0x00045		load32      0x8
	0x00046		printf      
	0x00047		add         sp, 0x8
	0x00048		push        bp-0x10
	0x00049		push        bss
	0x0004a		addptr      0x4
	0x0004b		store64     
	0x0004c		arguments   
	0x0004d		push        ts+0x20
	0x0004e		push64      (bp-0x10)
	0x0004f		load32      0x0
	0x00050		printf      
	0x00051		add         sp, 0x8
	0x00052		push        ap
	0x00053		push32      0x0
	0x00054		store32     
	0x00055		return      
```

And finally, `virtual.Exec` produces this [expected](https://github.com/cznic/cc/blob/9604c5ca5ff2a70e0e4e82ee5a3653219e34954b/testdata/tcc-0.9.26/tests/tests2/10_pointer.expect) output:


```
all_test.go:262: ../cc/testdata/tcc-0.9.26/tests/tests2/10_pointer.c: OK
	a = 42
	bolshevic.a = 12
	bolshevic.b = 34
	bolshevic.c = 56
	tsar->a = 12
	tsar->b = 34
	tsar->c = 56
	bolshevic.b = 34
```

----

Disclaimer: Tested on Linux/64bit only.

