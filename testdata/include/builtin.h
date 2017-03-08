#ifndef _BUILTIN_H_
#define _BUILTIN_H_

#if defined __MODEL_32__
#define __LONG_MAX__ 2147483647l
#define __SIZEOF_LONG__ 4
#define __SIZEOF_POINTER__ 4
#define __stackAlign 4
#elif defined __MODEL_64__
#define __LONG_MAX__ 9223372036854775807l
#define __SIZEOF_LONG__ 8
#define __SIZEOF_POINTER__ 8
#define __stackAlign 8
#else
#error
#endif

#define __CHAR_BIT__ 8
#define __FILE_TYPE__ struct{int _;}
#define __FUNCTION__ __func__
#define __INT16_TYPE__ short
#define __INT32_TYPE__ int
#define __INT_MAX__ 2147483647
#define __LONG_LONG_MAX__ 9223372036854775807ll
#define __PTRDIFF_TYPE__ long
#define __SIZEOF_INT__ 4
#define __SIZE_TYPE__ unsigned long
#define __UINT32_TYPE__ unsigned
#define __UINT64_TYPE__ unsigned long long
#define __WCHAR_TYPE__ int
#define __attribute__(x)
#define __builtin_expect(exp, c) (exp)
#define __builtin_prefetch(...)
#define __builtin_va_list char *
#define __complex _Complex
#define __complex__ _Complex
#define __const const
#define __extension__
#define __inline inline
#define __restrict restrict
#define __roundup(n, mod) ((n + mod - 1) & ~(mod - 1))

__FILE_TYPE__ *__stdstreams[3];

__FILE_TYPE__ *__builtin_fopen(const char *path, const char *mode);
__FILE_TYPE__ *__bultin_fopen(const char *path, const char *mode);
__SIZE_TYPE__ __builtin_fread(void *ptr, __SIZE_TYPE__ size,
			      __SIZE_TYPE__ nmemb, __FILE_TYPE__ * stream);
__SIZE_TYPE__ __builtin_fwrite(const void *ptr, __SIZE_TYPE__ size,
			       __SIZE_TYPE__ nmemb, __FILE_TYPE__ * stream);
__SIZE_TYPE__ __builtin_strlen(const char *s);
char *__builtin_fgets(char *s, int size, __FILE_TYPE__ * stream);
char *__builtin_strcat(char *dest, const char *src);
char *__builtin_strchr(const char *s, int c);
char *__builtin_strcpy(char *dest, const char *src);
char *__builtin_strncpy(char *dest, const char *src, __SIZE_TYPE__ n);
char *__builtin_strrchr(const char *s, int c);
double __builtin_acos(double x);
double __builtin_asin(double x);
double __builtin_atan(double x);
double __builtin_ceil(double x);
double __builtin_cos(double x);
double __builtin_cosh(double x);
double __builtin_exp(double x);
double __builtin_fabs(double x);
double __builtin_floor(double x);
double __builtin_log(double x);
double __builtin_log10(double x);
double __builtin_pow(double x, double y);
double __builtin_round(double x);
double __builtin_sin(double x);
double __builtin_sinh(double x);
double __builtin_sqrt(double x);
double __builtin_tan(double x);
double __builtin_tanh(double x);
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
int __builtin_fclose(__FILE_TYPE__ * stream);
int __builtin_ffs(int i);
int __builtin_ffsl(long i);
int __builtin_ffsll(long long i);
int __builtin_fgetc(__FILE_TYPE__ * stream);
int __builtin_fprintf(__FILE_TYPE__ * stream, const char *format, ...);
int __builtin_isprint(int c);
int __builtin_memcmp(const void *s1, const void *s2, __SIZE_TYPE__ n);
int __builtin_parity(unsigned x);
int __builtin_parityl(unsigned long x);
int __builtin_parityll(unsigned long long x);
int __builtin_popcount(unsigned x);
int __builtin_popcountl(unsigned long x);
int __builtin_popcountll(unsigned long long x);
int __builtin_printf(const char *format, ...);
int __builtin_sprintf(char *str, const char *format, ...);
int __builtin_strcmp(const char *s1, const char *s2);
int __builtin_strncmp(const char *s1, const char *s2, __SIZE_TYPE__ n);
int __builtin_tolower(int c);
void *__builtin_calloc(__SIZE_TYPE__ nmemb, __SIZE_TYPE__ size);
void *__builtin_malloc(__SIZE_TYPE__ size);
void *__builtin_memcpy(void *dest, const void *src, __SIZE_TYPE__ n);
void *__builtin_memset(void *s, int c, __SIZE_TYPE__ n);
void __builtin_abort(void);
void __builtin_exit(int status);
void __builtin_trap(void);

#endif				/* _BUILTIN_H_ */
