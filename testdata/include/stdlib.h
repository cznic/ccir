#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stddef.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define NULL ((void *)0)
#define exit(x) __builtin_exit(x)

void __builtin_abort(void);
void __builtin_exit(int status);

void abort(void)
{
	__builtin_abort();
}

#endif				/* _STDLIB_H_ */
