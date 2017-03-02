#ifndef _STDDEF_H_
#define _STDDEF_H_

#define NULL ((void *)0)

// https://en.wikipedia.org/wiki/Offsetof
#define offsetof(st, m) ((size_t)(&((st *)0)->m))

typedef int wchar_t;
typedef long ptrdiff_t;
typedef unsigned long size_t;

#endif				/* _STDDEF_H_ */
