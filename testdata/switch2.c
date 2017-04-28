int main() {
	int i = 42;
	switch (i) {
	case 41:
		abort();
	case 42:
		i++;
	default:
		if (i == 43)
			exit(0);

		abort();
	case 43:
		abort();
	};
	abort();
}
