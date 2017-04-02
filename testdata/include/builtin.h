#ifndef _BUILTIN_H_
#define _BUILTIN_H_

#if \
	defined __arch_386__ || \
	defined __arch_arm64be__ || \
	defined __arch_arm__ || \
	defined __arch_armbe__ || \
	defined __arch_mips__ || \
	defined __arch_mipsle__ || \
	defined __arch_ppc64le__ || \
	defined __arch_ppc__ || \
	defined __arch_s390__ || \
	defined __arch_s390x__ || \
	defined __arch_sparc__
#define __LONG_MAX__ 2147483647l
#define __SIZEOF_LONG__ 4
#define __SIZEOF_POINTER__ 4
#define __ULONG_MAX__ 4294967295ul
#define __stackAlign 4
#elif \
	defined __arch_amd64__ || \
	defined __arch_amd64p32__ || \
	defined __arch_arm64__ || \
	defined __arch_mips64__ || \
	defined __arch_mips64le__ || \
	defined __arch_mips64p32__ || \
	defined __arch_mips64p32le__ || \
	defined __arch_ppc64__ || \
defined __arch_sparc64__
#define __LONG_MAX__ 9223372036854775807l
#define __SIZEOF_LONG__ 8
#define __SIZEOF_POINTER__ 8
#define __ULONG_MAX__ 18446744073709551615ul
#define __stackAlign 8
#else
#error
#endif

#if \
	defined __arch_386__ || \
	defined __arch_amd64__ || \
	defined __arch_amd64p32__ || \
	defined __arch_arm64__ || \
	defined __arch_arm__ || \
	defined __arch_mips64le__ || \
	defined __arch_mips64p32le__ || \
	defined __arch_mipsle__ || \
	defined __arch_ppc64le__ || \
	defined __arch_s390__ || \
	defined __arch_s390x__ || \
	defined __arch_sparc64__ || \
	defined __arch_sparc__
#define __BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__
#elif \
	defined __arch_arm64be__ || \
	defined __arch_armbe__ || \
	defined __arch_mips64__ || \
	defined __arch_mips64p32__ || \
	defined __arch_mips__ || \
	defined __arch_ppc64__
defined __arch_ppc__ ||
#define __BYTE_ORDER__ __ORDER_BIG_ENDIAN__
#error
#endif
#define __BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__
#define __CHAR_BIT__ 8
#define __DBL_MANT_DIG__ 53
#define __DBL_MAX__ 1.79769313486231570815e+308
#define __DBL_MIN__ 2.22507385850720138309e-308
#define __FILE_TYPE__ struct{int _;}
#define __FLT_MAX__ 3.40282346638528859812e+38F
#define __FLT_MIN__ 1.17549435082228750797e-38F
#define __FUNCTION__ __func__
#define __INT16_TYPE__ short
#define __INT32_TYPE__ int
#define __INT8_TYPE__ char
#define __INT8_TYPE__ char
#define __INTPTR_TYPE__ long
#define __INT_LEAST8_TYPE__ __INT8_TYPE__
#define __INT_MAX__ 2147483647
#define __LDBL_MAX__ 1.79769313486231570815e+308
#define __LDBL_MIN__ 2.22507385850720138309e-308
#define __LOCALE_TYPE__ struct{int _;}
#define __LONG_LONG_MAX__ 9223372036854775807ll
#define __ORDER_BIG_ENDIAN__ 2
#define __ORDER_LITTLE_ENDIAN__ 1
#define __PTRDIFF_TYPE__ long
#define __SIZEOF_INT__ 4
#define __SIZE_TYPE__ unsigned long
#define __SSIZE_TYPE__ long
#define __UINT32_TYPE__ unsigned
#define __UINT64_TYPE__ unsigned long long
#define __UINT8_TYPE__ unsigned char
#define __UINTPTR_TYPE__ unsigned long
#define __UINT_LEAST32_TYPE__ __UINT32_TYPE__
#define __WCHAR_TYPE__ int
#define __attribute(x)
#define __attribute__(x)
#define __builtin_choose_expr(a, b, c) (a) ? (b) : (c)
#define __builtin_expect(exp, c) (exp)
#define __builtin_offsetof(st, m) ((__SIZE_TYPE__)(&((st *)0)->m))
#define __builtin_prefetch(addr, ...) (void)(addr)
#define __builtin_signbit(x) (sizeof(x) == sizeof(float) ? __builtin_sign_bitf(x) : __builtin_sign_bit(x))
#define __builtin_types_compatible_p(type1, type2) __builtin_types_compatible__((type1){}, (type2){})
#define __builtin_va_arg(ap, type) *(type*)(ap -= __roundup(sizeof(type), __stackAlign))
#define __builtin_va_copy(dest, src) dest = src
#define __builtin_va_end(ap) ap = 0
#define __builtin_va_list char *
#define __builtin_va_start(ap, arg) ap = (__builtin_va_list)(&arg)
#define __complex _Complex
#define __complex__ _Complex
#define __const const
#define __extension__
#define __inline inline
#define __restrict restrict
#define __roundup(n, mod) ((n + mod - 1) & ~(mod - 1))
#define __volatile volatile
typedef void *__JMP_BUF_TYPE__[7];

__FILE_TYPE__ *__stdstreams[3];

__FILE_TYPE__ *__builtin_fopen(const char *path, const char *mode);
__FILE_TYPE__ *__bultin_fopen(const char *path, const char *mode);
__SIZE_TYPE__ __builtin_fread(void *ptr, __SIZE_TYPE__ size, __SIZE_TYPE__ nmemb, __FILE_TYPE__ * stream);
__SIZE_TYPE__ __builtin_fwrite(const void *ptr, __SIZE_TYPE__ size, __SIZE_TYPE__ nmemb, __FILE_TYPE__ * stream);
__SIZE_TYPE__ __builtin_strlen(const char *s);
__SSIZE_TYPE__ __builtin_read(int fd, void *buf, __SIZE_TYPE__ count);
__SSIZE_TYPE__ __builtin_write(int fd, const void *buf, __SIZE_TYPE__ count);
__UINT64_TYPE__ __builtin_bswap64(__UINT64_TYPE__ x);
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
double __builtin_copysign(double x, double y);
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
float __builtin_cimagf(float _Complex z);
float __builtin_crealf(float _Complex z);
int __builtin_abs(int j);
int __builtin_close(int fd);
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
int __builtin_isinf(double x);
int __builtin_isinff(float x);
int __builtin_isinfl(long double x);
int __builtin_isprint(int c);
int __builtin_memcmp(const void *s1, const void *s2, __SIZE_TYPE__ n);
int __builtin_open(const char *pathname, int flags, ...);
int __builtin_parity(unsigned x);
int __builtin_parityl(unsigned long x);
int __builtin_parityll(unsigned long long x);
int __builtin_popcount(unsigned x);
int __builtin_popcountl(unsigned long x);
int __builtin_popcountll(unsigned long long x);
int __builtin_printf(const char *format, ...);
int __builtin_setjmp(void *env);
int __builtin_sign_bit(double x);
int __builtin_sign_bitf(float x);
int __builtin_sprintf(char *str, const char *format, ...);
int __builtin_strcmp(const char *s1, const char *s2);
int __builtin_strncmp(const char *s1, const char *s2, __SIZE_TYPE__ n);
int __builtin_tolower(int c);
int __builtin_vfprintf(__FILE_TYPE__ * stream, const char *format, __builtin_va_list ap);
int __builtin_vprintf(const char *format, __builtin_va_list ap);
void *__builtin_alloca(__SIZE_TYPE__ size);
void *__builtin_calloc(__SIZE_TYPE__ nmemb, __SIZE_TYPE__ size);
void *__builtin_frame_address(unsigned int level);
void *__builtin_malloc(__SIZE_TYPE__ size);
void *__builtin_memcpy(void *dest, const void *src, __SIZE_TYPE__ n);
void *__builtin_memmove(void *dest, const void *src, __SIZE_TYPE__ n);
void *__builtin_mempcpy(void *dest, const void *src, __SIZE_TYPE__ n);
void *__builtin_memset(void *s, int c, __SIZE_TYPE__ n);
void *__builtin_return_address(unsigned int level);
void __builtin_abort(void);
void __builtin_exit(int status);
void __builtin_free(void *ptr);
void __builtin_longjmp(void *env, int val);
void __builtin_qsort(void *base, __SIZE_TYPE__ nmemb, __SIZE_TYPE__ size, int (*compar) (const void *, const void *));
void __builtin_trap(void);

#endif				/* _BUILTIN_H_ */
