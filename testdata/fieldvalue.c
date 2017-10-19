typedef struct t {
	int f;
} t;

typedef struct u {
	t *g;
} u;

t a;

u foo()
{
	a.f = 12345678;
	u b;
	b.g = &a;
	return b;
}

int main()
{
	t *a = foo().g;
	__builtin_printf("%i\n", a->f);
}
