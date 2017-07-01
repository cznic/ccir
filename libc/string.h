//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _STRING_H_
#define _STRING_H_

#include __header(string)

int strerror_r(int errnum, char *buf, __SIZE_TYPE__ buflen);

#endif				/* _STRING_H_ */
