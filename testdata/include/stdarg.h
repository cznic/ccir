#ifndef _STDARG_H_
#define _STDARG_H_

#if defined __MODEL_32__
#define __stackAlign 4
#elif defined __MODEL_64__
#define __stackAlign 8
#else
#error
#endif

#define __roundup(n, mod) ((n + mod - 1) & ~(mod - 1))
#define va_arg(ap, type) *(type*)(ap -= __roundup(sizeof(type), __stackAlign))
#define va_start(ap, arg) ap = (char*)(&arg)
#define va_end(ap) ap = 0

typedef char *va_list;

#endif				/* _STDARG_H_ */
