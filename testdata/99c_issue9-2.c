typedef int ft();

int foo()
{
	return 42;
}

int bar(ft f)
{
	return f();
}

int main()
{
	__builtin_printf("%i\n", bar(foo));
}
