//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _TIME_H_
#define _TIME_H_

#include <sys/types.h>
#include <locale.h>
#include <signal.h>
#include <stddef.h>
#include __header(time)

struct timespec {
	time_t tv_sec;		// Seconds. 
	long tv_nsec;		// Nanoseconds. 
};

#endif				/* _TIME_H_ */
