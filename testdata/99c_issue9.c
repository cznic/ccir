int foo()
{
	return 42;
}

int bar(int (*f) ())
{
	return f();
}

int main()
{
	__builtin_printf("%i\n", bar(foo));
}
