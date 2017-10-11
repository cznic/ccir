//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

#ifndef _SYS_SELECT_H_
#define _SYS_SELECT_H_

#include __header(sys/select)

int __FD_ISSET(int, fd_set *);
void __FD_SET(int, fd_set *);
void __FD_ZERO(fd_set *);

#endif				/* _SYS_SELECT_H_ */
