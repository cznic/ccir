//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _ASSERT_H_
#define _ASSERT_H_

#include <stdio.h>
#include <stdlib.h>

#endif				/* _ASSERT_H_ */

#undef assert

#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(x) (void)((x) ? 0 : (fprintf(stderr, "%s:%s: assertion failure in %s: %s\n", __FILE__, __LINE__, __func__, #x), abort(), 0), 0)
#endif				/* NDEBUG */
