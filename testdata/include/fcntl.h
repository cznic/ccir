#ifndef _FCNTL_H_
#define _FCNTL_H_

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define O_WRONLY	0x0001
#define O_NOFOLLOW      0x8000

int open(const char *pathname, int flags, ...);

#endif				/* _FCNTL_H_ */
