// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

// ----------------------------------------------------------------------------
//      /usr/include/locale.h
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

struct lconv {
	char *decimal_point;
	char *thousands_sep;
	char *grouping;
	char *int_curr_symbol;
	char *currency_symbol;
	char *mon_decimal_point;
	char *mon_thousands_sep;
	char *mon_grouping;
	char *positive_sign;
	char *negative_sign;
	char int_frac_digits;
	char frac_digits;
	char p_cs_precedes;
	char p_sep_by_space;
	char n_cs_precedes;
	char n_sep_by_space;
	char p_sign_posn;
	char n_sign_posn;
	char int_p_cs_precedes;
	char int_p_sep_by_space;
	char int_n_cs_precedes;
	char int_n_sep_by_space;
	char int_p_sign_posn;
	char int_n_sign_posn;
};
extern char *setlocale(int __category, const char *__locale);
extern struct lconv *localeconv(void);

// /usr/include/locale.h 

#define LC_COLLATE __LC_COLLATE

// /usr/include/x86_64-linux-gnu/bits/locale.h 

#define __LC_COLLATE (3)

// /usr/include/locale.h 

#define LC_TIME __LC_TIME

// /usr/include/x86_64-linux-gnu/bits/locale.h 

#define __LC_ADDRESS (9)

// /usr/include/locale.h 

#define LC_ALL __LC_ALL

// /usr/include/x86_64-linux-gnu/bits/locale.h 

#define __LC_MESSAGES (5)
#define __LC_MONETARY (4)
#define __LC_NUMERIC (1)

// /usr/include/locale.h 

#define LC_TELEPHONE __LC_TELEPHONE

// /usr/include/x86_64-linux-gnu/bits/locale.h 

#define __LC_CTYPE (0)

// /usr/include/locale.h 

#define LC_MONETARY __LC_MONETARY

// /usr/include/x86_64-linux-gnu/bits/locale.h 

#define __LC_PAPER (7)
#define __LC_NAME (8)

// /usr/include/locale.h 

#define _LOCALE_H (1)

// /usr/include/x86_64-linux-gnu/bits/locale.h 

#define __LC_IDENTIFICATION (12)
#define __LC_TIME (2)
#define __LC_ALL (6)

// /usr/include/locale.h 

#define LC_MESSAGES __LC_MESSAGES
#define LC_CTYPE __LC_CTYPE

// /usr/include/x86_64-linux-gnu/bits/locale.h 

#define __LC_MEASUREMENT (11)
#define __LC_TELEPHONE (10)

// /usr/include/locale.h 

#define LC_MEASUREMENT __LC_MEASUREMENT
#define LC_PAPER __LC_PAPER
#define LC_IDENTIFICATION __LC_IDENTIFICATION
#define LC_NUMERIC __LC_NUMERIC

// /usr/include/x86_64-linux-gnu/bits/locale.h 

#define _BITS_LOCALE_H (1)

// /usr/include/locale.h 

#define LC_NAME __LC_NAME
#define LC_ADDRESS __LC_ADDRESS
