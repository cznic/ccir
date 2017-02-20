#ifndef _LIMITS_H_
#define _LIMITS_H_

#if defined __MODEL_32__
#define ULONG_MAX 4294967295ul
#elif defined __MODEL_64__
#define ULONG_MAX 18446744073709551615ull
#else
#error
#endif

#define ULONG_LONG_MAX 18446744073709551615ull

#endif				/* _LIMITS_H_ */
