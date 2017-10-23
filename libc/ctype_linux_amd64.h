// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

// ----------------------------------------------------------------------------
//      /usr/include/ctype.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct {
	int __val[2];
} __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef int __daddr_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void *__timer_t;
typedef long int __blksize_t;
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;
typedef long int __fsword_t;
typedef long int __ssize_t;
typedef long int __syscall_slong_t;
typedef unsigned long int __syscall_ulong_t;
typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;
typedef long int __intptr_t;
typedef unsigned int __socklen_t;
// /usr/include/ctype.h

enum { _ISupper = 256, _ISlower = 512, _ISalpha = 1024, _ISdigit = 2048, _ISxdigit = 4096, _ISspace = 8192, _ISprint = 16384, _ISgraph = 32768, _ISblank = 1, _IScntrl = 2, _ISpunct = 4, _ISalnum = 8 };
extern const unsigned short int **__ctype_b_loc(void);
extern const __int32_t **__ctype_tolower_loc(void);
extern const __int32_t **__ctype_toupper_loc(void);
extern int isalnum(int);
extern int isalpha(int);
extern int iscntrl(int);
extern int isdigit(int);
extern int islower(int);
extern int isgraph(int);
extern int isprint(int);
extern int ispunct(int);
extern int isspace(int);
extern int isupper(int);
extern int isxdigit(int);
extern int tolower(int __c);
extern int toupper(int __c);
extern int isblank(int);
extern int isascii(int __c);
extern int toascii(int __c);
extern int _toupper(int);
extern int _tolower(int);

// /usr/include/ctype.h 

#define __tobody(c, f, a, args) ( __extension__ ( { int __res ; if ( sizeof ( c ) > 1 ) { if ( __builtin_constant_p ( c ) ) { int __c = ( c ) ; __res = __c < - 128 || __c > 255 ? __c : ( a ) [ __c ] ; } else __res = f args ; } else __res = ( a ) [ ( int ) ( c ) ] ; __res ; } ) )
#define _toupper(c) ( ( int ) ( * __ctype_toupper_loc ( ) ) [ ( int ) ( c ) ] )
#define islower(c) __isctype ( ( c ) , _ISlower )

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __U64_TYPE unsigned long int
#define __UWORD_TYPE unsigned long int
#define __U16_TYPE unsigned short int

// /usr/include/ctype.h 

#define isblank(c) __isctype ( ( c ) , _ISblank )
#define _ISbit(bit) ( ( bit ) < 8 ? ( ( 1 << ( bit ) ) << 8 ) : ( ( 1 << ( bit ) ) >> 8 ) )
#define __isascii(c) ( ( ( c ) & ~ 0x7f ) == 0 )
#define isalpha(c) __isctype ( ( c ) , _ISalpha )

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define _BITS_TYPES_H (1)
#define __UQUAD_TYPE unsigned long int
#define __S64_TYPE long int
#define __U32_TYPE unsigned int

// /usr/include/ctype.h 

#define __isctype(c, type) ( ( * __ctype_b_loc ( ) ) [ ( int ) ( c ) ] & ( unsigned short int ) type )
#define _tolower(c) ( ( int ) ( * __ctype_tolower_loc ( ) ) [ ( int ) ( c ) ] )
#define iscntrl(c) __isctype ( ( c ) , _IScntrl )
#define isdigit(c) __isctype ( ( c ) , _ISdigit )

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SLONG32_TYPE int
#define __SWORD_TYPE long int

// /usr/include/ctype.h 

#define isxdigit(c) __isctype ( ( c ) , _ISxdigit )
#define __toascii(c) ( ( c ) & 0x7f )
#define _CTYPE_H (1)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __S32_TYPE int
#define __SLONGWORD_TYPE long int

// /usr/include/ctype.h 

#define isalnum(c) __isctype ( ( c ) , _ISalnum )
#define isgraph(c) __isctype ( ( c ) , _ISgraph )

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __ULONGWORD_TYPE unsigned long int
#define __ULONG32_TYPE unsigned int
#define __S16_TYPE short int

// /usr/include/ctype.h 

#define toascii(c) __toascii ( c )
#define ispunct(c) __isctype ( ( c ) , _ISpunct )
#define __exctype(name) extern int name ( int ) __THROW
#define isprint(c) __isctype ( ( c ) , _ISprint )
#define isupper(c) __isctype ( ( c ) , _ISupper )
#define isspace(c) __isctype ( ( c ) , _ISspace )

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SQUAD_TYPE long int

// /usr/include/ctype.h 

#define isascii(c) __isascii ( c )
