//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _CTYPE_H_
#define _CTYPE_H_

#include __header(ctype)

#ifdef _WIN32
// TODO: I doubt the windows stuff works exactly as the linux stuff here...
//       This might cause some trouble (windows e.g. additionally respects the locale...)
#define _IScntrl _CONTROL
#define _ISspace _SPACE
#define _ISblank _BLANK
#define _ISprint _BLANK | _PUNCT | _ALPHA | _DIGIT
#define _ISgraph _PUNCT | _ALPHA | _DIGIT
#define _ISpunct _PUNCT
#define _ISdigit _DIGIT
#define _ISxdigit _HEX
#define _ISalnum _ALPHA | _DIGIT
#define _ISupper _UPPER
#define _ISlower _LOWER
#define  _ISalpha _ALPHA
#endif

#include "__ctype_b_loc_tab.c"

static unsigned short *__ctype_b_loc_tablep = &__ctype_b_table[128];

unsigned short **__ctype_b_loc(void)
{
	return &__ctype_b_loc_tablep;
}

#endif				/* _CTYPE_H_ */
