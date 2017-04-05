//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_

#include <stdint.h>

typedef __clock_t clock_t;
typedef int pid_t;
typedef int pthread_attr_t;
typedef long blkcnt_t;
typedef long blksize_t;
typedef long long off_t;
typedef long ssize_t;
typedef long time_t;
typedef uint32_t dev_t;
typedef uint32_t nlink_t;
typedef unsigned gid_t;
typedef unsigned ino_t;
typedef unsigned short mode_t;
typedef unsigned uid_t;
typedef void *pthread_t;

typedef struct pthread_mutexattr_t {
	int type;
	int robustness;
} pthread_mutexattr_t;

typedef struct pthread_mutex_t {
	pthread_mutexattr_t attr;
	struct sync_Mutex {
		int state;
		unsigned sema;
	} innerMu, outerMu;
	pthread_t owner;
	int cnt;
} pthread_mutex_t;

#endif				/* _SYS_TYPES_H_ */
