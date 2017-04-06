//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#include <sys/types.h>
#include __header(sys/mman)

#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4
#define PROT_NONE 0
#define PROT_GROWSDOWN 16777216
#define PROT_GROWSUP 33554432
#define MAP_SHARED 1
#define MAP_PRIVATE 2
#define MAP_FIXED 16
#define MS_ASYNC 1
#define MS_SYNC 4
#define MS_INVALIDATE 2
#define MCL_CURRENT 1
#define MCL_FUTURE 2
#define MCL_ONFAULT 4

#endif				/* _SYS_MMAN_H_ */
