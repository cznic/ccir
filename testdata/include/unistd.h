#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);

#endif				/* _UNISTD_H_ */
