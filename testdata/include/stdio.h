#ifndef _STDIO_H_
#define _STDIO_H_

#include <stddef.h>

#define EOF -1
#define NULL ((void *)0)
#define fclose(x) __builtin_fclose(x)
#define fgetc(x) __builtin_fgetc(x)
#define fgets(x, y, z) __builtin_fgets(x, y, z)
#define fopen(x, y) __builtin_fopen(x, y)
#define fprintf(x, y...) __builtin_fprintf(x, y)
#define fread(x, y, z, t) __builtin_fread(x, y, z, t)
#define fwrite(x, y, z, t) __builtin_fwrite(x, y, z, t)
#define getc(x) __builtin_fgetc(x)
#define printf(x...) __builtin_printf(x)
#define sprintf(x, y...) __builtin_sprintf(x, y)
#define stderr (__stdstreams[2])
#define stdin (__stdstreams[0])
#define stdout (__stdstreams[1])

typedef struct {
	int dummy;
} FILE;

FILE *__stdstreams[3];

FILE *__builtin_fopen(const char *path, const char *mode);
char *__builtin_fgets(char *s, int size, FILE * stream);
int __builtin_fclose(FILE * stream);
int __builtin_fgetc(FILE * stream);
int __builtin_fprintf(FILE * stream, const char *format, ...);
int __builtin_printf(const char *format, ...);
int __builtin_sprintf(char *str, const char *format, ...);
size_t __builtin_fread(void *ptr, size_t size, size_t nmemb, FILE * stream);
size_t __builtin_fwrite(const void *ptr, size_t size, size_t nmemb,
			FILE * stream);

#endif				/* _STDIO_H_ */
