// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

#define _SYS_MMAN_H (1)
typedef __off_t off_t;
#define __off_t_defined
typedef __mode_t mode_t;
#define __mode_t_defined
#define MAP_FAILED ( ( void * ) - 1 )
extern void *mmap(void *__addr, size_t __len, int __prot, int __flags, int __fd, __off_t __offset);
extern int munmap(void *__addr, size_t __len);
extern int mprotect(void *__addr, size_t __len, int __prot);
extern int msync(void *__addr, size_t __len, int __flags);
extern int mlock(void *__addr, size_t __len);
extern int munlock(void *__addr, size_t __len);
extern int mlockall(int __flags);
extern int munlockall(void);
extern int shm_open(char *__name, int __oflag, mode_t __mode);
extern int shm_unlink(char *__name);
#define PROT_READ (1)
#define PROT_WRITE (2)
#define PROT_EXEC (4)
#define PROT_NONE (0)
#define PROT_GROWSDOWN (16777216)
#define PROT_GROWSUP (33554432)
#define MAP_SHARED (1)
#define MAP_PRIVATE (2)
#define MAP_FIXED (16)
#define MS_ASYNC (1)
#define MS_SYNC (4)
#define MS_INVALIDATE (2)
#define MCL_CURRENT (1)
#define MCL_FUTURE (2)
#define MCL_ONFAULT (4)
