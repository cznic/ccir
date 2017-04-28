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
    #define _MSC_VER 1200
    // needed for nameless unions
    #define _MSC_EXTENSIONS
    // TODO: not sure if we might want a `#define _MSVCRT_`?
    #define __MINGW_EXTENSION
    
    // this is set because we set _MSC_VER, we need to get rid of it though
    #define __restrict__

    #define __int32 long
    #define __int64 long long

    // prevent _mingw_stdarg.h from doing "#define va_start _crt_va_start" which results in
    // "cannot redefine an object-like macro __va_copy using a function-like macro"
    // luckily this header doesn't do anything else besides messing that up
    #define _INC_STDARG

    // from builtin somehow they are not applied... TODO
    #define __builtin_va_start(ap, arg) ap = (__builtin_va_list)(&arg)
    #define __builtin_va_end(ap) ap = 0  
    #define __builtin_offsetof(st, m) ((__SIZE_TYPE__)(&((st *)0)->m))
    int __builtin_fprintf(void *__stream, char *__format, ...);

    #define _VA_LIST_DEFINED
    typedef __builtin_va_list va_list;

    #define __inline inline
    #define __forceinline inline __attribute__((__always_inline__))

    // make sure we can redirect some functions like sprintf (else we do not have a definition of them at all)
    #define __USE_MINGW_ANSI_STDIO 0

    // missing in MINGW, but used by TCC tests
    #define index(s, c) strchr(s, c)
    #define rindex(s, c) strrchr(s, c)

    // make sure we do not use an unnecessary big FILE type (and be consistent with linux so it actually works)
    #define _FILE_DEFINED
    typedef void * FILE;

    // TODO: seems like we do not recognize that?
    #undef __unaligned
    #define __unaligned

    // TODO: not sure if we need those, for now exclude them (since else we'd need a bunch of __builtin definitions here)
    #define _X86INTRIN_H_INCLUDED
    // these seems to use something cznic/cc isn't able to handle
    #define __RPCASYNC_H__
    #define _OBJBASE_H_
    // these seem not necessary but cause some other problems (WINDOWS.h)
    #define __objidlbase_h__
    #define _COMBASEAPI_H_
    #define _OLEAUTO_H_
    #define __unknwn_h__
    #define __objidl_h__
    #define __oleidl_h__
    #define _OLE2_H_

    // prevent annoying _iob stuff (and better to do it directly)
    extern FILE stdin;
    extern FILE stdout;
    extern FILE stderr;
    #define _STDSTREAM_DEFINED

    // TODO: __builtin_fprintf(stderr, "%s:%i.%s STUB %s called!\n", __FILE__, __LINE__, __func__, #x), __builtin_abort(), 0)
    #define abort_stubbed(x) 0
    
    // maybe: `#define __CRT__NO_INLINE` to remove some unnecessary stuff
    // Implementing __readgsqword as macro also prevents an anonymous union access 
    // (which isn't supported in C99 actually WTF)
    #define __readfsdword(x) abort_stubbed("__readfsdword")
    #define __readgsqword(x) abort_stubbed("__readgsqword")

    // TODO: ? not relevant for SQLite since we have mutexes
    #define _mm_mfence() 
#endif

//TODO int128
#undef __SIZEOF_INT128__

#undef __ELF__

#endif				/* _PREDEFINED_H_ */
