// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

	typedef unsigned long long size_t ;
typedef long long ssize_t ;
typedef size_t rsize_t ;
typedef long long intptr_t ;
typedef unsigned long long uintptr_t ;
typedef long long ptrdiff_t ;
typedef unsigned short wchar_t ;
typedef unsigned short wint_t ;
typedef unsigned short wctype_t ;
typedef int errno_t ;
typedef long __time32_t ;
typedef long long __time64_t ;
typedef __time64_t time_t ;
struct threadlocaleinfostruct ;
struct threadmbcinfostruct ;
typedef struct threadlocaleinfostruct *pthreadlocinfo ;
typedef struct threadmbcinfostruct *pthreadmbcinfo ;
struct __lc_time_data ;
typedef struct localeinfo_struct {pthreadlocinfo locinfo ;pthreadmbcinfo mbcinfo ;}_locale_tstruct ;
typedef struct localeinfo_struct {pthreadlocinfo locinfo ;pthreadmbcinfo mbcinfo ;}*_locale_t ;

typedef struct tagLC_ID {unsigned short wLanguage ;unsigned short wCountry ;unsigned short wCodePage ;}LC_ID ;
typedef struct tagLC_ID {unsigned short wLanguage ;unsigned short wCountry ;unsigned short wCodePage ;}*LPLC_ID ;

typedef struct threadlocaleinfostruct {int refcount ;unsigned int lc_codepage ;unsigned int lc_collate_cp ;unsigned long lc_handle [6 ];LC_ID lc_id [6 ];struct {char *locale ;wchar_t *wlocale ;int *refcount ;int *wrefcount ;}lc_category [6 ];int lc_clike ;int mb_cur_max ;int *lconv_intl_refcount ;int *lconv_num_refcount ;int *lconv_mon_refcount ;struct lconv *lconv ;int *ctype1_refcount ;unsigned short *ctype1 ;const unsigned short *pctype ;const unsigned char *pclmap ;const unsigned char *pcumap ;struct __lc_time_data *lc_time_curr ;}threadlocinfo ;
// m:\mingw\x86_64-w64-mingw32\include\time.h

typedef long clock_t ;
struct tm {int tm_sec ;int tm_min ;int tm_hour ;int tm_mday ;int tm_mon ;int tm_year ;int tm_wday ;int tm_yday ;int tm_isdst ;};
int _daylight ;
long _dstbias ;
long _timezone ;
char *_tzname [2 ];
errno_t _get_daylight (int *_Daylight );
errno_t _get_dstbias (long *_Daylight_savings_bias );
errno_t _get_timezone (long *_Timezone );
errno_t _get_tzname (size_t *_ReturnValue ,char *_Buffer ,size_t _SizeInBytes ,int _Index );
char *asctime (const struct tm *_Tm );
errno_t asctime_s (char *_Buf ,size_t _SizeInWords ,const struct tm *_Tm );
char *_ctime32 (const __time32_t *_Time );
errno_t _ctime32_s (char *_Buf ,size_t _SizeInBytes ,const __time32_t *_Time );
clock_t clock (void );
double _difftime32 (__time32_t _Time1 ,__time32_t _Time2 );
struct tm *_gmtime32 (const __time32_t *_Time );
errno_t _gmtime32_s (struct tm *_Tm ,const __time32_t *_Time );
struct tm *_localtime32 (const __time32_t *_Time );
errno_t _localtime32_s (struct tm *_Tm ,const __time32_t *_Time );
size_t strftime (char *_Buf ,size_t _SizeInBytes ,const char *_Format ,const struct tm *_Tm );
size_t _strftime_l (char *_Buf ,size_t _Max_size ,const char *_Format ,const struct tm *_Tm ,_locale_t _Locale );
char *_strdate (char *_Buffer );
errno_t _strdate_s (char *_Buf ,size_t _SizeInBytes );
char *_strtime (char *_Buffer );
errno_t _strtime_s (char *_Buf ,size_t _SizeInBytes );
__time32_t _time32 (__time32_t *_Time );
__time32_t _mktime32 (struct tm *_Tm );
__time32_t _mkgmtime32 (struct tm *_Tm );
void _tzset (void );
double _difftime64 (__time64_t _Time1 ,__time64_t _Time2 );
char *_ctime64 (const __time64_t *_Time );
errno_t _ctime64_s (char *_Buf ,size_t _SizeInBytes ,const __time64_t *_Time );
struct tm *_gmtime64 (const __time64_t *_Time );
errno_t _gmtime64_s (struct tm *_Tm ,const __time64_t *_Time );
struct tm *_localtime64 (const __time64_t *_Time );
errno_t _localtime64_s (struct tm *_Tm ,const __time64_t *_Time );
__time64_t _mktime64 (struct tm *_Tm );
__time64_t _mkgmtime64 (struct tm *_Tm );
__time64_t _time64 (__time64_t *_Time );
unsigned _getsystime (struct tm *_Tm );
unsigned _setsystime (struct tm *_Tm ,unsigned _MilliSec );
wchar_t *_wasctime (const struct tm *_Tm );
errno_t _wasctime_s (wchar_t *_Buf ,size_t _SizeInWords ,const struct tm *_Tm );
wchar_t *_wctime32 (const __time32_t *_Time );
errno_t _wctime32_s (wchar_t *_Buf ,size_t _SizeInWords ,const __time32_t *_Time );
size_t wcsftime (wchar_t *_Buf ,size_t _SizeInWords ,const wchar_t *_Format ,const struct tm *_Tm );
size_t _wcsftime_l (wchar_t *_Buf ,size_t _SizeInWords ,const wchar_t *_Format ,const struct tm *_Tm ,_locale_t _Locale );
wchar_t *_wstrdate (wchar_t *_Buffer );
errno_t _wstrdate_s (wchar_t *_Buf ,size_t _SizeInWords );
wchar_t *_wstrtime (wchar_t *_Buffer );
errno_t _wstrtime_s (wchar_t *_Buf ,size_t _SizeInWords );
wchar_t *_wctime64 (const __time64_t *_Time );
errno_t _wctime64_s (wchar_t *_Buf ,size_t _SizeInWords ,const __time64_t *_Time );
wchar_t *_wctime (const time_t *);
errno_t _wctime_s (wchar_t *,size_t ,const time_t *);
double difftime (time_t _Time1 ,time_t _Time2 );
char *ctime (const time_t *_Time );
struct tm *gmtime (const time_t *_Time );
struct tm *localtime (const time_t *_Time );
time_t mktime (struct tm *_Tm );
time_t _mkgmtime (struct tm *_Tm );
time_t time (time_t *_Time );
extern int daylight ;
extern long timezone ;
extern char *tzname [2 ];
void tzset (void );
// m:\mingw\x86_64-w64-mingw32\include\_timeval.h

struct timeval {long tv_sec ;long tv_usec ;};
// m:\mingw\x86_64-w64-mingw32\include\time.h

struct timezone {int tz_minuteswest ;int tz_dsttime ;};
extern int mingw_gettimeofday (struct timeval *p ,struct timezone *z );
// m:\mingw\x86_64-w64-mingw32\include\sys\time.h

int gettimeofday (struct timeval *,void *);
#define CLK_TCK CLOCKS_PER_SEC
#define CLOCKS_PER_SEC (1000)
#define NULL ( ( void * ) 0 )
#define _CLOCK_T_DEFINED 
#define _CRTNOALIAS 
#define _CRTRESTRICT 
#define _CRT_PACKING (8)
#define _CRT_SECURE_CPP_NOTHROW throw ( )
#define _ERRCODE_DEFINED 
#define _GETTIMEOFDAY_DEFINED 
#define _INC_CRTDEFS 
#define _INC_WTIME_INL 
#define _INC_WTIME_S_INL 
#define _INTPTR_T_DEFINED 
#define _PTRDIFF_T_ 
#define _PTRDIFF_T_DEFINED 
#define _RSIZE_T_DEFINED 
#define _SIZE_T_DEFINED 
#define _SSIZE_T_DEFINED 
#define _SYS_TIME_H_ 
#define _TAGLC_ID_DEFINED 
#define _THREADLOCALEINFO 
#define _TIME32_T_DEFINED 
#define _TIME64_T_DEFINED 
#define _TIMEVAL_DEFINED 
#define _TIMEZONE_DEFINED 
#define _TIME_H_ 
#define _TIME_T_DEFINED 
#define _TM_DEFINED 
#define _UINTPTR_T_DEFINED 
#define _WCHAR_T_DEFINED 
#define _WCTYPE_T_DEFINED 
#define _WINT_T 
#define _WTIME_DEFINED 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(__ret, __func, __dsttype, __dst) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(__ret, __func, __dsttype, __dst, __type1, __arg1) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(__ret, __func, __vfunc, __dsttype, __dst, __type1, __arg1) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(__ret, __func, __dsttype, __dst, __type1, __arg1, __type2, __arg2) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(__ret, __func, __vfunc, __dsttype, __dst, __type1, __arg1, __type2, __arg2) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(__ret, __func, __dsttype, __dst, __type1, __arg1, __type2, __arg2, __type3, __arg3) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(__ret, __func, __dsttype, __dst, __type1, __arg1, __type2, __arg2, __type3, __arg3, __type4, __arg4) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(__ret, __func, __type0, __arg0, __dsttype, __dst, __type1, __arg1) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(__ret, __func, __type0, __arg0, __dsttype, __dst, __type1, __arg1, __type2, __arg2) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(__ret, __func, __type0, __arg0, __dsttype, __dst, __type1, __arg1, __type2, __arg2, __type3, __arg3) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(__ret, __func, __type1, __arg1, __type2, __arg2, __dsttype, __dst) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(__ret, __func, __dsttype, __src) 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst )
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst) 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst , __arg1_type , __arg1 , __arg2_type , __arg2 )
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1) 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst , __arg1_type , __arg1 , __arg2_type , __arg2 )
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2) 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2, __arg3_type, __arg3) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst , __arg1_type , __arg1 , __arg2_type , __arg2 , __arg3_type , __arg3 )
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2, __arg3_type, __arg3) 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2, __arg3_type, __arg3, __arg4_type, __arg4) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst , __arg1_type , __arg1 , __arg2_type , __arg2 , __arg3_type , __arg3 , __arg4_type , __arg4 )
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2, __arg3_type, __arg3, __arg4_type, __arg4) 
#define __crt_typefix(ctype) 
#define __intptr_t_defined 
#define __uintptr_t_defined 
#define timerclear(tvp) ( tvp ) -> tv_sec = ( tvp ) -> tv_usec = 0
#define timercmp(tvp, uvp, cmp) ( ( tvp ) -> tv_sec cmp ( uvp ) -> tv_sec || ( ( tvp ) -> tv_sec == ( uvp ) -> tv_sec && ( tvp ) -> tv_usec cmp ( uvp ) -> tv_usec ) )
#define timerisset(tvp) ( ( tvp ) -> tv_sec || ( tvp ) -> tv_usec )
