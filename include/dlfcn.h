//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

#ifndef _DLFCN_H_
#define _DLFCN_H_

#define RTLD_LAZY	0x1
#define RTLD_NOW	0x2
#define RTLD_LOCAL	0x4
#define RTLD_GLOBAL	0x8

char *dlerror(void);
int dlclose(void *handle);
void *dlopen(const char *filename, int flags);
void *dlsym(void *handle, const char *symbol);

#endif				/* _DLFCN_H_ */
