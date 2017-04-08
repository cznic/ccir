//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _STDIO_H_
#define _STDIO_H_

#include __header(stdio)

#undef getc
#define getc(x) fgetc(x)

#endif				/* _STDIO_H_ */
