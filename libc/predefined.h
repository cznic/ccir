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

typedef char *__builtin_va_list;

#ifdef _WIN32
    #define _MSC_VER 1600
    // TODO: not sure if we might want a `#define _MSVCRT_`?
    #define __MINGW_EXTENSION
    
    // this is set because we set _MSC_VER, we need to get rid of it though
    #define __restrict__

    #define __int64 long long

    // prevent _mingw_stdarg.h from doing "#define va_start _crt_va_start" which results in
    // "cannot redefine an object-like macro __va_copy using a function-like macro"
    // luckily this header doesn't do anything else besides messing that up
    #define _INC_STDARG

    // from builtin somehow they are not applied...
    #define __builtin_va_start(ap, arg) ap = (__builtin_va_list)(&arg)
    #define __builtin_va_end(ap) ap = 0

    #define _VA_LIST_DEFINED
    typedef __builtin_va_list va_list;

    #define __inline inline
    #define __forceinline inline __attribute__((__always_inline__))

    // make sure we can redirect some functions like sprintf (else we do not have a definition of them at all)
    #define __USE_MINGW_ANSI_STDIO 0

    // missing in MINGW, but used by TCC tests
    #define index(s, c) strchr(s, c)
    #define rindex(s, c) strrchr(s, c)
#endif

//TODO int128
#undef __SIZEOF_INT128__

#undef __ELF__

#endif				/* _PREDEFINED_H_ */
