//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

#ifndef _DLFCN_H_
#define _DLFCN_H_

#include __header(dlfcn)

#define RTLD_LAZY 1
#define RTLD_NOW 2
#define RTLD_BINDING_MASK 3
#define RTLD_NOLOAD 4
#define RTLD_DEEPBIND 8
#define RTLD_GLOBAL 256
#define RTLD_LOCAL 0
#define RTLD_NODELETE 4096

#endif				/* _DLFCN_H_ */
