// Copyright © 2005-2014 Rich Felker, et al. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE-MUSL file.

// +build ignore

#include <stdlib.h>
#include <ctype.h>

int atoi(const char *s)
{
	int n = 0, neg = 0;
	while (isspace(*s))
		s++;
	switch (*s) {
	case '-':
		neg = 1;
	case '+':
		s++;
	}
	/* Compute n as a negative number to avoid overflow on INT_MIN */
	while (isdigit(*s))
		n = 10 * n - (*s++ - '0');
	return neg ? n : -n;
}
