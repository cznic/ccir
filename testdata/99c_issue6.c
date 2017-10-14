#include <stdlib.h>

typedef struct Node Node;

struct Node {
	size_t weight;
	Node *tail;
	int count;
};

typedef struct NodePool {
	Node *next;
} NodePool;

void foo(void *)
{
}

static void BoundaryPM(Node * (*lists)[2])
{
	foo(lists);
	foo(lists[0]);		//TODO
	foo(lists[0][0]);	//TODO
}

int main()
{				// https://github.com/cznic/99c/issues/6
	Node *(*lists)[2];
	lists = (Node * (*)[2]) malloc(42 * sizeof(*lists));
	foo(lists);
	foo(lists[0]);
	foo(lists[0][0]);
	__builtin_printf("ok\n");
}
