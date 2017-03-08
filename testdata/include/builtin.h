#ifndef _BUILTIN_H_
#define _BUILTIN_H_

#if defined __MODEL_32__
#define __LONG_MAX__ 2147483647l
#define __SIZEOF_LONG__ 4
#define __SIZEOF_POINTER__ 4
#elif defined __MODEL_64__
#define __LONG_MAX__ 9223372036854775807l
#define __SIZEOF_LONG__ 8
#define __SIZEOF_POINTER__ 8
#else
#error
#endif

#define __CHAR_BIT__ 8
#define __FUNCTION__ __func__
#define __INT16_TYPE__ short
#define __INT32_TYPE__ int
#define __INT_MAX__ 2147483647
#define __LONG_LONG_MAX__ 9223372036854775807ll
#define __PTRDIFF_TYPE__ long
#define __SIZEOF_INT__ 4
#define __UINT32_TYPE__ unsigned
#define __attribute__(x)
#define __builtin_expect(exp, c) (exp)
#define __complex _Complex
#define __complex__ _Complex
#define __const const
#define __extension__
#define __inline inline
#define __restrict restrict

typedef char *__builtin_va_list;
typedef unsigned long __SIZE_TYPE__;

__SIZE_TYPE__ __builtin_strlen(const char *s);
char *__builtin_strcpy(char *dest, const char *src);
double __builtin_fabs(double x);
int __builtin_clz(unsigned x);
int __builtin_ctz(unsigned x);
int __builtin_ffs(int i);
int __builtin_isprint(int c);
int __builtin_memcmp(const void *s1, const void *s2, size_t n);
int __builtin_printf(const char *format, ...);
int __builtin_strcmp(const char *s1, const char *s2);
int __builtin_strncmp(const char *s1, const char *s2, size_t n);
void *__builtin_malloc(size_t size);
void *__builtin_memcpy(void *dest, const void *src, size_t n);
void *__builtin_memset(void *s, int c, size_t n);
void __builtin_abort(void);
void __builtin_trap(void);

#endif				/* _BUILTIN_H_ */
