#include <stdio.h>
#include <stdlib.h>
typedef int Elem;
typedef struct LinkedList{
	Elem data;
	struct LinkedList* next;
}LinkedList;
LinkedList* creatA() {
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
LinkedList* creatB() {
	int A[10] = { 20,19,18,17,16,15,14,13,10,9 }, i = 0;
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
LinkedList* sortAndLink(LinkedList* A, LinkedList* B) {
	LinkedList* C = (LinkedList*)malloc(sizeof(LinkedList)),*ptail=C,*pa=A->next,*pb=B->next;
	C->next = NULL;
	while (pa&&pb) {
		LinkedList* ptemp = (LinkedList*)malloc(sizeof(LinkedList));
		ptemp->next = NULL;
		ptail->next = ptemp;
		ptail = ptemp;
		if (pa->data <= pb->data) {
			ptemp->data = pa->data;
			pa = pa->next;
		}
		else{
			ptemp->data = pb->data;
			pb = pb->next;
		}
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
	LinkedList* A = creatA();
	LinkedList* B = creatB();
	LinkedList* C = sortAndLink(A, B), *p = C->next;
	while (p) {
		printf("%d\t", p->data);
		p = p->next;
	}
	return 0;
}