// Code generated by running "go generate". DO NOT EDIT.

	// +build ignore
	
	// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

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
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

typedef int (*_onexit_t )(void );
typedef struct _div_t {int quot ;int rem ;}div_t ;
typedef struct _ldiv_t {long quot ;long rem ;}ldiv_t ;
typedef struct {unsigned char ld [10 ];}_LDOUBLE ;
typedef struct {double x ;}_CRT_DOUBLE ;
typedef struct {float f ;}_CRT_FLOAT ;
typedef struct {long double x ;}_LONGDOUBLE ;
typedef struct {unsigned char ld12 [12 ];}_LDBL12 ;
extern int *__imp___mb_cur_max ;
typedef void (*_purecall_handler )(void );
_purecall_handler _set_purecall_handler (_purecall_handler _Handler );
_purecall_handler _get_purecall_handler (void );
typedef void (*_invalid_parameter_handler )(const wchar_t *,const wchar_t *,const wchar_t *,unsigned int ,uintptr_t );
_invalid_parameter_handler _set_invalid_parameter_handler (_invalid_parameter_handler _Handler );
_invalid_parameter_handler _get_invalid_parameter_handler (void );
extern int *_errno (void );
errno_t _set_errno (int _Value );
errno_t _get_errno (int *_Value );
unsigned long *__doserrno (void );
errno_t _set_doserrno (unsigned long _Value );
errno_t _get_doserrno (unsigned long *_Value );
extern char *_sys_errlist [1 ];
extern int _sys_nerr ;
extern int *__imp___argc ;
extern char ***__imp___argv ;
extern wchar_t ***__imp___wargv ;
extern char ***__imp__environ ;
extern wchar_t ***__imp__wenviron ;
extern char **__imp__pgmptr ;
extern wchar_t **__imp__wpgmptr ;
errno_t _get_pgmptr (char **_Value );
errno_t _get_wpgmptr (wchar_t **_Value );
extern int *__imp__fmode ;
errno_t _set_fmode (int _Mode );
errno_t _get_fmode (int *_PMode );
extern unsigned int *__imp__osplatform ;
extern unsigned int *__imp__osver ;
extern unsigned int *__imp__winver ;
extern unsigned int *__imp__winmajor ;
extern unsigned int *__imp__winminor ;
errno_t _get_osplatform (unsigned int *_Value );
errno_t _get_osver (unsigned int *_Value );
errno_t _get_winver (unsigned int *_Value );
errno_t _get_winmajor (unsigned int *_Value );
errno_t _get_winminor (unsigned int *_Value );
void exit (int _Code );
void _exit (int _Code );
void _Exit (int );
void abort (void );
unsigned int _set_abort_behavior (unsigned int _Flags ,unsigned int _Mask );
int abs (int _X );
long labs (long _X );
long long _abs64 (long long );
int atexit (void (*)(void ));
double atof (const char *_String );
double _atof_l (const char *_String ,_locale_t _Locale );
int atoi (const char *_Str );
int _atoi_l (const char *_Str ,_locale_t _Locale );
long atol (const char *_Str );
long _atol_l (const char *_Str ,_locale_t _Locale );
void *bsearch (const void *_Key ,const void *_Base ,size_t _NumOfElements ,size_t _SizeOfElements ,int (*_PtFuncCompare )(const void *,const void *));
void qsort (void *_Base ,size_t _NumOfElements ,size_t _SizeOfElements ,int (*_PtFuncCompare )(const void *,const void *));
unsigned short _byteswap_ushort (unsigned short _Short );
unsigned long _byteswap_ulong (unsigned long _Long );
unsigned long long _byteswap_uint64 (unsigned long long _Int64 );
div_t div (int _Numerator ,int _Denominator );
char *getenv (const char *_VarName );
char *_itoa (int _Value ,char *_Dest ,int _Radix );
char *_i64toa (long long _Val ,char *_DstBuf ,int _Radix );
char *_ui64toa (unsigned long long _Val ,char *_DstBuf ,int _Radix );
long long _atoi64 (const char *_String );
long long _atoi64_l (const char *_String ,_locale_t _Locale );
long long _strtoi64 (const char *_String ,char **_EndPtr ,int _Radix );
long long _strtoi64_l (const char *_String ,char **_EndPtr ,int _Radix ,_locale_t _Locale );
unsigned long long _strtoui64 (const char *_String ,char **_EndPtr ,int _Radix );
unsigned long long _strtoui64_l (const char *_String ,char **_EndPtr ,int _Radix ,_locale_t _Locale );
ldiv_t ldiv (long _Numerator ,long _Denominator );
char *_ltoa (long _Value ,char *_Dest ,int _Radix );
int mblen (const char *_Ch ,size_t _MaxCount );
int _mblen_l (const char *_Ch ,size_t _MaxCount ,_locale_t _Locale );
size_t _mbstrlen (const char *_Str );
size_t _mbstrlen_l (const char *_Str ,_locale_t _Locale );
size_t _mbstrnlen (const char *_Str ,size_t _MaxCount );
size_t _mbstrnlen_l (const char *_Str ,size_t _MaxCount ,_locale_t _Locale );
int mbtowc (wchar_t *_DstCh ,const char *_SrcCh ,size_t _SrcSizeInBytes );
int _mbtowc_l (wchar_t *_DstCh ,const char *_SrcCh ,size_t _SrcSizeInBytes ,_locale_t _Locale );
size_t mbstowcs (wchar_t *_Dest ,const char *_Source ,size_t _MaxCount );
size_t _mbstowcs_l (wchar_t *_Dest ,const char *_Source ,size_t _MaxCount ,_locale_t _Locale );
int mkstemp (char *template_name );
int rand (void );
int _set_error_mode (int _Mode );
void srand (unsigned int _Seed );
double strtod (const char *_Str ,char **_EndPtr );
float strtof (const char *nptr ,char **endptr );
long double strtold (const char *,char **);
extern double __strtod (const char *,char **);
float __mingw_strtof (const char *,char **);
double __mingw_strtod (const char *,char **);
long double __mingw_strtold (const char *,char **);
double _strtod_l (const char *_Str ,char **_EndPtr ,_locale_t _Locale );
long strtol (const char *_Str ,char **_EndPtr ,int _Radix );
long _strtol_l (const char *_Str ,char **_EndPtr ,int _Radix ,_locale_t _Locale );
unsigned long strtoul (const char *_Str ,char **_EndPtr ,int _Radix );
unsigned long _strtoul_l (const char *_Str ,char **_EndPtr ,int _Radix ,_locale_t _Locale );
int system (const char *_Command );
char *_ultoa (unsigned long _Value ,char *_Dest ,int _Radix );
int wctomb (char *_MbCh ,wchar_t _WCh );
int _wctomb_l (char *_MbCh ,wchar_t _WCh ,_locale_t _Locale );
size_t wcstombs (char *_Dest ,const wchar_t *_Source ,size_t _MaxCount );
size_t _wcstombs_l (char *_Dest ,const wchar_t *_Source ,size_t _MaxCount ,_locale_t _Locale );
void *calloc (size_t _NumOfElements ,size_t _SizeOfElements );
void free (void *_Memory );
void *malloc (size_t _Size );
void *realloc (void *_Memory ,size_t _NewSize );
void *_recalloc (void *_Memory ,size_t _Count ,size_t _Size );
void _aligned_free (void *_Memory );
void *_aligned_malloc (size_t _Size ,size_t _Alignment );
void *_aligned_offset_malloc (size_t _Size ,size_t _Alignment ,size_t _Offset );
void *_aligned_realloc (void *_Memory ,size_t _Size ,size_t _Alignment );
void *_aligned_recalloc (void *_Memory ,size_t _Count ,size_t _Size ,size_t _Alignment );
void *_aligned_offset_realloc (void *_Memory ,size_t _Size ,size_t _Alignment ,size_t _Offset );
void *_aligned_offset_recalloc (void *_Memory ,size_t _Count ,size_t _Size ,size_t _Alignment ,size_t _Offset );
wchar_t *_itow (int _Value ,wchar_t *_Dest ,int _Radix );
wchar_t *_ltow (long _Value ,wchar_t *_Dest ,int _Radix );
wchar_t *_ultow (unsigned long _Value ,wchar_t *_Dest ,int _Radix );
double __mingw_wcstod (const wchar_t *_Str ,wchar_t **_EndPtr );
float __mingw_wcstof (const wchar_t *nptr ,wchar_t **endptr );
long double __mingw_wcstold (const wchar_t *,wchar_t **);
double wcstod (const wchar_t *_Str ,wchar_t **_EndPtr );
float wcstof (const wchar_t *nptr ,wchar_t **endptr );
long double wcstold (const wchar_t *,wchar_t **);
double _wcstod_l (const wchar_t *_Str ,wchar_t **_EndPtr ,_locale_t _Locale );
long wcstol (const wchar_t *_Str ,wchar_t **_EndPtr ,int _Radix );
long _wcstol_l (const wchar_t *_Str ,wchar_t **_EndPtr ,int _Radix ,_locale_t _Locale );
unsigned long wcstoul (const wchar_t *_Str ,wchar_t **_EndPtr ,int _Radix );
unsigned long _wcstoul_l (const wchar_t *_Str ,wchar_t **_EndPtr ,int _Radix ,_locale_t _Locale );
wchar_t *_wgetenv (const wchar_t *_VarName );
int _wsystem (const wchar_t *_Command );
double _wtof (const wchar_t *_Str );
double _wtof_l (const wchar_t *_Str ,_locale_t _Locale );
int _wtoi (const wchar_t *_Str );
int _wtoi_l (const wchar_t *_Str ,_locale_t _Locale );
long _wtol (const wchar_t *_Str );
long _wtol_l (const wchar_t *_Str ,_locale_t _Locale );
wchar_t *_i64tow (long long _Val ,wchar_t *_DstBuf ,int _Radix );
wchar_t *_ui64tow (unsigned long long _Val ,wchar_t *_DstBuf ,int _Radix );
long long _wtoi64 (const wchar_t *_Str );
long long _wtoi64_l (const wchar_t *_Str ,_locale_t _Locale );
long long _wcstoi64 (const wchar_t *_Str ,wchar_t **_EndPtr ,int _Radix );
long long _wcstoi64_l (const wchar_t *_Str ,wchar_t **_EndPtr ,int _Radix ,_locale_t _Locale );
unsigned long long _wcstoui64 (const wchar_t *_Str ,wchar_t **_EndPtr ,int _Radix );
unsigned long long _wcstoui64_l (const wchar_t *_Str ,wchar_t **_EndPtr ,int _Radix ,_locale_t _Locale );
int _putenv (const char *_EnvString );
int _wputenv (const wchar_t *_EnvString );
char *_fullpath (char *_FullPath ,const char *_Path ,size_t _SizeInBytes );
char *_ecvt (double _Val ,int _NumOfDigits ,int *_PtDec ,int *_PtSign );
char *_fcvt (double _Val ,int _NumOfDec ,int *_PtDec ,int *_PtSign );
char *_gcvt (double _Val ,int _NumOfDigits ,char *_DstBuf );
int _atodbl (_CRT_DOUBLE *_Result ,char *_Str );
int _atoldbl (_LDOUBLE *_Result ,char *_Str );
int _atoflt (_CRT_FLOAT *_Result ,char *_Str );
int _atodbl_l (_CRT_DOUBLE *_Result ,char *_Str ,_locale_t _Locale );
int _atoldbl_l (_LDOUBLE *_Result ,char *_Str ,_locale_t _Locale );
int _atoflt_l (_CRT_FLOAT *_Result ,char *_Str ,_locale_t _Locale );
unsigned long _lrotl (unsigned long ,int );
unsigned long _lrotr (unsigned long ,int );
void _makepath (char *_Path ,const char *_Drive ,const char *_Dir ,const char *_Filename ,const char *_Ext );
_onexit_t _onexit (_onexit_t _Func );
void perror (const char *_ErrMsg );
unsigned long long _rotl64 (unsigned long long _Val ,int _Shift );
unsigned long long _rotr64 (unsigned long long Value ,int Shift );
unsigned int _rotr (unsigned int _Val ,int _Shift );
unsigned int _rotl (unsigned int _Val ,int _Shift );
unsigned long long _rotr64 (unsigned long long _Val ,int _Shift );
void _searchenv (const char *_Filename ,const char *_EnvVar ,char *_ResultPath );
void _splitpath (const char *_FullPath ,char *_Drive ,char *_Dir ,char *_Filename ,char *_Ext );
void _swab (char *_Buf1 ,char *_Buf2 ,int _SizeInBytes );
wchar_t *_wfullpath (wchar_t *_FullPath ,const wchar_t *_Path ,size_t _SizeInWords );
void _wmakepath (wchar_t *_ResultPath ,const wchar_t *_Drive ,const wchar_t *_Dir ,const wchar_t *_Filename ,const wchar_t *_Ext );
void _wperror (const wchar_t *_ErrMsg );
void _wsearchenv (const wchar_t *_Filename ,const wchar_t *_EnvVar ,wchar_t *_ResultPath );
void _wsplitpath (const wchar_t *_FullPath ,wchar_t *_Drive ,wchar_t *_Dir ,wchar_t *_Filename ,wchar_t *_Ext );
void _beep (unsigned _Frequency ,unsigned _Duration );
void _seterrormode (int _Mode );
void _sleep (unsigned long _Duration );
char *ecvt (double _Val ,int _NumOfDigits ,int *_PtDec ,int *_PtSign );
char *fcvt (double _Val ,int _NumOfDec ,int *_PtDec ,int *_PtSign );
char *gcvt (double _Val ,int _NumOfDigits ,char *_DstBuf );
char *itoa (int _Val ,char *_DstBuf ,int _Radix );
char *ltoa (long _Val ,char *_DstBuf ,int _Radix );
int putenv (const char *_EnvString );
void swab (char *_Buf1 ,char *_Buf2 ,int _SizeInBytes );
char *ultoa (unsigned long _Val ,char *_Dstbuf ,int _Radix );
_onexit_t onexit (_onexit_t _Func );
typedef struct {long long quot ,rem ;}lldiv_t ;
lldiv_t lldiv (long long ,long long );
long long llabs (long long );
long long strtoll (const char *,char **__restrict ,int );
unsigned long long strtoull (const char *,char **,int );
long long atoll (const char *);
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _OUT_TO_STDERR (1)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _INC_CRTDEFS 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define strtod __strtod
#define _CRT_PERROR_DEFINED 
#define ___mb_cur_max_func() ( __mb_cur_max )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _INTPTR_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define EXIT_SUCCESS (0)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(__ret, __func, __dsttype, __dst, __type1, __arg1, __type2, __arg2) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define onexit_t _onexit_t
#define __min(a, b) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1) 
#define __uintptr_t_defined 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _MAX_ENV (32767)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(__ret, __func, __dsttype, __dst, __type1, __arg1, __type2, __arg2, __type3, __arg3, __type4, __arg4) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _WSTDLIBP_DEFINED 
#define _CRT_ALGO_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2, __arg3_type, __arg3) 
#define _CRT_SECURE_CPP_NOTHROW throw ( )
#define _TIME32_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _osplatform ( * __MINGW_IMP_SYMBOL ( _osplatform ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _PTRDIFF_T_ 
#define __intptr_t_defined 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2, __arg3_type, __arg3) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst , __arg1_type , __arg1 , __arg2_type , __arg2 , __arg3_type , __arg3 )
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(__ret, __func, __dsttype, __src) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define errno ( * _errno ( ) )
#define _CALL_REPORTFAULT (2)
#define _wenviron ( * __MINGW_IMP_SYMBOL ( _wenviron ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _WCTYPE_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define __argc ( * __MINGW_IMP_SYMBOL ( __argc ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _TIME_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _CRT_ERRNO_DEFINED 
#define _CRT_ABS_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _SIZE_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define RAND_MAX (32767)
#define MB_CUR_MAX ___mb_cur_max_func ( )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _CRTRESTRICT 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst )
#define _THREADLOCALEINFO 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _PTR_LD(x) ( ( unsigned char * ) ( & ( x ) -> ld ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst , __arg1_type , __arg1 , __arg2_type , __arg2 )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _winmajor ( * __MINGW_IMP_SYMBOL ( _winmajor ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _TAGLC_ID_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _CRT_WSYSTEM_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _ERRCODE_DEFINED 
#define __crt_typefix(ctype) 
#define _TIME64_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define sys_nerr _sys_nerr
#define _MAX_DRIVE (3)
#define _WSTDLIB_DEFINED 
#define _CRT_ATOF_DEFINED 
#define EXIT_FAILURE (1)
#define __max(a, b) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#define _CRT_ALLOCATION_DEFINED 
#define _CRT_DOUBLE_DEC 
#define _winminor ( * __MINGW_IMP_SYMBOL ( _winminor ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(__ret, __func, __dsttype, __dst) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _countof(_Array) ( sizeof ( _Array ) / sizeof ( _Array [ 0 ] ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(__ret, __func, __dsttype, __dst, __type1, __arg1) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _winver ( * __MINGW_IMP_SYMBOL ( _winver ) )
#define _pgmptr ( * __MINGW_IMP_SYMBOL ( _pgmptr ) )
#define _MAX_PATH (260)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2, __arg3_type, __arg3, __arg4_type, __arg4) 
#define _WCHAR_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _fmode ( * __MINGW_IMP_SYMBOL ( _fmode ) )
#define __wargv ( * __MINGW_IMP_SYMBOL ( __wargv ) )
#define environ _environ
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _RSIZE_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _WRITE_ABORT_MSG (1)
#define _osver ( * __MINGW_IMP_SYMBOL ( _osver ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(__ret, __func, __type0, __arg0, __dsttype, __dst, __type1, __arg1, __type2, __arg2, __type3, __arg3) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define NULL ( ( void * ) 0 )
#define __argv ( * __MINGW_IMP_SYMBOL ( __argv ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _SSIZE_T_DEFINED 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _INC_STDLIB 
#define _MAX_DIR (256)
#define _CRT_SYSTEM_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(__ret, __func, __vfunc, __dsttype, __dst, __type1, __arg1) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _wpgmptr ( * __MINGW_IMP_SYMBOL ( _wpgmptr ) )
#define _CRT_SWAB_DEFINED 
#define _CRT_TERMINATE_DEFINED 
#define _REPORT_ERRMODE (3)
#define _MAX_FNAME (256)
#define _CVTBUFSIZE (349)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst , __arg1_type , __arg1 , __arg2_type , __arg2 )
#define _WINT_T 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _doserrno ( * __doserrno ( ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _PTRDIFF_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _OUT_TO_MSGBOX (2)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(__ret, __func, __dsttype, __dst, __type1, __arg1, __type2, __arg2, __type3, __arg3) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _MAX_EXT (256)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _UINTPTR_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _DIV_T_DEFINED 
#define _CRT_WPERROR_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _CRTNOALIAS 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _environ ( * __MINGW_IMP_SYMBOL ( _environ ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _CRT_PACKING (8)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define sys_errlist _sys_errlist
#define __mb_cur_max ( * __MINGW_IMP_SYMBOL ( __mb_cur_max ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(__ret, __func, __type1, __arg1, __type2, __arg2, __dsttype, __dst) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _ONEXIT_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(__ret, __func, __type0, __arg0, __dsttype, __dst, __type1, __arg1) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\stdlib.h 

#define _OUT_TO_DEFAULT (0)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(__ret, __func, __vfunc, __dsttype, __dst, __type1, __arg1, __type2, __arg2) 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2, __arg3_type, __arg3, __arg4_type, __arg4) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst , __arg1_type , __arg1 , __arg2_type , __arg2 , __arg3_type , __arg3 , __arg4_type , __arg4 )
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(__ret, __func, __type0, __arg0, __dsttype, __dst, __type1, __arg1, __type2, __arg2)