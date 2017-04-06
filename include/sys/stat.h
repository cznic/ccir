//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#include <time.h>
#include <sys/types.h>
#include __header(sys/stat)

#define __S_IFMT 61440
#define __S_IFDIR 16384
#define __S_IFCHR 8192
#define __S_IFBLK 24576
#define __S_IFREG 32768
#define __S_IFIFO 4096
#define __S_IFLNK 40960
#define __S_IFSOCK 49152
#define __S_TYPEISMQ(buf) ( ( buf ) -> st_mode - ( buf ) -> st_mode )
#define __S_TYPEISSEM(buf) ( ( buf ) -> st_mode - ( buf ) -> st_mode )
#define __S_TYPEISSHM(buf) ( ( buf ) -> st_mode - ( buf ) -> st_mode )
#define __S_ISUID 2048
#define __S_ISGID 1024
#define __S_ISVTX 512
#define __S_IREAD 256
#define __S_IWRITE 128
#define __S_IEXEC 64

struct stat {
	dev_t st_dev;		/* ID of device containing file */
	ino_t st_ino;		/* inode number */
	mode_t st_mode;		/* file type and mode */
	nlink_t st_nlink;	/* number of hard links */
	uid_t st_uid;		/* user ID of owner */
	gid_t st_gid;		/* group ID of owner */
	dev_t st_rdev;		/* device ID (if special file) */
	off_t st_size;		/* total size, in bytes */
	blksize_t st_blksize;	/* blocksize for filesystem I/O */
	blkcnt_t st_blocks;	/* number of 512B blocks allocated */

	/* Since Linux 2.6, the kernel supports nanosecond
	   precision for the following timestamp fields.
	   For the details before Linux 2.6, see NOTES. */

	struct timespec st_atim;	/* time of last access */
	struct timespec st_mtim;	/* time of last modification */
	struct timespec st_ctim;	/* time of last status change */

#define st_atime st_atim.tv_sec	/* Backward compatibility */
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
};

int fchmod(int fd, mode_t mode);
int lstat(const char *pathname, struct stat *buf);

#endif				/* _SYS_STAT_H_ */
