#ifndef _STDDEF_H_
#define _STDDEF_H_

#define NULL ((void *)0)

// https://en.wikipedia.org/wiki/Offsetof
#define offsetof(st, m) ((size_t)(&((st *)0)->m))

typedef unsigned long size_t;
typedef long ptrdiff_t;

#endif				/* _STDDEF_H_ */
