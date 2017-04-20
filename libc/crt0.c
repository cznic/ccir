//  Copyright 2017 The CCIR Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style
//  license that can be found in the LICENSE file.

// +build ignore

int main();

__FILE_TYPE__ __stdfiles[3];
void *stdin = &__stdfiles[0], *stdout = &__stdfiles[1], *stderr = &__stdfiles[2];

void _start(int argc, char **argv)
{
	__register_stdfiles(stdin, stdout, stderr);
	exit(((int (*)())main) (argc, argv));
}
