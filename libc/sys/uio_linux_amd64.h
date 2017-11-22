// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

// ----------------------------------------------------------------------------
//      /usr/include/sys/types.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1991-2015 Free Software Foundation, Inc.
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

// ----------------------------------------------------------------------------
//      /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1989-2013 Free Software Foundation, Inc.

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
//      /usr/include/bits/uio.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1996-2015 Free Software Foundation, Inc.
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

// ----------------------------------------------------------------------------
//      /usr/include/sys/uio.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1991-2015 Free Software Foundation, Inc.
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
// /usr/include/sys/types.h

typedef __loff_t loff_t;
typedef __ino64_t ino_t;
typedef __ino64_t ino64_t;
typedef __dev_t dev_t;
typedef __gid_t gid_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __uid_t uid_t;
typedef __off64_t off_t;
typedef __off64_t off64_t;
typedef __pid_t pid_t;
typedef __id_t id_t;
typedef __ssize_t ssize_t;
typedef __key_t key_t;
typedef __useconds_t useconds_t;
typedef __suseconds_t suseconds_t;
// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h

typedef long unsigned int size_t;
// /usr/include/sys/types.h

typedef char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int int64_t;
typedef unsigned char u_int8_t;
typedef unsigned short int u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long int u_int64_t;
typedef int register_t;
typedef __blksize_t blksize_t;
typedef __blkcnt64_t blkcnt_t;
typedef __fsblkcnt64_t fsblkcnt_t;
typedef __fsfilcnt64_t fsfilcnt_t;
typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;
// /usr/include/bits/uio.h

struct iovec {
	void *iov_base;
	size_t iov_len;
};
// /usr/include/sys/uio.h

extern ssize_t readv(int __fd, const struct iovec *__iovec, int __count);
extern ssize_t writev(int __fd, const struct iovec *__iovec, int __count);

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define _GCC_SIZE_T

// /usr/include/sys/types.h 

#define __gid_t_defined

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define __SIZE_T

// /usr/include/bits/types.h 

#define __SLONG32_TYPE int
#define __U32_TYPE unsigned int

// /usr/include/sys/types.h 

#define __fsblkcnt_t_defined
#define __uid_t_defined
#define __dev_t_defined

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define _T_SIZE_
#define _SIZE_T_DECLARED

// /usr/include/sys/types.h 

#define __need_clockid_t

// /usr/include/bits/types.h 

#define _BITS_TYPES_H (1)

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define __size_t

// /usr/include/bits/types.h 

#define __U64_TYPE unsigned long int

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define _BSD_SIZE_T_DEFINED_

// /usr/include/bits/uio.h 

#define UIO_MAXIOV (1024)

// /usr/include/sys/types.h 

#define __key_t_defined
#define __off_t_defined
#define __pid_t_defined
#define __ino64_t_defined
#define __mode_t_defined

// /usr/include/sys/uio.h 

#define _SYS_UIO_H (1)

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define __size_t__

// /usr/include/bits/types.h 

#define __SWORD_TYPE long int

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define _T_SIZE

// /usr/include/sys/types.h 

#define __off64_t_defined

// /usr/include/bits/types.h 

#define __UWORD_TYPE unsigned long int

// /usr/include/sys/types.h 

#define __blksize_t_defined
#define __useconds_t_defined

// /usr/include/bits/types.h 

#define __ULONGWORD_TYPE unsigned long int

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define ___int_size_t_h

// /usr/include/sys/types.h 

#define __BIT_TYPES_DEFINED__ (1)

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define _SIZE_T_DEFINED_

// /usr/include/sys/types.h 

#define __blkcnt_t_defined
#define __id_t_defined
#define __int8_t_defined

// /usr/include/bits/types.h 

#define __S16_TYPE short int

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define _SYS_SIZE_T_H

// /usr/include/bits/uio.h 

#define _BITS_UIO_H (1)

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define _BSD_SIZE_T_
#define _SIZE_T_

// /usr/include/bits/types.h 

#define __SLONGWORD_TYPE long int

// /usr/include/sys/types.h 

#define __fsfilcnt_t_defined

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define _SIZET_

// /usr/include/sys/types.h 

#define __ssize_t_defined

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define __SIZE_T__

// /usr/include/bits/types.h 

#define __U16_TYPE unsigned short int

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define _SIZE_T

// /usr/include/bits/types.h 

#define __UQUAD_TYPE unsigned long int

// /usr/lib64/gcc/x86_64-suse-linux/4.8/include/stddef.h 

#define _SIZE_T_DEFINED

// /usr/include/bits/types.h 

#define __ULONG32_TYPE unsigned int

// /usr/include/sys/types.h 

#define __suseconds_t_defined
#define __nlink_t_defined

// /usr/include/bits/types.h 

#define __SQUAD_TYPE long int
#define __S64_TYPE long int

// /usr/include/sys/types.h 

#define _SYS_TYPES_H (1)
#define __ino_t_defined

// /usr/include/bits/types.h 

#define __S32_TYPE int
