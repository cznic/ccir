//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _MATH_H_
#define _MATH_H_

#include <float.h>

//TODO
double acos(double x);
double asin(double x);
double atan(double x);
double ceil(double x);
double copysign(double x, double y);
double cos(double x);
double cosh(double x);
double exp(double x);
double fabs(double x);
double floor(double x);
double log(double x);
double log10(double x);
double pow(double x, double y);
double round(double x);
double sin(double x);
double sinh(double x);
double sqrt(double x);
double tan(double x);
double tanh(double x);
int isinf(double x);
int isinff(float x);
int isinfl(long double x);

#include __header(math)

#endif				/* _MATH_H_ */
