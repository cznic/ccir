//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _TIME_H_
#define _TIME_H_

typedef __CLOCK_TYPE__ clock_t;
typedef __TIME_TYPE__ time_t;

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
};

struct timespec {
	time_t tv_sec;		/* seconds */
	long tv_nsec;		/* nanoseconds */
};

#endif				/* _TIME_H_ */
