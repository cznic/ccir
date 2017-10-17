// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

// ----------------------------------------------------------------------------
//      /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1989-2016 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

// ----------------------------------------------------------------------------
//      /usr/include/time.h
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

typedef long unsigned int size_t;
// /usr/include/x86_64-linux-gnu/bits/types.h

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
// /usr/include/time.h

typedef __clock_t clock_t;
typedef __time_t time_t;
typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
struct timespec {
	__time_t tv_sec;
	__syscall_slong_t tv_nsec;
};
struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
	long int __tm_gmtoff;
	const char *__tm_zone;
};
struct itimerspec {
	struct timespec it_interval;
	struct timespec it_value;
};
struct sigevent;
extern clock_t clock(void);
extern time_t time(time_t * __timer);
extern double difftime(time_t __time1, time_t __time0);
extern time_t mktime(struct tm *__tp);
extern size_t strftime(char *__s, size_t __maxsize, const char *__format, const struct tm *__tp);
extern char *strptime(const char *__s, const char *__fmt, struct tm *__tp);
extern struct tm *gmtime(const time_t * __timer);
extern struct tm *localtime(const time_t * __timer);
extern struct tm *gmtime_r(const time_t * __timer, struct tm *__tp);
extern struct tm *localtime_r(const time_t * __timer, struct tm *__tp);
extern char *asctime(const struct tm *__tp);
extern char *ctime(const time_t * __timer);
extern char *asctime_r(const struct tm *__tp, char *__buf);
extern char *ctime_r(const time_t * __timer, char *__buf);
extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;
extern char *tzname[2];
extern void tzset(void);
extern int daylight;
extern long int timezone;
extern int nanosleep(const struct timespec *__requested_time, struct timespec *__remaining);
extern int clock_getres(clockid_t __clock_id, struct timespec *__res);
extern int clock_gettime(clockid_t __clock_id, struct timespec *__tp);
extern int clock_settime(clockid_t __clock_id, const struct timespec *__tp);
extern int timer_create(clockid_t __clock_id, struct sigevent *__evp, timer_t * __timerid);
extern int timer_delete(timer_t __timerid);
extern int timer_settime(timer_t __timerid, int __flags, const struct itimerspec *__value, struct itimerspec *__ovalue);
extern int timer_gettime(timer_t __timerid, struct itimerspec *__value);
extern int timer_getoverrun(timer_t __timerid);
extern int getdate_err;
extern struct tm *getdate(const char *__string);

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __SIZE_T
#define _GCC_SIZE_T
#define _SIZE_T_

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __UWORD_TYPE unsigned long int
#define __U32_TYPE unsigned int
#define __UQUAD_TYPE unsigned long int

// /usr/include/time.h 

#define __time_t_defined (1)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _BSD_SIZE_T_
#define _T_SIZE

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __S32_TYPE int

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZET_

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SLONG32_TYPE int
#define __S16_TYPE short int

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __size_t__

// /usr/include/time.h 

#define _TIME_H (1)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_DEFINED_

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __S64_TYPE long int
#define __SLONGWORD_TYPE long int

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define ___int_size_t_h
#define __size_t

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __ULONG32_TYPE unsigned int
#define __SWORD_TYPE long int
#define _BITS_TYPES_H (1)
#define __ULONGWORD_TYPE unsigned long int
#define __U16_TYPE unsigned short int

// /usr/include/time.h 

#define __timespec_defined (1)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_DEFINED

// /usr/include/time.h 

#define __isleap(year) ( ( year ) % 4 == 0 && ( ( year ) % 100 != 0 || ( year ) % 400 == 0 ) )

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define NULL ( ( void * ) 0 )
#define _SIZE_T_DECLARED

// /usr/include/time.h 

#define __clockid_t_defined (1)
#define __clock_t_defined (1)
#define __timer_t_defined (1)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __SIZE_T__

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __U64_TYPE unsigned long int

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T
#define _SYS_SIZE_T_H
#define _T_SIZE_
#define _BSD_SIZE_T_DEFINED_

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SQUAD_TYPE long int
