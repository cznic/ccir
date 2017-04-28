//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _FCNTL_H_
#define _FCNTL_H_

#ifdef __linux__
#undef stat
#endif

#include __header(fcntl)

#ifdef __linux__
#define stat stat64
#endif

#endif				/* _FCNTL_H_ */
