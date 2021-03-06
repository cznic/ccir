// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

// ----------------------------------------------------------------------------
//      /usr/include/bits/statfs.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1997-2015 Free Software Foundation, Inc.
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
// /usr/include/bits/statfs.h

struct statfs {
	__fsword_t f_type;
	__fsword_t f_bsize;
	__fsblkcnt64_t f_blocks;
	__fsblkcnt64_t f_bfree;
	__fsblkcnt64_t f_bavail;
	__fsfilcnt64_t f_files;
	__fsfilcnt64_t f_ffree;
	__fsid_t f_fsid;
	__fsword_t f_namelen;
	__fsword_t f_frsize;
	__fsword_t f_flags;
	__fsword_t f_spare[4];
};
struct statfs64 {
	__fsword_t f_type;
	__fsword_t f_bsize;
	__fsblkcnt64_t f_blocks;
	__fsblkcnt64_t f_bfree;
	__fsblkcnt64_t f_bavail;
	__fsfilcnt64_t f_files;
	__fsfilcnt64_t f_ffree;
	__fsid_t f_fsid;
	__fsword_t f_namelen;
	__fsword_t f_frsize;
	__fsword_t f_flags;
	__fsword_t f_spare[4];
};
// /usr/include/sys/statfs.h

extern int statfs64(const char *__file, struct statfs64 *__buf);
extern int fstatfs64(int __fildes, struct statfs64 *__buf);
#define _BITS_TYPES_H (1)
#define _STATFS_F_FLAGS
#define _STATFS_F_FRSIZE
#define _STATFS_F_NAMELEN
#define _SYS_STATFS_H (1)
#define __S16_TYPE short int
#define __S32_TYPE int
#define __S64_TYPE long int
#define __SLONG32_TYPE int
#define __SLONGWORD_TYPE long int
#define __SQUAD_TYPE long int
#define __SWORD_TYPE long int
#define __U16_TYPE unsigned short int
#define __U32_TYPE unsigned int
#define __U64_TYPE unsigned long int
#define __ULONG32_TYPE unsigned int
#define __ULONGWORD_TYPE unsigned long int
#define __UQUAD_TYPE unsigned long int
#define __UWORD_TYPE unsigned long int
#define fstatfs fstatfs64
#define statfs statfs64
