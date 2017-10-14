//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

#ifndef _CTYPE_H_
#define _CTYPE_H_

#include __header(ctype)

#include "__ctype_b_loc_tab.c"

static unsigned short *__ctype_b_loc_tablep = &__ctype_b_table[128];

unsigned short **__ctype_b_loc(void)
{
	return &__ctype_b_loc_tablep;
}

#endif				/* _CTYPE_H_ */
