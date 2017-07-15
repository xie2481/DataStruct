#include <stdio.h>
#include <stdlib.h>
typedef int Elem;
typedef struct LinkedList {
	Elem data;
	struct LinkedList* next;
}LinkedList;
LinkedList* creatWithNoHead() {
	int A[10] = { 1,10,9,8,7,6,5,4,3,2 },i=0;
	LinkedList* L = NULL;
	for (i = 0; i < 10; i++) {
		if (L == NULL) {
			L = (LinkedList*)malloc(sizeof(LinkedList));
			L->data = A[i];
			L->next = NULL;
		}
		else {
			LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
			node->data = A[i];
			node->next = L->next;
			L->next = node;
		}
	}
	return L;
}
LinkedList* creatWithHead() {
	int A[10] = {10,9,8,7,6,5,4,3,2,1 }, i = 0;
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
void insertWithNoHead(LinkedList** L, int i, Elem b) {
	LinkedList* p = *L, *pre = NULL, *node = NULL;
	int j = 1;
	if (i < 1 || i>11)
		return;
	while (j < i&&p!=NULL) {
		pre = p;
		p = p->next;
		j++;
	}
	node = (LinkedList*)malloc(sizeof(LinkedList));
	node->data = b;
	if (pre == NULL) {
		node->next = p;
		*L = node;
	}
	else {
		pre->next = node;
		node->next = p;
	}
}
void insertWithHead(LinkedList* L, int i, Elem b) {
	LinkedList* p = L->next, *pre = L,*node=NULL;
	int j = 1;
	if (i < 1 || i>11)
		return;
	while (j < i&&p!=NULL) {
		pre = p;
		p = p->next;
		j++;
	}
	node = (LinkedList*)malloc(sizeof(LinkedList));
	node->data = b;
	pre->next = node;
	node->next = p;
}
int main() {
	LinkedList* la = creatWithNoHead(),*pa=NULL;
	LinkedList* lb = creatWithHead(), *pb = NULL;
	insertWithNoHead(&la, 11, 78);
	insertWithHead(lb, 11, 78);
	pa = la;
	pb = lb->next;
	while (pa) {
		printf("%d\t", pa->data);
		pa = pa->next;
	}
	printf("\n");
	while (pb) {
		printf("%d\t", pb->data);
		pb = pb->next;
	}
}