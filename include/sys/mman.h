//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#include <sys/types.h>

#define PROT_READ       0x1
#define PROT_WRITE      0x2
#define PROT_EXEC       0x4
#define PROT_SEM        0x8
#define PROT_NONE       0x0
#define PROT_GROWSDOWN  0x01000000
#define PROT_GROWSUP    0x02000000

#define MAP_SHARED      0x001
#define MAP_PRIVATE     0x002
#define MAP_TYPE        0x00f
#define MAP_FIXED       0x010
#define MAP_RENAME      0x020
#define MAP_AUTOGROW    0x040
#define MAP_LOCAL       0x080
#define MAP_AUTORSRV    0x100
#define MAP_NORESERVE   0x0400
#define MAP_ANONYMOUS   0x0800
#define MAP_GROWSDOWN   0x1000
#define MAP_DENYWRITE   0x2000
#define MAP_EXECUTABLE  0x4000
#define MAP_LOCKED      0x8000
#define MAP_POPULATE    0x10000
#define MAP_NONBLOCK    0x20000
#define MAP_STACK       0x40000
#define MAP_HUGETLB     0x80000

#define MAP_FAILED (void *)-1

int munmap(void *addr, size_t length);
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

#endif				/* _SYS_MMAN_H_ */
