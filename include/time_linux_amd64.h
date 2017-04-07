// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

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

#define _TIME_H (1)
#define __clock_t_defined (1)
typedef __clock_t clock_t;
#define __time_t_defined (1)
typedef __time_t time_t;
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
	char *__tm_zone;
};
extern clock_t clock(void);
extern time_t time(time_t * __timer);
extern double difftime(time_t __time1, time_t __time0);
extern time_t mktime(struct tm *__tp);
extern size_t strftime(char *__s, size_t __maxsize, char *__format, struct tm *__tp);
extern struct tm *gmtime(time_t * __timer);
extern struct tm *localtime(time_t * __timer);
extern char *asctime(struct tm *__tp);
extern char *ctime(time_t * __timer);
extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;
#define __isleap(year) ( ( year ) % 4 == 0 && ( ( year ) % 100 != 0 || ( year ) % 400 == 0 ) )
#define _BITS_TIME_H (1)
#define CLOCKS_PER_SEC ( ( clock_t ) 1000000 )
