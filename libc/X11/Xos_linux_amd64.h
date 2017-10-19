// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

// ----------------------------------------------------------------------------
//      /usr/include/x86_64-linux-gnu/sys/types.h
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
//      /usr/include/string.h
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

// ----------------------------------------------------------------------------
//      /usr/include/x86_64-linux-gnu/bits/stat.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1999-2016 Free Software Foundation, Inc.
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
//      /usr/include/fcntl.h
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

// ----------------------------------------------------------------------------
//      /usr/include/unistd.h
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
// /usr/include/x86_64-linux-gnu/sys/types.h

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
// /usr/include/time.h

typedef __clock_t clock_t;
typedef __time_t time_t;
typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
// /usr/include/x86_64-linux-gnu/sys/types.h

typedef __useconds_t useconds_t;
typedef __suseconds_t suseconds_t;
// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h

typedef long unsigned int size_t;
// /usr/include/x86_64-linux-gnu/sys/types.h

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
// /usr/include/string.h

extern void *memcpy(void *__dest, const void *__src, size_t __n);
extern void *memmove(void *__dest, const void *__src, size_t __n);
extern void *memccpy(void *__dest, const void *__src, int __c, size_t __n);
extern void *memset(void *__s, int __c, size_t __n);
extern int memcmp(const void *__s1, const void *__s2, size_t __n);
extern void *memchr(const void *__s, int __c, size_t __n);
extern char *strcpy(char *__dest, const char *__src);
extern char *strncpy(char *__dest, const char *__src, size_t __n);
extern char *strcat(char *__dest, const char *__src);
extern char *strncat(char *__dest, const char *__src, size_t __n);
extern int strcmp(const char *__s1, const char *__s2);
extern int strncmp(const char *__s1, const char *__s2, size_t __n);
extern int strcoll(const char *__s1, const char *__s2);
extern size_t strxfrm(char *__dest, const char *__src, size_t __n);
extern char *strdup(const char *__s);
extern char *strchr(const char *__s, int __c);
extern char *strrchr(const char *__s, int __c);
extern size_t strcspn(const char *__s, const char *__reject);
extern size_t strspn(const char *__s, const char *__accept);
extern char *strpbrk(const char *__s, const char *__accept);
extern char *strstr(const char *__haystack, const char *__needle);
extern char *strtok(char *__s, const char *__delim);
extern char *__strtok_r(char *__s, const char *__delim, char **__save_ptr);
extern char *strtok_r(char *__s, const char *__delim, char **__save_ptr);
extern size_t strlen(const char *__s);
extern char *strerror(int __errnum);
extern void __bzero(void *__s, size_t __n);
// /usr/include/x86_64-linux-gnu/bits/stat.h

struct stat {
	__dev_t st_dev;
	__ino_t st_ino;
	__nlink_t st_nlink;
	__mode_t st_mode;
	__uid_t st_uid;
	__gid_t st_gid;
	int __pad0;
	__dev_t st_rdev;
	__off_t st_size;
	__blksize_t st_blksize;
	__blkcnt_t st_blocks;
	__time_t st_atime;
	__syscall_ulong_t st_atimensec;
	__time_t st_mtime;
	__syscall_ulong_t st_mtimensec;
	__time_t st_ctime;
	__syscall_ulong_t st_ctimensec;
	__syscall_slong_t __glibc_reserved[3];
};
struct stat64 {
	__dev_t st_dev;
	__ino64_t st_ino;
	__nlink_t st_nlink;
	__mode_t st_mode;
	__uid_t st_uid;
	__gid_t st_gid;
	int __pad0;
	__dev_t st_rdev;
	__off_t st_size;
	__blksize_t st_blksize;
	__blkcnt64_t st_blocks;
	__time_t st_atime;
	__syscall_ulong_t st_atimensec;
	__time_t st_mtime;
	__syscall_ulong_t st_mtimensec;
	__time_t st_ctime;
	__syscall_ulong_t st_ctimensec;
	__syscall_slong_t __glibc_reserved[3];
};
// /usr/include/fcntl.h

extern int fcntl(int __fd, int __cmd, ...);
extern int open64(const char *__file, int __oflag, ...);
extern int creat64(const char *__file, mode_t __mode);
// /usr/include/unistd.h

typedef __intptr_t intptr_t;
typedef __socklen_t socklen_t;
extern int access(const char *__name, int __type);
extern __off64_t lseek64(int __fd, __off64_t __offset, int __whence);
extern int close(int __fd);
extern ssize_t read(int __fd, void *__buf, size_t __nbytes);
extern ssize_t write(int __fd, const void *__buf, size_t __n);
extern ssize_t pread64(int __fd, void *__buf, size_t __nbytes, __off64_t __offset);
extern ssize_t pwrite64(int __fd, const void *__buf, size_t __n, __off64_t __offset);
extern int pipe(int __pipedes[2]);
extern unsigned int alarm(unsigned int __seconds);
extern unsigned int sleep(unsigned int __seconds);
extern __useconds_t ualarm(__useconds_t __value, __useconds_t __interval);
extern int usleep(__useconds_t __useconds);
extern int pause(void);
extern int chown(const char *__file, __uid_t __owner, __gid_t __group);
extern int fchown(int __fd, __uid_t __owner, __gid_t __group);
extern int lchown(const char *__file, __uid_t __owner, __gid_t __group);
extern int chdir(const char *__path);
extern int fchdir(int __fd);
extern char *getcwd(char *__buf, size_t __size);
extern char *getwd(char *__buf);
extern int dup(int __fd);
extern int dup2(int __fd, int __fd2);
extern char **__environ;
extern int execve(const char *__path, char *const __argv[], char *const __envp[]);
extern int execv(const char *__path, char *const __argv[]);
extern int execle(const char *__path, const char *__arg, ...);
extern int execl(const char *__path, const char *__arg, ...);
extern int execvp(const char *__file, char *const __argv[]);
extern int execlp(const char *__file, const char *__arg, ...);
extern int nice(int __inc);
extern void _exit(int __status);
extern long int pathconf(const char *__path, int __name);
extern long int fpathconf(int __fd, int __name);
extern long int sysconf(int __name);
extern size_t confstr(int __name, char *__buf, size_t __len);
extern __pid_t getpid(void);
extern __pid_t getppid(void);
extern __pid_t getpgrp(void);
extern __pid_t __getpgid(__pid_t __pid);
extern __pid_t getpgid(__pid_t __pid);
extern int setpgid(__pid_t __pid, __pid_t __pgid);
extern int setpgrp(void);
extern __pid_t setsid(void);
extern __pid_t getsid(__pid_t __pid);
extern __uid_t getuid(void);
extern __uid_t geteuid(void);
extern __gid_t getgid(void);
extern __gid_t getegid(void);
extern int getgroups(int __size, __gid_t __list[]);
extern int setuid(__uid_t __uid);
extern int setreuid(__uid_t __ruid, __uid_t __euid);
extern int setgid(__gid_t __gid);
extern int setregid(__gid_t __rgid, __gid_t __egid);
extern __pid_t fork(void);
extern __pid_t vfork(void);
extern char *ttyname(int __fd);
extern int ttyname_r(int __fd, char *__buf, size_t __buflen);
extern int isatty(int __fd);
extern int link(const char *__from, const char *__to);
extern int symlink(const char *__from, const char *__to);
extern ssize_t readlink(const char *__path, char *__buf, size_t __len);
extern int unlink(const char *__name);
extern int rmdir(const char *__path);
extern __pid_t tcgetpgrp(int __fd);
extern int tcsetpgrp(int __fd, __pid_t __pgrp_id);
extern char *getlogin(void);
extern int getlogin_r(char *__name, size_t __name_len);
extern int gethostname(char *__name, size_t __len);
extern int chroot(const char *__path);
extern char *getpass(const char *__prompt);
extern int fsync(int __fd);
extern long int gethostid(void);
extern void sync(void);
extern int getpagesize(void);
extern int getdtablesize(void);
extern int truncate64(const char *__file, __off64_t __length);
extern int ftruncate64(int __fd, __off64_t __length);
extern int brk(void *__addr);
extern void *sbrk(intptr_t __delta);
extern int lockf64(int __fd, int __cmd, __off64_t __len);
extern int fdatasync(int __fildes);
extern char *crypt(const char *__key, const char *__salt);
extern void encrypt(char *__glibc_block, int __edflag);
extern void swab(const void *__from, void *__to, ssize_t __n);
extern char *ctermid(char *__s);
extern char *cuserid(char *__s);
extern int pthread_atfork(void (*__prepare) (void), void (*__parent) (void), void (*__child) (void));
// /usr/include/time.h

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

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __ssize_t_defined

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __S64_TYPE long int

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __mode_t_defined

// /usr/include/unistd.h 

#define _XOPEN_XPG2 (1)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define __O_DIRECTORY (65536)
#define __O_NOFOLLOW (131072)

// /usr/include/unistd.h 

#define F_ULOCK (0)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define __O_DSYNC (4096)
#define __F_GETOWN (9)

// /usr/include/unistd.h 

#define _POSIX_VERSION (199506l)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define __F_GETOWN_EX (16)

// /usr/include/unistd.h 

#define _POSIX2_C_DEV __POSIX2_THIS_VERSION
#define STDERR_FILENO (2)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define __F_GETSIG (11)

// /usr/include/unistd.h 

#define ftruncate ftruncate64

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define O_APPEND (1024)

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define __S_TYPEISSEM(buf) ( ( buf ) -> st_mode - ( buf ) -> st_mode )
#define __S_ISGID (1024)

// /usr/include/unistd.h 

#define _XOPEN_ENH_I18N (1)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __UQUAD_TYPE unsigned long int

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __useconds_t_defined

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_DEFINED

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __S16_TYPE short int
#define _BITS_TYPES_H (1)

// /usr/include/unistd.h 

#define _POSIX2_LOCALEDEF __POSIX2_THIS_VERSION

// /usr/include/fcntl.h 

#define S_IWUSR __S_IWRITE
#define S_IFLNK __S_IFLNK

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _BSD_SIZE_T_DEFINED_

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __off64_t_defined

// /usr/include/string.h 

#define _STRING_H (1)

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define _STAT_VER_KERNEL (0)

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __blksize_t_defined

// /usr/include/unistd.h 

#define _POSIX2_SW_DEV __POSIX2_THIS_VERSION

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define __O_CLOEXEC (524288)

// /usr/include/time.h 

#define __time_t_defined (1)

// /usr/include/fcntl.h 

#define S_IRWXO (7)

// /usr/include/unistd.h 

#define pwrite pwrite64

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __id_t_defined

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __size_t__

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define __S_ISVTX (512)

// /usr/include/unistd.h 

#define _XOPEN_XCU_VERSION (4)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_GETLK F_GETLK64

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T

// /usr/include/unistd.h 

#define _XOPEN_XPG3 (1)

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define _STATBUF_ST_RDEV

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_SETFD (2)
#define O_TRUNC (512)

// /usr/include/unistd.h 

#define STDIN_FILENO (0)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define O_SYNC (1052672)

// /usr/include/fcntl.h 

#define SEEK_CUR (1)

// /usr/include/unistd.h 

#define X_OK (1)
#define _POSIX2_C_BIND __POSIX2_THIS_VERSION

// /usr/include/time.h 

#define __clock_t_defined (1)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZET_

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __U16_TYPE unsigned short int

// /usr/include/fcntl.h 

#define S_IWGRP (16)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define __O_TMPFILE (4259840)
#define F_GETOWN __F_GETOWN
#define O_FSYNC O_SYNC

// /usr/include/fcntl.h 

#define SEEK_END (2)

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __nlink_t_defined

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define ___int_size_t_h

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define __S_TYPEISSHM(buf) ( ( buf ) -> st_mode - ( buf ) -> st_mode )

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_GETFL (3)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _GCC_SIZE_T

// /usr/include/fcntl.h 

#define S_ISUID __S_ISUID

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __ino64_t_defined

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_SETLKW F_SETLKW64

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define _BITS_STAT_H (1)

// /usr/include/unistd.h 

#define _XOPEN_XPG4 (1)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define __F_SETOWN (8)

// /usr/include/unistd.h 

#define _XOPEN_UNIX (1)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __ULONGWORD_TYPE unsigned long int

// /usr/include/fcntl.h 

#define S_IXUSR __S_IEXEC

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define __S_IWRITE (128)

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __off_t_defined

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define FD_CLOEXEC (1)

// /usr/include/unistd.h 

#define STDOUT_FILENO (1)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_DUPFD (0)

// /usr/include/fcntl.h 

#define creat creat64

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define O_ACCMODE (3)

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define __S_IFSOCK (49152)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __size_t

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define __S_IEXEC (64)
#define __S_IFDIR (16384)

// /usr/include/unistd.h 

#define R_OK (4)

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __suseconds_t_defined
#define __int8_t_defined

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define O_RDONLY (0)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SLONG32_TYPE int

// /usr/include/unistd.h 

#define _POSIX2_C_VERSION __POSIX2_THIS_VERSION

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_RDLCK (0)
#define O_NOCTTY (256)

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __BIT_TYPES_DEFINED__ (1)

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define __S_IFREG (32768)
#define __S_TYPEISMQ(buf) ( ( buf ) -> st_mode - ( buf ) -> st_mode )
#define __S_IFIFO (4096)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define O_NDELAY O_NONBLOCK

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define __S_IREAD (256)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __U64_TYPE unsigned long int

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_SETFL (4)

// /usr/include/fcntl.h 

#define S_IFIFO __S_IFIFO

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define O_RDWR (2)

// /usr/include/fcntl.h 

#define S_IFREG __S_IFREG

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_WRLCK (1)
#define F_GETFD (1)

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __fsfilcnt_t_defined

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_EXLCK (4)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SYS_SIZE_T_H

// /usr/include/fcntl.h 

#define S_IRUSR __S_IREAD
#define S_IFMT __S_IFMT

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _BSD_SIZE_T_

// /usr/include/fcntl.h 

#define open open64
#define S_IFBLK __S_IFBLK
#define SEEK_SET (0)
#define S_ISVTX __S_ISVTX

// /usr/include/unistd.h 

#define _POSIX2_VERSION __POSIX2_THIS_VERSION

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __blkcnt_t_defined
#define __ino_t_defined

// /usr/include/fcntl.h 

#define S_IRWXU (448)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define __O_DIRECT (16384)
#define O_ASYNC (8192)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SLONGWORD_TYPE long int

// /usr/include/unistd.h 

#define lseek lseek64

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __key_t_defined

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __U32_TYPE unsigned int
#define __ULONG32_TYPE unsigned int

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_DEFINED_

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SQUAD_TYPE long int

// /usr/include/fcntl.h 

#define __OPEN_NEEDS_MODE(oflag) ( ( ( oflag ) & O_CREAT ) != 0 || ( ( oflag ) & __O_TMPFILE ) == __O_TMPFILE )

// /usr/include/time.h 

#define __timespec_defined (1)

// /usr/include/unistd.h 

#define __socklen_t_defined

// /usr/include/fcntl.h 

#define S_IXOTH (1)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_DECLARED

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define O_DSYNC __O_DSYNC

// /usr/include/fcntl.h 

#define S_IXGRP (8)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define __POSIX_FADV_NOREUSE (5)

// /usr/include/fcntl.h 

#define S_ISGID __S_ISGID

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define __S_IFMT (61440)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define __POSIX_FADV_DONTNEED (4)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __SIZE_T__

// /usr/include/unistd.h 

#define _XOPEN_LEGACY (1)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define O_EXCL (128)

// /usr/include/unistd.h 

#define __intptr_t_defined
#define __POSIX2_THIS_VERSION (199506l)

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define _SYS_TYPES_H (1)
#define __need_clockid_t

// /usr/include/fcntl.h 

#define S_IRGRP (32)

// /usr/include/time.h 

#define _TIME_H (1)

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __fsblkcnt_t_defined

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define O_LARGEFILE __O_LARGEFILE

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SWORD_TYPE long int

// /usr/include/unistd.h 

#define F_TLOCK (2)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __UWORD_TYPE unsigned long int

// /usr/include/time.h 

#define __isleap(year) ( ( year ) % 4 == 0 && ( ( year ) % 100 != 0 || ( year ) % 400 == 0 ) )

// /usr/include/unistd.h 

#define lockf lockf64

// /usr/include/time.h 

#define __timer_t_defined (1)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_SETOWN __F_SETOWN

// /usr/include/unistd.h 

#define truncate truncate64

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __uid_t_defined

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define _STAT_VER_LINUX (1)

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __gid_t_defined

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define O_CREAT (64)

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define __S_IFLNK (40960)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _T_SIZE
#define NULL ( ( void * ) 0 )

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define O_WRONLY (1)
#define O_RSYNC O_SYNC
#define __O_NOATIME (262144)

// /usr/include/unistd.h 

#define pread pread64

// /usr/include/fcntl.h 

#define _FCNTL_H (1)

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __dev_t_defined

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_SHLCK (8)

// /usr/include/time.h 

#define __clockid_t_defined (1)

// /usr/include/unistd.h 

#define F_OK (0)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_SETLK F_SETLK64
#define O_NONBLOCK (2048)

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define _MKNOD_VER_LINUX (0)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __SIZE_T

// /usr/include/fcntl.h 

#define S_IFDIR __S_IFDIR

// /usr/include/unistd.h 

#define _XOPEN_VERSION (500)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _T_SIZE_

// /usr/include/unistd.h 

#define _XOPEN_CRYPT (1)

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define __F_SETOWN_EX (15)
#define __F_SETSIG (10)

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define _STATBUF_ST_BLKSIZE

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define __O_PATH (2097152)

// /usr/include/fcntl.h 

#define S_IROTH (4)

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define _STATBUF_ST_NSEC
#define _STAT_VER _STAT_VER_LINUX
#define __S_IFCHR (8192)

// /usr/include/unistd.h 

#define F_LOCK (1)

// /usr/include/x86_64-linux-gnu/sys/types.h 

#define __pid_t_defined

// /usr/include/unistd.h 

#define F_TEST (3)

// /usr/include/fcntl.h 

#define S_IWOTH (2)
#define S_IFSOCK __S_IFSOCK

// /usr/include/unistd.h 

#define _UNISTD_H (1)

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define __S_IFBLK (24576)

// /usr/include/fcntl.h 

#define S_IFCHR __S_IFCHR

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __S32_TYPE int

// /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h 

#define F_UNLCK (2)

// /usr/include/x86_64-linux-gnu/bits/stat.h 

#define __S_ISUID (2048)

// /usr/include/unistd.h 

#define W_OK (2)

// /usr/include/fcntl.h 

#define S_IRWXG (56)
