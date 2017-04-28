int main() {
	int i = 42;
	switch (i) {
	default:
		exit(0);
	case 41:
		abort();
	case 43:
		abort();
	};
	abort();
}
