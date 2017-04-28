//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _BUILTIN_H_
#define _BUILTIN_H_

#include <predefined.h>

#define __FUNCTION__ __func__
#define __attribute(x)
#define __attribute__(x)
#define __builtin_choose_expr(a, b, c) (a) ? (b) : (c)
#define __builtin_expect(exp, c) (exp)
#define __builtin_offsetof(st, m) ((__SIZE_TYPE__)(&((st *)0)->m))
#define __builtin_prefetch(addr, ...) (void)(addr)
#define __builtin_signbit(x) (sizeof(x) == sizeof(float) ? __signbitf(x) : sizeof (x) == sizeof(double) ? __signbit(x) : __signbitl(x))
#define __builtin_types_compatible_p(type1, type2) __builtin_types_compatible__((type1){}, (type2){})
#define __builtin_va_arg(ap, type) *(type*)(ap -= (__UINTPTR_TYPE__)(__roundup(sizeof(type), __SIZEOF_POINTER__)))
#define __builtin_va_copy(dest, src) dest = src
#define __builtin_va_end(ap) ap = 0
#define __builtin_va_start(ap, arg) ap = (__builtin_va_list)(&arg)
#define __complex__ _Complex
#define __const const
#define __extension__
#define __inline inline
#define __restrict restrict
#define __roundup(n, mod) ((n + mod - 1) & ~(mod - 1))
#define __volatile volatile

typedef __builtin_va_list __gnuc_va_list;
typedef void *__FILE_TYPE__;
typedef void *__jmp_buf[7];

__FILE_TYPE__ __builtin_fopen(char *__filename, char *__modes);
__SIZE_TYPE__ __builtin_strlen(char *__s);
__UINT64_TYPE__ __builtin_bswap64(__UINT64_TYPE__ x);
char *__builtin_strchr(char *__s, int __c);
char *__builtin_strcpy(char *__dest, char *__src);
double __builtin_copysign(double x, double y);
int __builtin_abs(int j);
int __builtin_clrsb(int x);
int __builtin_clrsbl(long x);
int __builtin_clrsbll(long long x);
int __builtin_clz(unsigned x);
int __builtin_clzl(unsigned long x);
int __builtin_clzll(unsigned long long x);
int __builtin_ctz(unsigned x);
int __builtin_ctzl(unsigned long x);
int __builtin_ctzll(unsigned long long x);
int __builtin_ffs(int i);
int __builtin_ffsl(long i);
int __builtin_ffsll(long long i);
int __builtin_fprintf(void *__stream, char *__format, ...);
int __builtin_isprint(int);
int __builtin_memcmp(void *__s1, void *__s2, __SIZE_TYPE__ __n);
int __builtin_parity(unsigned x);
int __builtin_parityl(unsigned long x);
int __builtin_parityll(unsigned long long x);
int __builtin_popcount(unsigned x);
int __builtin_popcountl(unsigned long x);
int __builtin_popcountll(unsigned long long x);
int __builtin_printf(char *__format, ...);
int __builtin_setjmp(void *__env);
int __builtin_sprintf(char *__s, char *__format, ...);
int __builtin_strcmp(char *__s1, char *__s2);
int __signbit(double x);
int __signbitf(float x);
void *__builtin_alloca(__SIZE_TYPE__ __size);
void *__builtin_frame_address(unsigned int level);
void *__builtin_malloc(__SIZE_TYPE__ __size);
void *__builtin_memcpy(void *dest, const void *src, __SIZE_TYPE__ n);
void *__builtin_memset(void *s, int c, __SIZE_TYPE__ n);
void *__builtin_return_address(unsigned int level);
void __builtin_abort(void);
void __builtin_exit(int __status);
void __builtin_longjmp(void *__env, int __val);
void __builtin_trap(void);
void __register_stdfiles(void *, void *, void *);

#ifdef _WIN32
#ifndef _WIN64
#define InterlockedCompareExchange(d,e,c) _InterlockedCompareExchange(d,e,c)
#endif

long _InterlockedCompareExchange(long volatile * Destination,  long Exchange, long Comparand);
#endif

#endif				/* _BUILTIN_H_ */
