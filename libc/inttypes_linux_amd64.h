// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

// ----------------------------------------------------------------------------
//      /usr/include/inttypes.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
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

typedef int __gwchar_t;
typedef struct {
	long int quot;
	long int rem;
} imaxdiv_t;
extern intmax_t imaxabs(intmax_t __n);
extern imaxdiv_t imaxdiv(intmax_t __numer, intmax_t __denom);
extern intmax_t strtoimax(const char *__nptr, char **__endptr, int __base);
extern uintmax_t strtoumax(const char *__nptr, char **__endptr, int __base);
extern intmax_t wcstoimax(const __gwchar_t * __nptr, __gwchar_t ** __endptr, int __base);
extern uintmax_t wcstoumax(const __gwchar_t * __nptr, __gwchar_t ** __endptr, int __base);

// /usr/include/inttypes.h 

#define PRIuLEAST16 "u"
#define SCNu32 "u"
#define PRIXFAST8 "X"
#define SCNoFAST32 __PRIPTR_PREFIX "o"
#define SCNo64 __PRI64_PREFIX "o"
#define SCNxLEAST32 "x"
#define SCNiMAX __PRI64_PREFIX "i"
#define SCNiLEAST32 "i"
#define SCNdFAST64 __PRI64_PREFIX "d"
#define PRIiLEAST32 "i"
#define SCNdLEAST8 "hhd"
#define PRIiLEAST8 "i"
#define PRIXFAST32 __PRIPTR_PREFIX "X"
#define PRIX32 "X"
#define PRIdFAST8 "d"
#define SCNi16 "hi"
#define PRIXLEAST16 "X"
#define SCNuPTR __PRIPTR_PREFIX "u"
#define SCNdPTR __PRIPTR_PREFIX "d"
#define PRIuFAST16 __PRIPTR_PREFIX "u"
#define SCNuLEAST16 "hu"
#define PRIxMAX __PRI64_PREFIX "x"
#define SCNd16 "hd"
#define SCNdFAST32 __PRIPTR_PREFIX "d"
#define SCNuFAST16 __PRIPTR_PREFIX "u"
#define SCNoFAST16 __PRIPTR_PREFIX "o"
#define PRIX64 __PRI64_PREFIX "X"
#define SCNu16 "hu"
#define SCNiFAST32 __PRIPTR_PREFIX "i"
#define SCNoPTR __PRIPTR_PREFIX "o"
#define PRIu16 "u"
#define PRIxLEAST32 "x"
#define _INTTYPES_H (1)
#define SCNoLEAST16 "ho"
#define PRIxLEAST16 "x"
#define SCNu64 __PRI64_PREFIX "u"
#define SCNuFAST32 __PRIPTR_PREFIX "u"
#define SCNdFAST8 "hhd"
#define PRId8 "d"
#define PRIXPTR __PRIPTR_PREFIX "X"
#define PRIdMAX __PRI64_PREFIX "d"
#define SCNxLEAST64 __PRI64_PREFIX "x"
#define PRIoPTR __PRIPTR_PREFIX "o"
#define SCNi8 "hhi"
#define PRIdLEAST32 "d"
#define SCNdMAX __PRI64_PREFIX "d"
#define PRIXFAST16 __PRIPTR_PREFIX "X"
#define PRIx16 "x"
#define SCNo8 "hho"
#define PRIi32 "i"
#define PRIiFAST64 __PRI64_PREFIX "i"
#define PRIuFAST8 "u"
#define PRIdLEAST64 __PRI64_PREFIX "d"
#define PRIo16 "o"
#define PRIi16 "i"
#define PRIoLEAST32 "o"
#define SCNi32 "i"
#define PRIdLEAST16 "d"
#define SCNxFAST16 __PRIPTR_PREFIX "x"
#define PRIi64 __PRI64_PREFIX "i"
#define PRIo8 "o"
#define SCNxLEAST8 "hhx"
#define PRIXMAX __PRI64_PREFIX "X"
#define SCNiFAST64 __PRI64_PREFIX "i"
#define __PRI64_PREFIX "l"
#define SCNx64 __PRI64_PREFIX "x"
#define PRIx8 "x"
#define SCNo32 "o"
#define SCNoMAX __PRI64_PREFIX "o"
#define SCNuLEAST8 "hhu"
#define SCNdLEAST32 "d"
#define SCNuLEAST32 "u"
#define PRIo64 __PRI64_PREFIX "o"
#define SCNuMAX __PRI64_PREFIX "u"
#define SCNoFAST64 __PRI64_PREFIX "o"
#define PRIoLEAST64 __PRI64_PREFIX "o"
#define PRIu8 "u"
#define SCNxLEAST16 "hx"
#define SCNd8 "hhd"
#define PRIi8 "i"
#define SCNxPTR __PRIPTR_PREFIX "x"
#define PRIu32 "u"
#define PRIu64 __PRI64_PREFIX "u"
#define PRId32 "d"
#define SCNoLEAST64 __PRI64_PREFIX "o"
#define SCNiFAST8 "hhi"
#define PRIxFAST32 __PRIPTR_PREFIX "x"
#define PRIiPTR __PRIPTR_PREFIX "i"
#define PRIxLEAST8 "x"
#define SCNi64 __PRI64_PREFIX "i"
#define SCNx32 "x"
#define PRIXFAST64 __PRI64_PREFIX "X"
#define PRIoLEAST8 "o"
#define SCNxMAX __PRI64_PREFIX "x"
#define PRIdFAST64 __PRI64_PREFIX "d"
#define SCNd64 __PRI64_PREFIX "d"
#define PRIx64 __PRI64_PREFIX "x"
#define PRIiLEAST16 "i"
#define SCNiLEAST16 "hi"
#define SCNx8 "hhx"
#define PRIuFAST32 __PRIPTR_PREFIX "u"
#define PRIX8 "X"
#define SCNu8 "hhu"
#define SCNxFAST8 "hhx"
#define ____gwchar_t_defined (1)
#define SCNuLEAST64 __PRI64_PREFIX "u"
#define SCNdLEAST64 __PRI64_PREFIX "d"
#define SCNx16 "hx"
#define PRIxLEAST64 __PRI64_PREFIX "x"
#define SCNoLEAST32 "o"
#define SCNoFAST8 "hho"
#define PRIoLEAST16 "o"
#define SCNiPTR __PRIPTR_PREFIX "i"
#define PRIuLEAST8 "u"
#define PRIiFAST16 __PRIPTR_PREFIX "i"
#define PRId64 __PRI64_PREFIX "d"
#define PRIuPTR __PRIPTR_PREFIX "u"
#define PRIuMAX __PRI64_PREFIX "u"
#define SCNoLEAST8 "hho"
#define PRIxFAST16 __PRIPTR_PREFIX "x"
#define PRIXLEAST64 __PRI64_PREFIX "X"
#define SCNxFAST64 __PRI64_PREFIX "x"
#define PRIiFAST32 __PRIPTR_PREFIX "i"
#define PRIiFAST8 "i"
#define PRIxFAST8 "x"
#define PRIXLEAST32 "X"
#define PRIxFAST64 __PRI64_PREFIX "x"
#define SCNdFAST16 __PRIPTR_PREFIX "d"
#define PRIoFAST32 __PRIPTR_PREFIX "o"
#define PRIXLEAST8 "X"
#define PRIiMAX __PRI64_PREFIX "i"
#define SCNxFAST32 __PRIPTR_PREFIX "x"
#define PRIiLEAST64 __PRI64_PREFIX "i"
#define PRIuLEAST64 __PRI64_PREFIX "u"
#define PRIxPTR __PRIPTR_PREFIX "x"
#define PRIoFAST16 __PRIPTR_PREFIX "o"
#define PRIuLEAST32 "u"
#define PRIdLEAST8 "d"
#define PRIuFAST64 __PRI64_PREFIX "u"
#define SCNo16 "ho"
#define SCNdLEAST16 "hd"
#define SCNuFAST8 "hhu"
#define PRIoFAST8 "o"
#define PRIoMAX __PRI64_PREFIX "o"
#define PRId16 "d"
#define __PRIPTR_PREFIX "l"
#define SCNiFAST16 __PRIPTR_PREFIX "i"
#define PRIo32 "o"
#define PRIdFAST16 __PRIPTR_PREFIX "d"
#define SCNd32 "d"
#define PRIX16 "X"
#define PRIx32 "x"
#define PRIdFAST32 __PRIPTR_PREFIX "d"
#define PRIoFAST64 __PRI64_PREFIX "o"
#define SCNiLEAST8 "hhi"
#define PRIdPTR __PRIPTR_PREFIX "d"
#define SCNiLEAST64 __PRI64_PREFIX "i"
#define SCNuFAST64 __PRI64_PREFIX "u"
