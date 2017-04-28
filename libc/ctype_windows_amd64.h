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
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

extern unsigned short **__imp__pctype ;
extern unsigned short **__imp__wctype ;
extern unsigned short **__imp__pwctype ;
extern const unsigned char __newclmap [];
extern const unsigned char __newcumap [];
extern pthreadlocinfo __ptlocinfo ;
extern pthreadmbcinfo __ptmbcinfo ;
extern int __globallocalestatus ;
extern int __locale_changed ;
extern struct threadlocaleinfostruct __initiallocinfo ;
extern _locale_tstruct __initiallocalestructinfo ;
pthreadlocinfo __updatetlocinfo (void );
pthreadmbcinfo __updatetmbcinfo (void );
int _isctype (int _C ,int _Type );
int _isctype_l (int _C ,int _Type ,_locale_t _Locale );
int isalpha (int _C );
int _isalpha_l (int _C ,_locale_t _Locale );
int isupper (int _C );
int _isupper_l (int _C ,_locale_t _Locale );
int islower (int _C );
int _islower_l (int _C ,_locale_t _Locale );
int isdigit (int _C );
int _isdigit_l (int _C ,_locale_t _Locale );
int isxdigit (int _C );
int _isxdigit_l (int _C ,_locale_t _Locale );
int isspace (int _C );
int _isspace_l (int _C ,_locale_t _Locale );
int ispunct (int _C );
int _ispunct_l (int _C ,_locale_t _Locale );
int isalnum (int _C );
int _isalnum_l (int _C ,_locale_t _Locale );
int isprint (int _C );
int _isprint_l (int _C ,_locale_t _Locale );
int isgraph (int _C );
int _isgraph_l (int _C ,_locale_t _Locale );
int iscntrl (int _C );
int _iscntrl_l (int _C ,_locale_t _Locale );
int toupper (int _C );
int tolower (int _C );
int _tolower (int _C );
int _tolower_l (int _C ,_locale_t _Locale );
int _toupper (int _C );
int _toupper_l (int _C ,_locale_t _Locale );
int __isascii (int _C );
int __toascii (int _C );
int __iscsymf (int _C );
int __iscsym (int _C );
int isblank (int _C );
int iswalpha (wint_t _C );
int _iswalpha_l (wint_t _C ,_locale_t _Locale );
int iswupper (wint_t _C );
int _iswupper_l (wint_t _C ,_locale_t _Locale );
int iswlower (wint_t _C );
int _iswlower_l (wint_t _C ,_locale_t _Locale );
int iswdigit (wint_t _C );
int _iswdigit_l (wint_t _C ,_locale_t _Locale );
int iswxdigit (wint_t _C );
int _iswxdigit_l (wint_t _C ,_locale_t _Locale );
int iswspace (wint_t _C );
int _iswspace_l (wint_t _C ,_locale_t _Locale );
int iswpunct (wint_t _C );
int _iswpunct_l (wint_t _C ,_locale_t _Locale );
int iswalnum (wint_t _C );
int _iswalnum_l (wint_t _C ,_locale_t _Locale );
int iswprint (wint_t _C );
int _iswprint_l (wint_t _C ,_locale_t _Locale );
int iswgraph (wint_t _C );
int _iswgraph_l (wint_t _C ,_locale_t _Locale );
int iswcntrl (wint_t _C );
int _iswcntrl_l (wint_t _C ,_locale_t _Locale );
int iswascii (wint_t _C );
int isleadbyte (int _C );
int _isleadbyte_l (int _C ,_locale_t _Locale );
wint_t towupper (wint_t _C );
wint_t _towupper_l (wint_t _C ,_locale_t _Locale );
wint_t towlower (wint_t _C );
wint_t _towlower_l (wint_t _C ,_locale_t _Locale );
int iswctype (wint_t _C ,wctype_t _Type );
int _iswctype_l (wint_t _C ,wctype_t _Type ,_locale_t _Locale );
int __iswcsymf (wint_t _C );
int _iswcsymf_l (wint_t _C ,_locale_t _Locale );
int __iswcsym (wint_t _C );
int _iswcsym_l (wint_t _C ,_locale_t _Locale );
int is_wctype (wint_t _C ,wctype_t _Type );
int iswblank (wint_t _C );
extern int *__imp___mb_cur_max ;
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _THREADLOCALEINFO 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define iswdigit(_c) ( iswctype ( _c , _DIGIT ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _INTPTR_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _tolower(_Char) ( ( _Char ) - 'A' + 'a' )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __intptr_t_defined 
#define __crt_typefix(ctype) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(__ret, __func, __type0, __arg0, __dsttype, __dst, __type1, __arg1, __type2, __arg2) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(__ret, __func, __dsttype, __dst, __type1, __arg1, __type2, __arg2) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _chvalidchk_l(_Char, _Flag, _Locale) ( ! _Locale ? __chvalidchk ( _Char , _Flag ) : ( ( _locale_t ) _Locale ) -> locinfo -> pctype [ _Char ] & ( _Flag ) )
#define _WCTYPE_INLINE_DEFINED 
#define iswspace(_c) ( iswctype ( _c , _SPACE ) )
#define _isgraph_l(_Char, _Locale) _ischartype_l ( _Char , _PUNCT | _ALPHA | _DIGIT , _Locale )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst , __arg1_type , __arg1 , __arg2_type , __arg2 )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _iswgraph_l(_c, _p) ( _iswctype_l ( _c , _PUNCT | _ALPHA | _DIGIT , _p ) )
#define _isprint_l(_Char, _Locale) _ischartype_l ( _Char , _BLANK | _PUNCT | _ALPHA | _DIGIT , _Locale )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst) 
#define _WCTYPE_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define iscsymf __iscsymf
#define WEOF ( wint_t ) ( 0xFFFF )
#define _isalpha_l(_Char, _Locale) _ischartype_l ( _Char , _ALPHA , _Locale )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _RSIZE_T_DEFINED 
#define _INC_CRTDEFS 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define iswupper(_c) ( iswctype ( _c , _UPPER ) )
#define _iscsym_l(_c, _p) ( _isalnum_l ( _c , _p ) || ( ( _c ) == '_' ) )
#define _iswcsym_l(_c, _p) ( _iswalnum_l ( _c , _p ) || ( ( _c ) == '_' ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _CRTRESTRICT 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _iswalnum_l(_c, _p) ( _iswctype_l ( _c , _ALPHA | _DIGIT , _p ) )
#define iswalnum(_c) ( iswctype ( _c , _ALPHA | _DIGIT ) )
#define _iswpunct_l(_c, _p) ( _iswctype_l ( _c , _PUNCT , _p ) )
#define _iswprint_l(_c, _p) ( _iswctype_l ( _c , _BLANK | _PUNCT | _ALPHA | _DIGIT , _p ) )
#define _isxdigit_l(_Char, _Locale) _ischartype_l ( _Char , _HEX , _Locale )
#define iswcntrl(_c) ( iswctype ( _c , _CONTROL ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(__ret, __func, __type0, __arg0, __dsttype, __dst, __type1, __arg1) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define __pwctype_func() ( * __MINGW_IMP_SYMBOL ( _pwctype ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _CRT_PACKING (8)
#define _PTRDIFF_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define __pctype_func() ( * __MINGW_IMP_SYMBOL ( _pctype ) )
#define _islower_l(_Char, _Locale) _ischartype_l ( _Char , _LOWER , _Locale )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _PTRDIFF_T_ 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _iswdigit_l(_c, _p) ( _iswctype_l ( _c , _DIGIT , _p ) )
#define __isascii(_Char) ( ( unsigned ) ( _Char ) < 0x80 )
#define _pctype ( * __MINGW_IMP_SYMBOL ( _pctype ) )
#define toascii __toascii
#define _iscsymf_l(_c, _p) ( _isalpha_l ( _c , _p ) || ( ( _c ) == '_' ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(__ret, __func, __dsttype, __src) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _wctype ( * __MINGW_IMP_SYMBOL ( _wctype ) )
#define _iswupper_l(_c, _p) ( _iswctype_l ( _c , _UPPER , _p ) )
#define _HEX (128)
#define __PCTYPE_FUNC __pctype_func ( )
#define __iscsymf(_c) ( isalpha ( _c ) || ( ( _c ) == '_' ) )
#define iswgraph(_c) ( iswctype ( _c , _PUNCT | _ALPHA | _DIGIT ) )
#define __iswcsymf(_c) ( iswalpha ( _c ) || ( ( _c ) == '_' ) )
#define MB_CUR_MAX ___mb_cur_max_func ( )
#define _CTYPE_DEFINED 
#define iswalpha(_c) ( iswctype ( _c , _ALPHA ) )
#define _CRT_CTYPEDATA_DEFINED 
#define _ispunct_l(_Char, _Locale) _ischartype_l ( _Char , _PUNCT , _Locale )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _CRT_SECURE_CPP_NOTHROW throw ( )
#define _CRTNOALIAS 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define iswpunct(_c) ( iswctype ( _c , _PUNCT ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2, __arg3_type, __arg3) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(__ret, __func, __vfunc, __dsttype, __dst, __type1, __arg1) 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(__ret, __func, __dsttype, __dst, __type1, __arg1, __type2, __arg2, __type3, __arg3) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define ___mb_cur_max_func() ( __mb_cur_max )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _SSIZE_T_DEFINED 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _iswxdigit_l(_c, _p) ( _iswctype_l ( _c , _HEX , _p ) )
#define _pwctype ( * __MINGW_IMP_SYMBOL ( _pwctype ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _ERRCODE_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _INC_CTYPE 
#define __iswcsym(_c) ( iswalnum ( _c ) || ( ( _c ) == '_' ) )
#define _isupper_l(_Char, _Locale) _ischartype_l ( _Char , _UPPER , _Locale )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _LOWER (2)
#define _SPACE (8)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst , __arg1_type , __arg1 , __arg2_type , __arg2 )
#define _TIME_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _PUNCT (16)
#define _isdigit_l(_Char, _Locale) _ischartype_l ( _Char , _DIGIT , _Locale )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _UINTPTR_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _iscntrl_l(_Char, _Locale) _ischartype_l ( _Char , _CONTROL , _Locale )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(__ret, __func, __dsttype, __dst, __type1, __arg1) 
#define _TIME64_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define iswascii(_c) ( ( unsigned ) ( _c ) < 0x80 )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _TIME32_T_DEFINED 
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(__ret, __func, __vfunc, __dsttype, __dst, __type1, __arg1, __type2, __arg2) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _CONTROL (32)
#define __chvalidchk(a, b) ( __PCTYPE_FUNC [ ( a ) ] & ( b ) )
#define _iswalpha_l(_c, _p) ( _iswctype_l ( _c , _ALPHA , _p ) )
#define _ALPHA (259)
#define _DIGIT (4)
#define __mb_cur_max ( * __MINGW_IMP_SYMBOL ( __mb_cur_max ) )
#define _CRT_WCTYPEDATA_DEFINED 
#define iswlower(_c) ( iswctype ( _c , _LOWER ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(__ret, __func, __dsttype, __dst) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _iswlower_l(_c, _p) ( _iswctype_l ( _c , _LOWER , _p ) )
#define _LEADBYTE (32768)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(__ret, __func, __type1, __arg1, __type2, __arg2, __dsttype, __dst) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define isascii __isascii
#define _iswcntrl_l(_c, _p) ( _iswctype_l ( _c , _CONTROL , _p ) )
#define _BLANK (64)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __uintptr_t_defined 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define iswxdigit(_c) ( iswctype ( _c , _HEX ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(__ret, __func, __type0, __arg0, __dsttype, __dst, __type1, __arg1, __type2, __arg2, __type3, __arg3) 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2, __arg3_type, __arg3) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst , __arg1_type , __arg1 , __arg2_type , __arg2 , __arg3_type , __arg3 )
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(__ret, __func, __dsttype, __dst, __type1, __arg1, __type2, __arg2, __type3, __arg3, __type4, __arg4) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define __iscsym(_c) ( isalnum ( _c ) || ( ( _c ) == '_' ) )
#define _toupper(_Char) ( ( _Char ) - 'a' + 'A' )
#define _UPPER (1)
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4(__ret_type, __ret_policy, __decl_spec, __name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2, __arg3_type, __arg3, __arg4_type, __arg4) __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX ( __ret_type , __ret_policy , __decl_spec , __func_name , __func_name ## _s , __dst_attr , __dst_type , __dst , __arg1_type , __arg1 , __arg2_type , __arg2 , __arg3_type , __arg3 , __arg4_type , __arg4 )
#define _SIZE_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define _iswspace_l(_c, _p) ( _iswctype_l ( _c , _SPACE , _p ) )
#define _WCTYPE_DEFINED 
#define _isspace_l(_Char, _Locale) _ischartype_l ( _Char , _SPACE , _Locale )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _WINT_T 
#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(__ret_type, __ret_policy, __decl_spec, __name, __sec_name, __dst_attr, __dst_type, __dst, __arg1_type, __arg1, __arg2_type, __arg2, __arg3_type, __arg3, __arg4_type, __arg4) 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define __toascii(_Char) ( ( _Char ) & 0x7f )
#define _iswcsymf_l(_c, _p) ( _iswalpha_l ( _c , _p ) || ( ( _c ) == '_' ) )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _WCHAR_T_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define iswprint(_c) ( iswctype ( _c , _BLANK | _PUNCT | _ALPHA | _DIGIT ) )
#define _isalnum_l(_Char, _Locale) _ischartype_l ( _Char , _ALPHA | _DIGIT , _Locale )
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\crtdefs.h 

#define _TAGLC_ID_DEFINED 
// BEGIN OF FILE m:\mingw\x86_64-w64-mingw32\include\ctype.h 

#define iscsym __iscsym
#define _ischartype_l(_Char, _Flag, _Locale) ( ( ( _Locale ) != NULL && ( ( ( _locale_t ) ( _Locale ) ) -> locinfo -> mb_cur_max ) > 1 ) ? _isctype_l ( _Char , ( _Flag ) , _Locale ) : _chvalidchk_l ( _Char , _Flag , _Locale ) )