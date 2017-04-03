//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

extern int main();

void _start(int argc, char **argv)
{
	__stdstreams[0] = __builtin_fopen("/dev/stdin", "r");
	__stdstreams[1] = __builtin_fopen("/dev/stdout", "w");
	__stdstreams[2] = __builtin_fopen("/dev/stderr", "w");

	__builtin_exit(((int (*)())(main)) (argc, argv));
}
