//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

char *getcwd(char *buf, size_t size);
int access(const char *pathname, int mode);
int chown(const char *pathname, uid_t owner, gid_t group);
int close(int fd);
int fchown(int fd, uid_t owner, gid_t group);
int ftruncate(int fd, off_t length);
int lchown(const char *pathname, uid_t owner, gid_t group);
int rmdir(const char *pathname);
int truncate(const char *path, off_t length);
int unlink(const char *pathname);
ssize_t read(int fd, void *buf, size_t count);
ssize_t readlink(const char *pathname, char *buf, size_t bufsiz);
ssize_t write(int fd, const void *buf, size_t count);
uid_t geteuid(void);
uid_t getuid(void);

#endif				/* _UNISTD_H_ */
