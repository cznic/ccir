//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _FCNTL_H_
#define _FCNTL_H_

#include <stdio.h>
//#include <sys/stat.h>
#include <sys/types.h>

int fcntl(int fd, int cmd, ... /* arg */ );
int open(const char *pathname, int flags, ...);

#endif				/* _FCNTL_H_ */
