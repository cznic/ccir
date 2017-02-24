#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>

#define NULL ((void *)0)

char *strcat(char *dest, const char *src);
char *strchr(const char *s, int c);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *strrchr(const char *s, int c);
int memcmp(const void *s1, const void *s2, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
size_t strlen(const char *s);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);

#endif				/* _STRING_H_ */
