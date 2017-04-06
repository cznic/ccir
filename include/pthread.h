//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _PTHREAD_H_
#define _PTHREAD_H_

#include <sys/types.h>
#include <time.h>
#include <sched.h>
#include __header(pthread)

#undef PTHREAD_MUTEX_INITIALIZER
#define PTHREAD_MUTEX_INITIALIZER 0

enum {
	PTHREAD_MUTEX_RECURSIVE
};

int pthread_mutexattr_settype(pthread_mutexattr_t *, int);

#endif				/* _PTHREAD_H_ */
