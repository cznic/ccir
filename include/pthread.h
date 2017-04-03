//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _PTHREAD_H_
#define _PTHREAD_H_

#include <sys/types.h>

#define PTHREAD_MUTEXATTR_INITIALIZER {0, 0}
#define PTHREAD_MUTEX_INITIALIZER {PTHREAD_MUTEXATTR_INITIALIZER, {0, 0}, {0, 0}, 0, 0}

enum {
	PTHREAD_MUTEX_NORMAL,
	PTHREAD_MUTEX_ERRORCHECK,
	PTHREAD_MUTEX_RECURSIVE,
	PTHREAD_MUTEX_DEFAULT
};

#endif				/* _PTHREAD_H_ */
