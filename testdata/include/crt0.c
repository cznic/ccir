#include <builtin.h>
#include <stdio.h>
#include <stdlib.h>

extern int main();

void _start(int argc, char **argv)
{
	__stdstreams[0] = fopen("/dev/stdin", "r");
	__stdstreams[1] = fopen("/dev/stdout", "w");
	__stdstreams[2] = fopen("/dev/stderr", "w");

	exit(((int (*)(int, char **, ...))(main)) (argc, argv));
}
