//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _FCNTL_H_
#define _FCNTL_H_

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include __header(fcntl)

#define O_ACCMODE 3
#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2
#define O_CREAT 64
#define O_EXCL 128
#define O_NOCTTY 256
#define O_TRUNC 512
#define O_APPEND 1024
#define O_NONBLOCK 2048
#define O_NDELAY O_NONBLOCK
#define O_SYNC 1052672
#define O_FSYNC O_SYNC
#define O_ASYNC 8192
#define F_GETLK 5
#define F_SETLK 6
#define F_SETLKW 7
#define F_DUPFD 0
#define F_GETFD 1
#define F_SETFD 2
#define F_GETFL 3
#define F_SETFL 4
#define FD_CLOEXEC 1
#define F_RDLCK 0
#define F_WRLCK 1
#define F_UNLCK 2
#define F_EXLCK 4
#define F_SHLCK 8
#define F_GETLK64 5
#define F_SETLK64 6
#define F_SETLKW64 7

struct flock {
	short l_type;		// Type of lock; F_RDLCK, F_WRLCK, F_UNLCK. 
	short l_whence;		// Flag for starting offset. 
	off_t l_start;		// Relative offset in bytes. 
	off_t l_len;		// Size; if 0 then until EOF. 
	pid_t l_pid;		// Process ID of the process holding the lock; returned with F_GETLK.
};

#endif				/* _FCNTL_H_ */
