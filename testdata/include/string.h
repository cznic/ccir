#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>

#define NULL ((void *)0)
#define memcmp(a, b, c) __builtin_memcmp(a, b, c)
#define memcpy(a, b, c) __builtin_memcpy(a, b, c)
#define memset(a, b, c) __builtin_memset(a, b, c)
#define strcat(a, b) __builtin_strcat(a, b)
#define strchr(a, b) __builtin_strchr(a, b)
#define strcmp(a, b) __builtin_strcmp(a, b)
#define strcpy(a, b) __builtin_strcpy(a, b)
#define strlen(a) __builtin_strlen(a)
#define strncmp(a, b, c) __builtin_strncmp(a, b, c)
#define strncpy(a, b, c) __builtin_strncpy(a, b, c)
#define strrchr(a, b) __builtin_strrchr(a, b)

char *__builtin_strcat(char *dest, const char *src);
char *__builtin_strchr(const char *s, int c);
char *__builtin_strcpy(char *dest, const char *src);
char *__builtin_strncpy(char *dest, const char *src, size_t n);
char *__builtin_strrchr(const char *s, int c);
int __builtin_memcmp(const void *s1, const void *s2, size_t n);
int __builtin_strcmp(const char *s1, const char *s2);
int __builtin_strncmp(const char *s1, const char *s2, size_t n);
size_t __builtin_strlen(const char *s);
void *__builtin_memcpy(void *dest, const void *src, size_t n);
void *__builtin_memset(void *s, int c, size_t n);

#endif				/* _STRING_H_ */
