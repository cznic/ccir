#ifndef _STDDEF_H_
#define _STDDEF_H_

#define NULL ((void *)0)

// https://en.wikipedia.org/wiki/Offsetof
#define offsetof(st, m) ((size_t)(&((st *)0)->m))
#define ptrdiff_t __PTRDIFF_TYPE__
#define size_t __SIZE_TYPE__
#define wchar_t __WCHAR_TYPE__

#endif				/* _STDDEF_H_ */
