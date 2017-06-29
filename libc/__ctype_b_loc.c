// Copyright © 2005-2014 Rich Felker, et al. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE-MUSL file.

// Modification Copyright 2017 The CCIR Authors.

// +build ignore

#if __BYTE_ORDER == __ORDER_BIG_ENDIAN__
#define X(x) x
#else
#define X(x) (((x)/256 | (x)*256) % 65536)
#endif

static const unsigned short table[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	X(0x200), X(0x200), X(0x200), X(0x200), X(0x200), X(0x200), X(0x200), X(0x200),
	X(0x200), X(0x320), X(0x220), X(0x220), X(0x220), X(0x220), X(0x200), X(0x200),
	X(0x200), X(0x200), X(0x200), X(0x200), X(0x200), X(0x200), X(0x200), X(0x200),
	X(0x200), X(0x200), X(0x200), X(0x200), X(0x200), X(0x200), X(0x200), X(0x200),
	X(0x160), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0),
	X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0),
	X(0x8d8), X(0x8d8), X(0x8d8), X(0x8d8), X(0x8d8), X(0x8d8), X(0x8d8), X(0x8d8),
	X(0x8d8), X(0x8d8), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0),
	X(0x4c0), X(0x8d5), X(0x8d5), X(0x8d5), X(0x8d5), X(0x8d5), X(0x8d5), X(0x8c5),
	X(0x8c5), X(0x8c5), X(0x8c5), X(0x8c5), X(0x8c5), X(0x8c5), X(0x8c5), X(0x8c5),
	X(0x8c5), X(0x8c5), X(0x8c5), X(0x8c5), X(0x8c5), X(0x8c5), X(0x8c5), X(0x8c5),
	X(0x8c5), X(0x8c5), X(0x8c5), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0),
	X(0x4c0), X(0x8d6), X(0x8d6), X(0x8d6), X(0x8d6), X(0x8d6), X(0x8d6), X(0x8c6),
	X(0x8c6), X(0x8c6), X(0x8c6), X(0x8c6), X(0x8c6), X(0x8c6), X(0x8c6), X(0x8c6),
	X(0x8c6), X(0x8c6), X(0x8c6), X(0x8c6), X(0x8c6), X(0x8c6), X(0x8c6), X(0x8c6),
	X(0x8c6), X(0x8c6), X(0x8c6), X(0x4c0), X(0x4c0), X(0x4c0), X(0x4c0), X(0x200),
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

static unsigned short *ptable;

const unsigned short **__ctype_b_loc(void)
{
	ptable = table + 128;
	return (void *)&ptable;
}
