//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

#ifndef _SYS_SELECT_H_
#define _SYS_SELECT_H_

#include __header(sys/select)

int __FD_ISSET(int n, fd_set * s)
{
	return (s->fds_bits[n / __NFDBITS] & (1 << (n & (__NFDBITS - 1)))) != 0;
}

void __FD_SET(int n, fd_set * s)
{
	s->fds_bits[n / __NFDBITS] |= 1 << (n & (__NFDBITS - 1));
}

void __FD_ZERO(fd_set * s)
{
	for (int i = 0; i < FD_SETSIZE / __NFDBITS; i++) {
		s->fds_bits[i] = 0;
	}
}

#endif				/* _SYS_SELECT_H_ */
