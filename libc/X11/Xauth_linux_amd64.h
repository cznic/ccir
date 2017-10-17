// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

// ----------------------------------------------------------------------------
//      /usr/include/X11/Xauth.h
// ----------------------------------------------------------------------------
/*

Copyright 1988, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

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
//      /usr/include/wchar.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1995-2016 Free Software Foundation, Inc.
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
//      /usr/include/libio.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Written by Per Bothner <bothner@cygnus.com>.

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
   <http://www.gnu.org/licenses/>.

   As a special exception, if you link the code in this file with
   files compiled with a GNU compiler to produce an executable,
   that does not cause the resulting executable to be covered by
   the GNU Lesser General Public License.  This exception does not
   however invalidate any other reasons why the executable file
   might be covered by the GNU Lesser General Public License.
   This exception applies to code released by its copyright holders
   in files containing the exception.  */

typedef struct xauth {
	unsigned short family;
	unsigned short address_length;
	char *address;
	unsigned short number_length;
	char *number;
	unsigned short name_length;
	char *name;
	unsigned short data_length;
	char *data;
} Xauth;
// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h

typedef long unsigned int size_t;
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
// /usr/include/stdio.h

struct _IO_FILE;
typedef struct _IO_FILE FILE;
typedef struct _IO_FILE __FILE;
// /usr/include/wchar.h

typedef struct {
	int __count;
	union {
		unsigned int __wch;
		char __wchb[4];
	} __value;
} __mbstate_t;
// /usr/include/_G_config.h

typedef struct {
	__off_t __pos;
	__mbstate_t __state;
} _G_fpos_t;
typedef struct {
	__off64_t __pos;
	__mbstate_t __state;
} _G_fpos64_t;
// /usr/include/libio.h

struct _IO_jump_t;
struct _IO_FILE;
typedef void _IO_lock_t;
struct _IO_marker {
	struct _IO_marker *_next;
	struct _IO_FILE *_sbuf;
	int _pos;
};
enum __codecvt_result { __codecvt_ok, __codecvt_partial, __codecvt_error, __codecvt_noconv };
struct _IO_FILE {
	int _flags;
	char *_IO_read_ptr;
	char *_IO_read_end;
	char *_IO_read_base;
	char *_IO_write_base;
	char *_IO_write_ptr;
	char *_IO_write_end;
	char *_IO_buf_base;
	char *_IO_buf_end;
	char *_IO_save_base;
	char *_IO_backup_base;
	char *_IO_save_end;
	struct _IO_marker *_markers;
	struct _IO_FILE *_chain;
	int _fileno;
	int _flags2;
	__off_t _old_offset;
	unsigned short _cur_column;
	signed char _vtable_offset;
	char _shortbuf[1];
	_IO_lock_t *_lock;
	__off64_t _offset;
	void *__pad1;
	void *__pad2;
	void *__pad3;
	void *__pad4;
	size_t __pad5;
	int _mode;
	char _unused2[20ul];
};
typedef struct _IO_FILE _IO_FILE;
struct _IO_FILE_plus;
extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
typedef __ssize_t __io_read_fn(void *__cookie, char *__buf, size_t __nbytes);
typedef __ssize_t __io_write_fn(void *__cookie, const char *__buf, size_t __n);
typedef int __io_seek_fn(void *__cookie, __off64_t * __pos, int __w);
typedef int __io_close_fn(void *__cookie);
extern int __underflow(_IO_FILE *);
extern int __uflow(_IO_FILE *);
extern int __overflow(_IO_FILE *, int);
extern int _IO_getc(_IO_FILE * __fp);
extern int _IO_putc(int __c, _IO_FILE * __fp);
extern int _IO_feof(_IO_FILE * __fp);
extern int _IO_ferror(_IO_FILE * __fp);
extern int _IO_peekc_locked(_IO_FILE * __fp);
extern void _IO_flockfile(_IO_FILE *);
extern void _IO_funlockfile(_IO_FILE *);
extern int _IO_ftrylockfile(_IO_FILE *);
extern int _IO_vfscanf(_IO_FILE *, const char *, __gnuc_va_list, int *);
extern int _IO_vfprintf(_IO_FILE *, const char *, __gnuc_va_list);
extern __ssize_t _IO_padn(_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn(_IO_FILE *, void *, size_t);
extern __off64_t _IO_seekoff(_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos(_IO_FILE *, __off64_t, int);
extern void _IO_free_backup_area(_IO_FILE *);
// /usr/include/stdio.h

typedef __off64_t off_t;
typedef __off64_t off64_t;
typedef _G_fpos64_t fpos_t;
typedef _G_fpos64_t fpos64_t;
extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;
extern int remove(const char *__filename);
extern int rename(const char *__old, const char *__new);
extern FILE *tmpfile64(void);
extern char *tmpnam(char *__s);
extern char *tempnam(const char *__dir, const char *__pfx);
extern int fclose(FILE * __stream);
extern int fflush(FILE * __stream);
extern FILE *fopen64(const char *__filename, const char *__modes);
extern FILE *freopen64(const char *__filename, const char *__modes, FILE * __stream);
extern FILE *fdopen(int __fd, const char *__modes);
extern void setbuf(FILE * __stream, char *__buf);
extern int setvbuf(FILE * __stream, char *__buf, int __modes, size_t __n);
extern int fprintf(FILE * __stream, const char *__format, ...);
extern int printf(const char *__format, ...);
extern int sprintf(char *__s, const char *__format, ...);
extern int vfprintf(FILE * __s, const char *__format, __gnuc_va_list __arg);
extern int vprintf(const char *__format, __gnuc_va_list __arg);
extern int vsprintf(char *__s, const char *__format, __gnuc_va_list __arg);
extern int snprintf(char *__s, size_t __maxlen, const char *__format, ...);
extern int vsnprintf(char *__s, size_t __maxlen, const char *__format, __gnuc_va_list __arg);
extern int fscanf(FILE * __stream, const char *__format, ...);
extern int scanf(const char *__format, ...);
extern int sscanf(const char *__s, const char *__format, ...);
extern int __isoc99_fscanf(FILE * __stream, const char *__format, ...);
extern int __isoc99_scanf(const char *__format, ...);
extern int __isoc99_sscanf(const char *__s, const char *__format, ...);
extern int vfscanf(FILE * __s, const char *__format, __gnuc_va_list __arg);
extern int vscanf(const char *__format, __gnuc_va_list __arg);
extern int vsscanf(const char *__s, const char *__format, __gnuc_va_list __arg);
extern int __isoc99_vfscanf(FILE * __s, const char *__format, __gnuc_va_list __arg);
extern int __isoc99_vscanf(const char *__format, __gnuc_va_list __arg);
extern int __isoc99_vsscanf(const char *__s, const char *__format, __gnuc_va_list __arg);
extern int fgetc(FILE * __stream);
extern int getc(FILE * __stream);
extern int getchar(void);
extern int getc_unlocked(FILE * __stream);
extern int getchar_unlocked(void);
extern int fputc(int __c, FILE * __stream);
extern int putc(int __c, FILE * __stream);
extern int putchar(int __c);
extern int putc_unlocked(int __c, FILE * __stream);
extern int putchar_unlocked(int __c);
extern int getw(FILE * __stream);
extern int putw(int __w, FILE * __stream);
extern char *fgets(char *__s, int __n, FILE * __stream);
extern char *gets(char *__s);
extern int fputs(const char *__s, FILE * __stream);
extern int puts(const char *__s);
extern int ungetc(int __c, FILE * __stream);
extern size_t fread(void *__ptr, size_t __size, size_t __n, FILE * __stream);
extern size_t fwrite(const void *__ptr, size_t __size, size_t __n, FILE * __s);
extern int fseek(FILE * __stream, long int __off, int __whence);
extern long int ftell(FILE * __stream);
extern void rewind(FILE * __stream);
extern int fseeko64(FILE * __stream, __off64_t __off, int __whence);
extern __off64_t ftello64(FILE * __stream);
extern int fgetpos64(FILE * __stream, fpos64_t * __pos);
extern int fsetpos64(FILE * __stream, const fpos64_t * __pos);
extern void clearerr(FILE * __stream);
extern int feof(FILE * __stream);
extern int ferror(FILE * __stream);
extern void perror(const char *__s);
extern int fileno(FILE * __stream);
extern FILE *popen(const char *__command, const char *__modes);
extern int pclose(FILE * __stream);
extern char *ctermid(char *__s);
extern char *cuserid(char *__s);
extern void flockfile(FILE * __stream);
extern int ftrylockfile(FILE * __stream);
extern void funlockfile(FILE * __stream);
// /usr/include/X11/Xauth.h

char *XauFileName(void);
Xauth *XauReadAuth(FILE *);
int XauLockAuth(const char *, int, int, long);
int XauUnlockAuth(const char *);
int XauWriteAuth(FILE *, Xauth *);
Xauth *XauGetAuthByAddr(unsigned short, unsigned short, const char *, unsigned short, const char *, unsigned short, const char *);
Xauth *XauGetBestAuthByAddr(unsigned short, unsigned short, const char *, unsigned short, const char *, int, char **, const int *);
void XauDisposeAuth(Xauth *);

// /usr/include/stdio.h 

#define vfscanf __isoc99_vfscanf

// /usr/include/libio.h 

#define _IO_ERR_SEEN (32)

// /usr/include/X11/Xauth.h 

#define LOCK_SUCCESS (0)

// /usr/include/wchar.h 

#define ____mbstate_t_defined (1)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SLONGWORD_TYPE long int
#define __SQUAD_TYPE long int

// /usr/include/libio.h 

#define _IO_peekc(_fp) _IO_peekc_unlocked ( _fp )

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define _BITS_TYPES_H (1)

// /usr/include/libio.h 

#define _IO_LINKED (128)

// /usr/include/_G_config.h 

#define _G_HAVE_ST_BLKSIZE defined ( _STATBUF_ST_BLKSIZE )

// /usr/include/libio.h 

#define _IO_LINE_BUF (512)

// /usr/include/stdio.h 

#define vsscanf __isoc99_vsscanf

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SYS_SIZE_T_H

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __ULONGWORD_TYPE unsigned long int

// /usr/include/stdio.h 

#define SEEK_CUR (1)

// /usr/include/libio.h 

#define _IO_uid_t __uid_t

// /usr/include/stdio.h 

#define stderr stderr

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __size_t__

// /usr/include/stdio.h 

#define fgetpos fgetpos64

// /usr/include/libio.h 

#define _IO_getc_unlocked(_fp) ( _IO_BE ( ( _fp ) -> _IO_read_ptr >= ( _fp ) -> _IO_read_end , 0 ) ? __uflow ( _fp ) : * ( unsigned char * ) ( _fp ) -> _IO_read_ptr ++ )
#define _IOS_NOREPLACE (64)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _BSD_SIZE_T_DEFINED_

// /usr/include/libio.h 

#define _IO_BUFSIZ _G_BUFSIZ
#define _IO_HAVE_ST_BLKSIZE _G_HAVE_ST_BLKSIZE

// /usr/include/stdio.h 

#define putc(_ch, _fp) _IO_putc ( _ch , _fp )

// /usr/include/libio.h 

#define _IO_funlockfile(_fp)

// /usr/include/X11/Xauth.h 

#define LOCK_ERROR (1)

// /usr/include/libio.h 

#define _IOS_NOCREATE (32)

// /usr/include/stdio.h 

#define _STDIO_H (1)
#define _IOLBF (1)

// /usr/include/libio.h 

#define _IO_IS_FILEBUF (8192)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __U16_TYPE unsigned short int

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _T_SIZE_

// /usr/include/libio.h 

#define _IO_stderr ( ( _IO_FILE * ) ( & _IO_2_1_stderr_ ) )
#define _IO_FLAGS2_MMAP (1)

// /usr/include/stdio.h 

#define scanf __isoc99_scanf

// /usr/include/libio.h 

#define _IO_UPPERCASE (512)
#define _OLD_STDIO_MAGIC (4206624768u)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SWORD_TYPE long int

// /usr/include/libio.h 

#define _IOS_INPUT (1)

// /usr/include/X11/Xauth.h 

#define FamilyLocalHost (252)

// /usr/include/stdio.h 

#define tmpfile tmpfile64

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_DEFINED

// /usr/include/libio.h 

#define _IO_pid_t __pid_t

// /usr/include/stdio.h 

#define ____FILE_defined (1)
#define BUFSIZ _IO_BUFSIZ

// /usr/include/libio.h 

#define _IO_ferror_unlocked(__fp) ( ( ( __fp ) -> _flags & _IO_ERR_SEEN ) != 0 )
#define _IO_IS_APPENDING (4096)
#define _IO_INTERNAL (8)
#define _IO_HEX (64)
#define _IO_UNBUFFERED (2)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __U32_TYPE unsigned int

// /usr/include/libio.h 

#define _IO_EOF_SEEN (16)
#define __HAVE_COLUMN

// /usr/include/stdio.h 

#define ftello ftello64

// /usr/include/libio.h 

#define _IO_TIED_PUT_GET (1024)
#define _IO_stdin ( ( _IO_FILE * ) ( & _IO_2_1_stdin_ ) )

// /usr/include/stdio.h 

#define stdin stdin

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _BSD_SIZE_T_

// /usr/include/stdio.h 

#define fseeko fseeko64

// /usr/include/libio.h 

#define _IO_file_flags _flags
#define _IO_USER_LOCK (32768)
#define _IO_USER_BUF (1)

// /usr/include/stdio.h 

#define __off64_t_defined

// /usr/include/libio.h 

#define _IO_stdout ( ( _IO_FILE * ) ( & _IO_2_1_stdout_ ) )

// /usr/include/stdio.h 

#define _IOFBF (0)

// /usr/include/libio.h 

#define _IO_FLAGS2_USER_WBUF (8)
#define _IO_CURRENTLY_PUTTING (2048)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __size_t

// /usr/include/libio.h 

#define _IO_wint_t wint_t

// /usr/include/_G_config.h 

#define _G_HAVE_MREMAP (1)

// /usr/include/libio.h 

#define _IO_ssize_t __ssize_t

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _GCC_SIZE_T

// /usr/include/libio.h 

#define _IOS_TRUNC (16)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_DEFINED_

// /usr/include/libio.h 

#define _IO_DEC (16)

// /usr/include/_G_config.h 

#define _G_IO_IO_FILE_VERSION (131073)

// /usr/include/libio.h 

#define _IOS_BIN (128)
#define _IO_SHOWPOINT (256)

// /usr/include/X11/Xauth.h 

#define FamilyNetname (254)

// /usr/include/libio.h 

#define _IO_ftrylockfile(_fp)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_DECLARED

// /usr/include/libio.h 

#define _IO_off_t __off_t

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __S16_TYPE short int

// /usr/include/X11/Xauth.h 

#define LOCK_TIMEOUT (2)

// /usr/include/libio.h 

#define _IO_cleanup_region_end(_Doit)
#define EOF (-1)
#define _IO_BE(expr, res) ( expr )
#define _IO_BAD_SEEN (16384)

// /usr/include/stdio.h 

#define stdout stdout
#define __FILE_defined (1)

// /usr/include/_G_config.h 

#define _G_HAVE_MMAP (1)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __SIZE_T__

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __S32_TYPE int

// /usr/include/stdio.h 

#define freopen freopen64

// /usr/include/libio.h 

#define _IO_SHOWPOS (1024)

// /usr/include/_G_config.h 

#define _G_BUFSIZ (8192)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __U64_TYPE unsigned long int

// /usr/include/libio.h 

#define _IO_IN_BACKUP (256)
#define _IO_OCT (32)
#define _IO_va_list __gnuc_va_list
#define _IO_putc_unlocked(_ch, _fp) ( _IO_BE ( ( _fp ) -> _IO_write_ptr >= ( _fp ) -> _IO_write_end , 0 ) ? __overflow ( _fp , ( unsigned char ) ( _ch ) ) : ( unsigned char ) ( * ( _fp ) -> _IO_write_ptr ++ = ( _ch ) ) )
#define _IO_DELETE_DONT_CLOSE (64)
#define _IO_STDIO (16384)
#define _IO_peekc_unlocked(_fp) ( _IO_BE ( ( _fp ) -> _IO_read_ptr >= ( _fp ) -> _IO_read_end , 0 ) && __underflow ( _fp ) == EOF ? EOF : * ( unsigned char * ) ( _fp ) -> _IO_read_ptr )
#define _IO_off64_t __off64_t

// /usr/include/X11/Xauth.h 

#define FamilyWild (65535)

// /usr/include/libio.h 

#define _IO_DONT_CLOSE (32768)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __SIZE_T

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SLONG32_TYPE int
#define __UQUAD_TYPE unsigned long int

// /usr/include/stdio.h 

#define SEEK_SET (0)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _T_SIZE

// /usr/include/stdio.h 

#define getc(_fp) _IO_getc ( _fp )

// /usr/include/libio.h 

#define _IO_SKIPWS (1)

// /usr/include/X11/Xauth.h 

#define FamilyKrb5Principal (253)

// /usr/include/libio.h 

#define _IO_feof_unlocked(__fp) ( ( ( __fp ) -> _flags & _IO_EOF_SEEN ) != 0 )

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define NULL ( ( void * ) 0 )

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __S64_TYPE long int

// /usr/include/libio.h 

#define _IO_flockfile(_fp)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_

// /usr/include/libio.h 

#define _IOS_ATEND (4)
#define _IO_PENDING_OUTPUT_COUNT(_fp) ( ( _fp ) -> _IO_write_ptr - ( _fp ) -> _IO_write_base )

// /usr/include/string.h 

#define _STRING_H (1)

// /usr/include/stdio.h 

#define fsetpos fsetpos64

// /usr/include/libio.h 

#define _IO_NO_READS (4)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __ULONG32_TYPE unsigned int

// /usr/include/stdio.h 

#define _STDIO_USES_IOSTREAM

// /usr/include/libio.h 

#define _IO_UNITBUF (8192)
#define _IO_RIGHT (4)

// /usr/include/stdio.h 

#define fscanf __isoc99_fscanf

// /usr/include/libio.h 

#define _IO_NO_WRITES (8)
#define _IO_SHOWBASE (128)

// /usr/include/X11/Xauth.h 

#define _Xauth_h

// /usr/include/libio.h 

#define _IO_FIXED (4096)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZET_

// /usr/include/stdio.h 

#define __off_t_defined

// /usr/include/libio.h 

#define _IOS_APPEND (8)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T

// /usr/include/libio.h 

#define _IO_FLAGS2_NOTCANCEL (2)

// /usr/include/stdio.h 

#define sscanf __isoc99_sscanf

// /usr/include/libio.h 

#define _IO_MAGIC (4222418944u)
#define _IO_LEFT (2)
#define _IO_iconv_t _G_iconv_t
#define _IO_cleanup_region_start(_fct, _fp)

// /usr/include/stdio.h 

#define fopen fopen64

// /usr/include/_G_config.h 

#define _G_va_list __gnuc_va_list

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __UWORD_TYPE unsigned long int

// /usr/include/_G_config.h 

#define _G_config_h (1)

// /usr/include/libio.h 

#define _IO_fpos64_t _G_fpos64_t

// /usr/include/stdio.h 

#define _IONBF (2)
#define P_tmpdir "/tmp"

// /usr/include/libio.h 

#define _IO_MAGIC_MASK (4294901760u)

// /usr/include/stdio.h 

#define vscanf __isoc99_vscanf

// /usr/include/libio.h 

#define _IO_BOOLALPHA (65536)
#define _IO_size_t size_t
#define _IO_SCIENTIFIC (2048)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define ___int_size_t_h

// /usr/include/libio.h 

#define _IO_fpos_t _G_fpos_t

// /usr/include/stdio.h 

#define SEEK_END (2)

// /usr/include/libio.h 

#define _IO_STDIO_H
#define _IOS_OUTPUT (2)

// /usr/include/X11/Xauth.h 

#define FamilyLocal (256)

// /usr/include/libio.h 

#define _IO_UNIFIED_JUMPTABLES (1)
