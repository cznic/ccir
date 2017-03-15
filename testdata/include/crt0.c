extern int main();

void _start(int argc, char **argv)
{
	__stdstreams[0] = __builtin_fopen("/dev/stdin", "r");
	__stdstreams[1] = __builtin_fopen("/dev/stdout", "w");
	__stdstreams[2] = __builtin_fopen("/dev/stderr", "w");

	__builtin_exit(((int (*)())(main)) (argc, argv));
}
