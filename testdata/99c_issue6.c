#include <stdlib.h>

typedef struct Node Node;

struct Node {
  size_t weight;
  Node* tail;
  int count;
};

void foo(void*) {}

int main() { // https://github.com/cznic/99c/issues/5
  Node* (*lists)[2];
  lists = (Node* (*)[2])malloc(42 * sizeof(*lists));
  foo(lists);
  foo(lists[0]);
  __builtin_printf("ok\n");
}
