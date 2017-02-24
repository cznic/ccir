#ifndef _STDIO_H_
#define _STDIO_H_

#include <stddef.h>

#define EOF -1
#define NULL ((void *)0)
#define getc(x) fgetc(x)
#define stderr (__stdstreams[2])
#define stdin (__stdstreams[0])
#define stdout (__stdstreams[1])

typedef struct {
	int _;
} FILE;

FILE *__stdstreams[3];

FILE *fopen(const char *path, const char *mode);
char *fgets(char *s, int size, FILE * stream);
int fclose(FILE * stream);
int fgetc(FILE * stream);
int fprintf(FILE * stream, const char *format, ...);
int printf(const char *format, ...);
int sprintf(char *str, const char *format, ...);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE * stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE * stream);

#endif				/* _STDIO_H_ */
