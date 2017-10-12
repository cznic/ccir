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

// 99c: mismatched type, got **struct{weight uint64,tail *struct{},count int32}, expected *[2]*struct{weight uint64,tail *struct{},count int32}
// BoundaryPM:0x6: 	element         	&[int32], *[2]*struct{weight uint64,tail *struct{},count int32}	; 99c_issue5.c:12:19

// Node* (*lists)[2];
// cdecl: declare lists as pointer to array 2 of pointer to Node
//    Go: lists *[2]*Node

// Node**lists[2];
// cdecl: declare lists as array 2 of pointer to pointer to Node
//    Go: lists [2]**Node

// $ 99c -c 99c_issue5.c && 99dump 99c_issue5.o
// ir.Objects 99c_issue5.o:
// ...
// # [56]: *ir.FunctionDefinition { InternalLinkage BoundaryPM  func(*[2]*struct{weight uint64,tail *struct{},count int32},int32)  99c_issue5.c:11:1} [lists index]
// 0x00000		beginScope      															; 99c_issue5.c:11:54
// 0x00001		varDecl         	#0, lastcount, int32												;  99c_issue5.c:12:7
// 0x00002		variable        	&#0, *int32													; 99c_issue5.c:12:7
// 0x00003		argument        	#0, *[2]*struct{weight uint64,tail *struct{},count int32}							; 99c_issue5.c:12:19
// 0x00004		convert         	*[2]*struct{weight uint64,tail *struct{},count int32}, **struct{weight uint64,tail *struct{},count int32}	; 99c_issue5.c:12:19
// 0x00005		argument        	#1, int32													; 99c_issue5.c:12:25
// 0x00006		element         	&[int32], *[2]*struct{weight uint64,tail *struct{},count int32}							; 99c_issue5.c:12:19
// 0x00007		convert         	*[2]*struct{weight uint64,tail *struct{},count int32}, **struct{weight uint64,tail *struct{},count int32}	; 99c_issue5.c:12:19
// 0x00008		const           	0x1, int32													; 99c_issue5.c:12:32
// 0x00009		element         	[int32], **struct{weight uint64,tail *struct{},count int32}							; 99c_issue5.c:12:19
// 0x0000a		field           	#2, *struct{weight uint64,tail *struct{},count int32}								; 99c_issue5.c:12:36
// 0x0000b		store           	int32														; 99c_issue5.c:12:7
// 0x0000c		drop            	int32														; 99c_issue5.c:12:7
// 0x0000d		variable        	#0, int32													; 99c_issue5.c:13:7
// 0x0000e		const           	0xbc614e, int32													; 99c_issue5.c:13:20
// 0x0000f		neq             	int32														; 99c_issue5.c:13:17
// 0x00010		jz              	0														; 99c_issue5.c:13:3
// 0x00011		beginScope      															; 99c_issue5.c:13:30
// 0x00012		global          	&abort, *func()													;  99c_issue5.c:14:4
// 0x00013		arguments       															; -
// 0x00014		callfp          	0, *func()													; 99c_issue5.c:14:4
// 0x00015		endScope        															; 99c_issue5.c:15:3
// 0x00016	0:																		; 99c_issue5.c:13:3
// 0x00017		return          															; 99c_issue5.c:16:1
// 0x00018		endScope        															; 99c_issue5.c:16:1
// # [57]: *ir.DataDefinition { InternalLinkage BoundaryPM__func__0  [11]int8  -} "BoundaryPM"+0
// # [58]: *ir.FunctionDefinition { ExternalLinkage main  func()int32  99c_issue5.c:18:1} []
// 0x00000		result          	&#0, *int32													; 99c_issue5.c:18:12
// 0x00001		const           	0x0, int32													; 99c_issue5.c:18:12
// 0x00002		store           	int32														; 99c_issue5.c:18:12
// 0x00003		drop            	int32														; 99c_issue5.c:18:12
// 0x00004		beginScope      															; 99c_issue5.c:18:12
// 0x00005		varDecl         	#0, n, struct{weight uint64,tail *struct{},count int32}								; XNode 99c_issue5.c:19:7
// 0x00006		variable        	&#0, *struct{weight uint64,tail *struct{},count int32}								; 99c_issue5.c:20:2
// 0x00007		field           	&#2, *struct{weight uint64,tail *struct{},count int32}								; 99c_issue5.c:20:2
// 0x00008		const           	0xbc614e, int32													; 99c_issue5.c:20:12
// 0x00009		store           	int32														; 99c_issue5.c:20:10
// 0x0000a		drop            	int32														; 99c_issue5.c:20:2
// 0x0000b		varDecl         	#1, a, [2]*struct{weight uint64,tail *struct{},count int32}							; [2]*XNode 99c_issue5.c:21:7
// 0x0000c		variable        	&#1, *[2]*struct{weight uint64,tail *struct{},count int32}							; 99c_issue5.c:22:2
// 0x0000d		convert         	*[2]*struct{weight uint64,tail *struct{},count int32}, **struct{weight uint64,tail *struct{},count int32}	; 99c_issue5.c:22:2
// 0x0000e		const           	0x1, int32													; 99c_issue5.c:22:4
// 0x0000f		element         	&[int32], **struct{weight uint64,tail *struct{},count int32}							; 99c_issue5.c:22:2
// 0x00010		variable        	&#0, *struct{weight uint64,tail *struct{},count int32}								; 99c_issue5.c:22:10
// 0x00011		store           	*struct{weight uint64,tail *struct{},count int32}								; 99c_issue5.c:22:7
// 0x00012		drop            	*struct{weight uint64,tail *struct{},count int32}								; 99c_issue5.c:22:2
// 0x00013		global          	&BoundaryPM, *func(*[2]*struct{weight uint64,tail *struct{},count int32},int32)					;  99c_issue5.c:23:2
// 0x00014		arguments       															; 99c_issue5.c:23:13
// 0x00015		variable        	&#1, *[2]*struct{weight uint64,tail *struct{},count int32}							; 99c_issue5.c:23:14
// 0x00016		const           	0x0, int32													; 99c_issue5.c:23:17
// 0x00017		callfp          	2, *func(*[2]*struct{weight uint64,tail *struct{},count int32},int32)						; 99c_issue5.c:23:2
// 0x00018		return          															; 99c_issue5.c:24:1
// 0x00019		endScope        															; 99c_issue5.c:24:1
// # [59]: *ir.DataDefinition { InternalLinkage main__func__0  [5]int8  -} "main"+0
// $
