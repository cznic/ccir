//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

int main();

void *stdin, *stdout, *stderr;

void _start(int argc, char **argv)
{
	stdin = fopen("/dev/stdin", "r");
	stdout = fopen("/dev/stdout", "w");
	stderr = fopen("/dev/stderr", "w");

	exit(((int (*)())main) (argc, argv));
}
