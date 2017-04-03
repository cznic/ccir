//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _STRINGS_H_
#define _STRINGS_H_

typedef __LOCALE_TYPE__ locale_t;
typedef __SIZE_TYPE__ size_t;

#define index(a, b) strchr(a, b)
#define rindex(a, b) strrchr(a, b)

#endif				/* _STRINGS_H_ */
