//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _STDIO_H_
#define _STDIO_H_

#define EOF -1
#define NULL ((void *)0)
#define getc(x) fgetc(x)
#define stderr (__stdstreams[2])
#define stdin (__stdstreams[0])
#define stdout (__stdstreams[1])

typedef __FILE_TYPE__ FILE;
typedef __SIZE_TYPE__ size_t;
typedef __builtin_va_list va_list;

FILE *fopen(const char *path, const char *mode);
char *fgets(char *s, int size, FILE * stream);
int fclose(FILE * stream);
int fgetc(FILE * stream);
int fprintf(FILE * stream, const char *format, ...);
int printf(const char *format, ...);
int sprintf(char *str, const char *format, ...);
int vfprintf(FILE * stream, const char *format, va_list ap);
int vprintf(const char *format, va_list ap);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE * stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE * stream);

#endif				/* _STDIO_H_ */
