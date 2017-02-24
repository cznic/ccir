#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stddef.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define NULL ((void *)0)

void abort(void);
void exit(int status);

#endif				/* _STDLIB_H_ */
