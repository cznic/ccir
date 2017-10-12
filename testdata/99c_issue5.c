#include <stdio.h>

typedef struct Node Node;

struct Node {
  size_t weight;
  Node* tail;
  int count;
};

void foo(Node*) {}

static void BoundaryPM(Node* (*lists)[2], int index) {
  if (index) {
	  return;
  }

  int lastcount = lists[index][1]->count;
  if (lastcount != 12345678) {
	  __builtin_abort();
  }
  BoundaryPM(lists, 1);
}

int main() { // https://github.com/cznic/99c/issues/5
	Node n;
	n.count = 12345678;
	Node *a[2];
	a[1] = &n;
	BoundaryPM(&a, 0);
	printf("ok\n");
}
