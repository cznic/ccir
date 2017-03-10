#ifndef _STDLIB_H_
#define _STDLIB_H_

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define NULL ((void *)0)

typedef __SIZE_TYPE__ size_t;
typedef __WCHAR_TYPE__ wchar_t;

int abs(int j);
void *calloc(size_t nmemb, size_t size);
void *malloc(size_t size);
void abort(void);
void exit(int status);
void free(void *ptr);

#endif				/* _STDLIB_H_ */
