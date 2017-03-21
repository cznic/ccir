#ifndef _FCNTL_H_
#define _FCNTL_H_

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int open(const char *pathname, int flags, ...);

#endif				/* _FCNTL_H_ */
