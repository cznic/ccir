#ifndef _MATH_H_
#define _MATH_H_

#define acos(x) __builtin_acos(x)
#define asin(x) __builtin_asin(x)
#define atan(x) __builtin_atan(x)
#define ceil(x) __builtin_ceil(x)
#define cos(x) __builtin_cos(x)
#define cosh(x) __builtin_cosh(x)
#define exp(x) __builtin_exp(x)
#define fabs(x) __builtin_fabs(x)
#define floor(x) __builtin_floor(x)
#define log(x) __builtin_log(x)
#define log10(x) __builtin_log10(x)
#define pow(x, y) __builtin_pow(x, y)
#define round(x) __builtin_round(x)
#define sin(x) __builtin_sin(x)
#define sinh(x) __builtin_sinh(x)
#define sqrt(x) __builtin_sqrt(x)
#define tan(x) __builtin_tan(x)
#define tanh(x) __builtin_tanh(x)

double __builtin_acos(double x);
double __builtin_asin(double x);
double __builtin_atan(double x);
double __builtin_ceil(double x);
double __builtin_cos(double x);
double __builtin_cosh(double x);
double __builtin_exp(double x);
double __builtin_fabs(double x);
double __builtin_floor(double x);
double __builtin_log(double x);
double __builtin_log10(double x);
double __builtin_pow(double x, double y);
double __builtin_round(double x);
double __builtin_sin(double x);
double __builtin_sinh(double x);
double __builtin_sqrt(double x);
double __builtin_tan(double x);
double __builtin_tanh(double x);

#endif				/* _MATH_H_ */
