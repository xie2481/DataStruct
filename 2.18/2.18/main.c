#include <stdio.h>
#include <stdlib.h>
typedef int Elem;
typedef struct LinkedList {
	Elem data;
	struct LinkedList* next;
}LinkedList;
LinkedList* creatWithNoHead() {
	int A[10] = { 1,10,9,8,7,6,5,4,3,2 }, i = 0;
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
void deleteWithHead(LinkedList* L, int i) {
	LinkedList* p = L->next, *pre = L;
	int j = 1;
	if (i < 1 || i>10)
		return;
	while (j < i) {
		pre = pre->next;
		p = p->next;
		j++;
	}
	pre->next = p->next;
	free(p);
}
void deleteWithNoHead(LinkedList** L, int i) {
	LinkedList* p = *L, *pre = NULL;
	int j = 1;
	if (i < 1 || i>10)
		return;
	while (j < i) {
		pre = p;
		p = p->next;
		j++;
	}
	if (pre == NULL) {
		*L = (*L)->next;
	}
	else {
		pre->next = p->next;
	}
	free(p);
}
int main() {
	LinkedList* la = creatWithHead(), *pa = NULL;
	LinkedList* lb = creatWithNoHead(), *pb = NULL;
	deleteWithHead(la, 11);
	deleteWithNoHead(&lb, 11);
	pa = la->next;
	pb = lb;
	while (pa) {
		printf("%d\t", pa->data);
		pa = pa->next;
	}
	printf("\n");
	while (pb) {
		printf("%d\t", pb->data);
		pb = pb->next;
	}
	printf("\n");
	return 0;
}