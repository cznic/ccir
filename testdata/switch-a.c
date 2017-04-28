int main() {
	int i = 42;
	switch (i) {
	case 41:
		abort();
	case 42:
		exit(0);
	case 43:
		abort();
	}
	abort();
}
