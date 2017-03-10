#ifndef _STDARG_H_
#define _STDARG_H_

#define va_arg(ap, type) *(type*)(ap -= __roundup(sizeof(type), __stackAlign))
#define va_end(ap) ap = 0
#define va_start(ap, arg) ap = (va_list)(&arg)

typedef __builtin_va_list va_list;

#endif				/* _STDARG_H_ */
