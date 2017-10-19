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

#define PRId8 "d"
#define SCNu64 __PRI64_PREFIX "u"
#define PRIxFAST64 __PRI64_PREFIX "x"
#define PRIxPTR __PRIPTR_PREFIX "x"
#define PRIi32 "i"
#define PRIdPTR __PRIPTR_PREFIX "d"
#define PRIuLEAST16 "u"
#define PRIX8 "X"
#define PRIXFAST16 __PRIPTR_PREFIX "X"
#define SCNoFAST8 "hho"
#define PRIdLEAST8 "d"
#define SCNo32 "o"
#define SCNoMAX __PRI64_PREFIX "o"
#define SCNxFAST32 __PRIPTR_PREFIX "x"
#define SCNi8 "hhi"
#define PRIiLEAST8 "i"
#define PRIoFAST64 __PRI64_PREFIX "o"
#define PRIoMAX __PRI64_PREFIX "o"
#define PRId64 __PRI64_PREFIX "d"
#define SCNxLEAST8 "hhx"
#define PRIu64 __PRI64_PREFIX "u"
#define PRIXFAST8 "X"
#define PRIXPTR __PRIPTR_PREFIX "X"
#define PRIdLEAST16 "d"
#define PRIdFAST16 __PRIPTR_PREFIX "d"
#define SCNiFAST32 __PRIPTR_PREFIX "i"
#define PRIuFAST8 "u"
#define SCNu32 "u"
#define _INTTYPES_H (1)
#define PRIxLEAST16 "x"
#define SCNo64 __PRI64_PREFIX "o"
#define PRIxMAX __PRI64_PREFIX "x"
#define SCNd16 "hd"
#define PRIxLEAST32 "x"
#define SCNiFAST8 "hhi"
#define PRIXLEAST16 "X"
#define SCNuFAST16 __PRIPTR_PREFIX "u"
#define PRIuLEAST8 "u"
#define PRIxFAST8 "x"
#define PRIuFAST64 __PRI64_PREFIX "u"
#define SCNo8 "hho"
#define SCNuLEAST64 __PRI64_PREFIX "u"
#define __PRIPTR_PREFIX "l"
#define PRIoFAST16 __PRIPTR_PREFIX "o"
#define PRIdFAST32 __PRIPTR_PREFIX "d"
#define PRIxFAST16 __PRIPTR_PREFIX "x"
#define SCNxFAST64 __PRI64_PREFIX "x"
#define SCNd64 __PRI64_PREFIX "d"
#define PRIX32 "X"
#define SCNiFAST16 __PRIPTR_PREFIX "i"
#define PRIx32 "x"
#define PRIiPTR __PRIPTR_PREFIX "i"
#define SCNdFAST8 "hhd"
#define SCNiLEAST16 "hi"
#define PRIuFAST16 __PRIPTR_PREFIX "u"
#define PRIX64 __PRI64_PREFIX "X"
#define SCNi32 "i"
#define SCNd8 "hhd"
#define PRIuFAST32 __PRIPTR_PREFIX "u"
#define SCNi64 __PRI64_PREFIX "i"
#define SCNdLEAST32 "d"
#define SCNu16 "hu"
#define PRIuMAX __PRI64_PREFIX "u"
#define SCNdPTR __PRIPTR_PREFIX "d"
#define SCNuFAST64 __PRI64_PREFIX "u"
#define SCNdFAST64 __PRI64_PREFIX "d"
#define PRIuPTR __PRIPTR_PREFIX "u"
#define SCNxFAST16 __PRIPTR_PREFIX "x"
#define PRIoLEAST16 "o"
#define SCNx8 "hhx"
#define PRIoPTR __PRIPTR_PREFIX "o"
#define PRIdLEAST64 __PRI64_PREFIX "d"
#define PRIo32 "o"
#define SCNdLEAST64 __PRI64_PREFIX "d"
#define SCNoLEAST16 "ho"
#define PRIX16 "X"
#define PRIXLEAST8 "X"
#define PRIxLEAST8 "x"
#define SCNxPTR __PRIPTR_PREFIX "x"
#define SCNoFAST16 __PRIPTR_PREFIX "o"
#define SCNoLEAST32 "o"
#define SCNiPTR __PRIPTR_PREFIX "i"
#define SCNxMAX __PRI64_PREFIX "x"
#define SCNiLEAST64 __PRI64_PREFIX "i"
#define PRIx8 "x"
#define SCNuPTR __PRIPTR_PREFIX "u"
#define PRIxLEAST64 __PRI64_PREFIX "x"
#define PRIx16 "x"
#define SCNdMAX __PRI64_PREFIX "d"
#define PRIoLEAST8 "o"
#define PRIXFAST32 __PRIPTR_PREFIX "X"
#define PRIiFAST8 "i"
#define PRIu32 "u"
#define __PRI64_PREFIX "l"
#define PRIdFAST64 __PRI64_PREFIX "d"
#define PRIoFAST8 "o"
#define SCNuMAX __PRI64_PREFIX "u"
#define SCNu8 "hhu"
#define PRIo64 __PRI64_PREFIX "o"
#define PRIu8 "u"
#define SCNiFAST64 __PRI64_PREFIX "i"
#define PRIx64 __PRI64_PREFIX "x"
#define SCNi16 "hi"
#define SCNdFAST16 __PRIPTR_PREFIX "d"
#define SCNxLEAST16 "hx"
#define PRIXLEAST64 __PRI64_PREFIX "X"
#define SCNuFAST8 "hhu"
#define PRIuLEAST64 __PRI64_PREFIX "u"
#define PRIiLEAST64 __PRI64_PREFIX "i"
#define SCNuLEAST32 "u"
#define PRIiFAST32 __PRIPTR_PREFIX "i"
#define PRIoFAST32 __PRIPTR_PREFIX "o"
#define SCNoLEAST8 "hho"
#define SCNoLEAST64 __PRI64_PREFIX "o"
#define PRIi16 "i"
#define PRId32 "d"
#define PRId16 "d"
#define PRIiMAX __PRI64_PREFIX "i"
#define PRIiFAST16 __PRIPTR_PREFIX "i"
#define SCNoFAST32 __PRIPTR_PREFIX "o"
#define ____gwchar_t_defined (1)
#define SCNxLEAST64 __PRI64_PREFIX "x"
#define SCNx64 __PRI64_PREFIX "x"
#define PRIoLEAST64 __PRI64_PREFIX "o"
#define PRIo16 "o"
#define PRIiLEAST32 "i"
#define PRIo8 "o"
#define SCNxFAST8 "hhx"
#define SCNx32 "x"
#define PRIXFAST64 __PRI64_PREFIX "X"
#define PRIxFAST32 __PRIPTR_PREFIX "x"
#define PRIdFAST8 "d"
#define SCNdLEAST16 "hd"
#define PRIi64 __PRI64_PREFIX "i"
#define SCNuLEAST16 "hu"
#define SCNd32 "d"
#define SCNiMAX __PRI64_PREFIX "i"
#define SCNdLEAST8 "hhd"
#define PRIXMAX __PRI64_PREFIX "X"
#define SCNxLEAST32 "x"
#define SCNdFAST32 __PRIPTR_PREFIX "d"
#define PRIXLEAST32 "X"
#define PRIiFAST64 __PRI64_PREFIX "i"
#define PRIi8 "i"
#define PRIiLEAST16 "i"
#define PRIdLEAST32 "d"
#define PRIdMAX __PRI64_PREFIX "d"
#define PRIu16 "u"
#define SCNx16 "hx"
#define SCNoPTR __PRIPTR_PREFIX "o"
#define SCNo16 "ho"
#define PRIoLEAST32 "o"
#define SCNuLEAST8 "hhu"
#define PRIuLEAST32 "u"
#define SCNuFAST32 __PRIPTR_PREFIX "u"
#define SCNoFAST64 __PRI64_PREFIX "o"
#define SCNiLEAST32 "i"
#define SCNiLEAST8 "hhi"
