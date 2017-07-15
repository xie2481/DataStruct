#include <stdio.h>
#include <stdlib.h>
typedef int Elem;
typedef struct LinkedList {
	Elem data;
	struct LinekdList* next;
}LinkedList;
LinkedList* creat() {
	int A[10] = { 10,9,8,7,6,5,4,3,2,1 },i=0;
	LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList));
	L->next = NULL;
	for (i = 0; i < 10; i++) {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->data = A[i];
		node->next = L->next;
		L->next = node;
	}
	return L;
}
LinkedList* creat1() {
	int A[11] = { 11,10,9,8,7,6,5,4,3,2,1 }, i = 0;
	LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList));
	L->next = NULL;
	for (i = 0; i < 11; i++) {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->data = A[i];
		node->next = L->next;
		L->next = node;
	}
	return L;
}
LinkedList* link(LinkedList* A, LinkedList* B) {
	LinkedList* C = (LinkedList*)malloc(sizeof(LinkedList)),*ptail=C,*pa=A->next,*pb=B->next;
	C->next = NULL;
	while (pa&&pb) {
		LinkedList* ptemp = (LinkedList*)malloc(sizeof(LinkedList));
		ptemp->data = pa->data;
		ptemp->next = NULL;
		ptail->next = ptemp;
		ptail = ptemp;
		ptemp = (LinkedList*)malloc(sizeof(LinkedList));
		ptemp->data = pb->data;
		ptemp->next = NULL;
		ptail->next = ptemp;
		ptail = ptemp;
		pa = pa->next;
		pb = pb->next;
	}
	if (pa != NULL) {
		ptail->next = pa;
	} 
	if (pb != NULL) {
		ptail->next = pb;
	}
	return C;
}
int main() {
	LinkedList* A = creat1();
	LinkedList* B = creat();
	LinkedList* C = link(A, B),*pc=C->next;
	while (pc) {
		printf("%d\t", pc->data);
		pc = pc->next;
	}
	return 0;
}