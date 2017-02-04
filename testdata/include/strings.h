#ifndef _STRINGS_H_
#define _STRINGS_H_

#include <string.h>

#define index(a, b) __builtin_strchr(a, b)
#define rindex(a, b) __builtin_strrchr(a, b)

#endif				/* _STRINGS_H_ */
