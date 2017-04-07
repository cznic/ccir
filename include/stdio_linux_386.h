// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

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

#define _STDIO_H (1)
struct _IO_FILE;
typedef struct _IO_FILE FILE;
#define __FILE_defined (1)
typedef struct _IO_FILE __FILE;
#define ____FILE_defined (1)
#define _STDIO_USES_IOSTREAM
typedef _G_fpos_t fpos_t;
#define _IOFBF (0)
#define _IOLBF (1)
#define _IONBF (2)
#define BUFSIZ _IO_BUFSIZ
#define SEEK_SET (0)
#define SEEK_CUR (1)
#define SEEK_END (2)
extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;
#define stdin stdin
#define stdout stdout
#define stderr stderr
extern int remove(char *__filename);
extern int rename(char *__old, char *__new);
extern FILE *tmpfile(void);
extern char *tmpnam(char *__s);
extern int fclose(FILE * __stream);
extern int fflush(FILE * __stream);
extern FILE *fopen(char *__filename, char *__modes);
extern FILE *freopen(char *__filename, char *__modes, FILE * __stream);
extern void setbuf(FILE * __stream, char *__buf);
extern int setvbuf(FILE * __stream, char *__buf, int __modes, size_t __n);
extern int fprintf(FILE * __stream, char *__format, ...);
extern int printf(char *__format, ...);
extern int sprintf(char *__s, char *__format, ...);
extern int vfprintf(FILE * __s, char *__format, __gnuc_va_list __arg);
extern int vprintf(char *__format, __gnuc_va_list __arg);
extern int vsprintf(char *__s, char *__format, __gnuc_va_list __arg);
extern int snprintf(char *__s, size_t __maxlen, char *__format, ...);
extern int vsnprintf(char *__s, size_t __maxlen, char *__format, __gnuc_va_list __arg);
extern int fscanf(FILE * __stream, char *__format, ...);
extern int scanf(char *__format, ...);
extern int sscanf(char *__s, char *__format, ...);
extern int __isoc99_fscanf(FILE * __stream, char *__format, ...);
extern int __isoc99_scanf(char *__format, ...);
extern int __isoc99_sscanf(char *__s, char *__format, ...);
#define fscanf __isoc99_fscanf
#define scanf __isoc99_scanf
#define sscanf __isoc99_sscanf
extern int vfscanf(FILE * __s, char *__format, __gnuc_va_list __arg);
extern int vscanf(char *__format, __gnuc_va_list __arg);
extern int vsscanf(char *__s, char *__format, __gnuc_va_list __arg);
extern int __isoc99_vfscanf(FILE * __s, char *__format, __gnuc_va_list __arg);
extern int __isoc99_vscanf(char *__format, __gnuc_va_list __arg);
extern int __isoc99_vsscanf(char *__s, char *__format, __gnuc_va_list __arg);
#define vfscanf __isoc99_vfscanf
#define vscanf __isoc99_vscanf
#define vsscanf __isoc99_vsscanf
extern int fgetc(FILE * __stream);
extern int getc(FILE * __stream);
extern int getchar(void);
#define getc(_fp) _IO_getc ( _fp )
extern int fputc(int __c, FILE * __stream);
extern int putc(int __c, FILE * __stream);
extern int putchar(int __c);
#define putc(_ch, _fp) _IO_putc ( _ch , _fp )
extern char *fgets(char *__s, int __n, FILE * __stream);
extern char *gets(char *__s);
extern int fputs(char *__s, FILE * __stream);
extern int puts(char *__s);
extern int ungetc(int __c, FILE * __stream);
extern size_t fread(void *__ptr, size_t __size, size_t __n, FILE * __stream);
extern size_t fwrite(void *__ptr, size_t __size, size_t __n, FILE * __s);
extern int fseek(FILE * __stream, long int __off, int __whence);
extern long int ftell(FILE * __stream);
extern void rewind(FILE * __stream);
extern int fgetpos(FILE * __stream, fpos_t * __pos);
extern int fsetpos(FILE * __stream, fpos_t * __pos);
extern void clearerr(FILE * __stream);
extern int feof(FILE * __stream);
extern int ferror(FILE * __stream);
extern void perror(char *__s);
#define ____mbstate_t_defined (1)
typedef struct {
	int __count;
	union {
		unsigned int __wch;
		char __wchb[4];
	} __value;
} __mbstate_t;
#define _G_config_h (1)
typedef struct {
	__off_t __pos;
	__mbstate_t __state;
} _G_fpos_t;
typedef struct {
	__off64_t __pos;
	__mbstate_t __state;
} _G_fpos64_t;
#define _G_va_list __gnuc_va_list
#define _G_HAVE_MMAP (1)
#define _G_HAVE_MREMAP (1)
#define _G_IO_IO_FILE_VERSION (131073)
#define _G_HAVE_ST_BLKSIZE defined ( _STATBUF_ST_BLKSIZE )
#define _G_BUFSIZ (8192)
#define _IO_STDIO_H
#define _IO_fpos_t _G_fpos_t
#define _IO_fpos64_t _G_fpos64_t
#define _IO_size_t size_t
#define _IO_ssize_t __ssize_t
#define _IO_off_t __off_t
#define _IO_off64_t __off64_t
#define _IO_pid_t __pid_t
#define _IO_uid_t __uid_t
#define _IO_iconv_t _G_iconv_t
#define _IO_HAVE_ST_BLKSIZE _G_HAVE_ST_BLKSIZE
#define _IO_BUFSIZ _G_BUFSIZ
#define _IO_wint_t wint_t
#define _IO_va_list __gnuc_va_list
#define _IO_UNIFIED_JUMPTABLES (1)
#define EOF (-1)
#define _IOS_INPUT (1)
#define _IOS_OUTPUT (2)
#define _IOS_ATEND (4)
#define _IOS_APPEND (8)
#define _IOS_TRUNC (16)
#define _IOS_NOCREATE (32)
#define _IOS_NOREPLACE (64)
#define _IOS_BIN (128)
#define _IO_MAGIC (4222418944u)
#define _OLD_STDIO_MAGIC (4206624768u)
#define _IO_MAGIC_MASK (4294901760u)
#define _IO_USER_BUF (1)
#define _IO_UNBUFFERED (2)
#define _IO_NO_READS (4)
#define _IO_NO_WRITES (8)
#define _IO_EOF_SEEN (16)
#define _IO_ERR_SEEN (32)
#define _IO_DELETE_DONT_CLOSE (64)
#define _IO_LINKED (128)
#define _IO_IN_BACKUP (256)
#define _IO_LINE_BUF (512)
#define _IO_TIED_PUT_GET (1024)
#define _IO_CURRENTLY_PUTTING (2048)
#define _IO_IS_APPENDING (4096)
#define _IO_IS_FILEBUF (8192)
#define _IO_BAD_SEEN (16384)
#define _IO_USER_LOCK (32768)
#define _IO_FLAGS2_MMAP (1)
#define _IO_FLAGS2_NOTCANCEL (2)
#define _IO_FLAGS2_USER_WBUF (8)
#define _IO_SKIPWS (1)
#define _IO_LEFT (2)
#define _IO_RIGHT (4)
#define _IO_INTERNAL (8)
#define _IO_DEC (16)
#define _IO_OCT (32)
#define _IO_HEX (64)
#define _IO_SHOWBASE (128)
#define _IO_SHOWPOINT (256)
#define _IO_UPPERCASE (512)
#define _IO_SHOWPOS (1024)
#define _IO_SCIENTIFIC (2048)
#define _IO_FIXED (4096)
#define _IO_UNITBUF (8192)
#define _IO_STDIO (16384)
#define _IO_DONT_CLOSE (32768)
#define _IO_BOOLALPHA (65536)
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
	char _unused2[40u];
};
#define _IO_file_flags _flags
#define __HAVE_COLUMN
typedef struct _IO_FILE _IO_FILE;
struct _IO_FILE_plus;
extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
#define _IO_stdin ( ( _IO_FILE * ) ( & _IO_2_1_stdin_ ) )
#define _IO_stdout ( ( _IO_FILE * ) ( & _IO_2_1_stdout_ ) )
#define _IO_stderr ( ( _IO_FILE * ) ( & _IO_2_1_stderr_ ) )
typedef __ssize_t __io_read_fn(void *__cookie, char *__buf, size_t __nbytes);
typedef __ssize_t __io_write_fn(void *__cookie, char *__buf, size_t __n);
typedef int __io_seek_fn(void *__cookie, __off64_t * __pos, int __w);
typedef int __io_close_fn(void *__cookie);
extern int __underflow(_IO_FILE *);
extern int __uflow(_IO_FILE *);
extern int __overflow(_IO_FILE *, int);
#define _IO_BE(expr, res) ( expr )
#define _IO_getc_unlocked(_fp) ( _IO_BE ( ( _fp ) -> _IO_read_ptr >= ( _fp ) -> _IO_read_end , 0 ) ? __uflow ( _fp ) : * ( unsigned char * ) ( _fp ) -> _IO_read_ptr ++ )
#define _IO_peekc_unlocked(_fp) ( _IO_BE ( ( _fp ) -> _IO_read_ptr >= ( _fp ) -> _IO_read_end , 0 ) && __underflow ( _fp ) == EOF ? EOF : * ( unsigned char * ) ( _fp ) -> _IO_read_ptr )
#define _IO_putc_unlocked(_ch, _fp) ( _IO_BE ( ( _fp ) -> _IO_write_ptr >= ( _fp ) -> _IO_write_end , 0 ) ? __overflow ( _fp , ( unsigned char ) ( _ch ) ) : ( unsigned char ) ( * ( _fp ) -> _IO_write_ptr ++ = ( _ch ) ) )
#define _IO_feof_unlocked(__fp) ( ( ( __fp ) -> _flags & _IO_EOF_SEEN ) != 0 )
#define _IO_ferror_unlocked(__fp) ( ( ( __fp ) -> _flags & _IO_ERR_SEEN ) != 0 )
extern int _IO_getc(_IO_FILE * __fp);
extern int _IO_putc(int __c, _IO_FILE * __fp);
extern int _IO_feof(_IO_FILE * __fp);
extern int _IO_ferror(_IO_FILE * __fp);
extern int _IO_peekc_locked(_IO_FILE * __fp);
#define _IO_PENDING_OUTPUT_COUNT(_fp) ( ( _fp ) -> _IO_write_ptr - ( _fp ) -> _IO_write_base )
extern void _IO_flockfile(_IO_FILE *);
extern void _IO_funlockfile(_IO_FILE *);
extern int _IO_ftrylockfile(_IO_FILE *);
#define _IO_peekc(_fp) _IO_peekc_unlocked ( _fp )
#define _IO_flockfile(_fp)
#define _IO_funlockfile(_fp)
#define _IO_ftrylockfile(_fp)
#define _IO_cleanup_region_start(_fct, _fp)
#define _IO_cleanup_region_end(_Doit)
extern int _IO_vfscanf(_IO_FILE *, char *, __gnuc_va_list, int *);
extern int _IO_vfprintf(_IO_FILE *, char *, __gnuc_va_list);
extern __ssize_t _IO_padn(_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn(_IO_FILE *, void *, size_t);
extern __off64_t _IO_seekoff(_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos(_IO_FILE *, __off64_t, int);
extern void _IO_free_backup_area(_IO_FILE *);
