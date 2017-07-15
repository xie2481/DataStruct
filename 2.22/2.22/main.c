#include <stdio.h>
#include <stdlib.h>
typedef int Elem;
typedef struct LinkedList {
	Elem data;
	struct LinkedList* next;
}LinkedList;
LinkedList* creat() {
	int A[10] = { 10,9,8,7,6,5,4,3,2,1 }, i = 0;
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
LinkedList* traverse(LinkedList* L) {
	LinkedList* phead = L,*p=L->next;
	phead->next = NULL;
	while (p) {
		LinkedList* ptemp = p;
		p = p->next;
		ptemp->next = phead->next;
		phead->next = ptemp;
	}
	L = phead;
	return L;
}
int main() {
	LinkedList* L = creat(),*p=NULL;
	L=traverse(L);
	p = L->next;
	while (p) {
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");
	return 0;
}