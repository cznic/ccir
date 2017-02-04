#include <stdlib.h>

int main();

void _start(int argc, char **argv)
{
	exit(((int (*)(int, char **, ...))(main)) (argc, argv));
}
