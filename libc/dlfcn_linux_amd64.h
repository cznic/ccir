// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

extern void *dlopen(const char *__file, int __mode);
extern int dlclose(void *__handle);
extern void *dlsym(void *__handle, const char *__name);
extern char *dlerror(void);

// /usr/include/x86_64-linux-gnu/bits/dlfcn.h 

#define RTLD_DEEPBIND (8)
#define RTLD_BINDING_MASK (3)
#define RTLD_NODELETE (4096)
#define RTLD_GLOBAL (256)
#define RTLD_LAZY (1)
#define RTLD_NOLOAD (4)

// /usr/include/dlfcn.h 

#define _DLFCN_H (1)

// /usr/include/x86_64-linux-gnu/bits/dlfcn.h 

#define RTLD_LOCAL (0)
#define RTLD_NOW (2)
