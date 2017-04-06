//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _PREDEFINED_H_
#define _PREDEFINED_H_

#define __str(x) #x
#define ____header(name, os, arch) __str(name##_##os##_##arch.h)
#define ___header(name, os, arch) ____header(name, os, arch)
#define __header(name) ___header(name, __os__, __arch__)

#include __header(predefined)

//TODO int128
#undef __SIZEOF_INT128__

#undef __ELF__

typedef char *__builtin_va_list;

#endif				/* _PREDEFINED_H_ */
