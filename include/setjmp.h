//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _SETJMP_H_
#define _SETJMP_H_

typedef __JMP_BUF_TYPE__ jmp_buf;

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);

#endif				/* _SETJMP_H_ */
