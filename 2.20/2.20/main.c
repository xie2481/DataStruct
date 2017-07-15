/*算法的复杂度显然和链表长度有关，所以为O(n)*/
#include <stdio.h>
#include <stdlib.h>
typedef int Elem;
typedef struct LinkedList {
	Elem data;
	struct LinkedList* next;
}LinkedList;
LinkedList* creat() {
	int A[10] = { 1,1,1,1,1,1,1,1,1,1 }, i = 0;
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
void deleteSameElem(LinkedList* L) {
	LinkedList* p =NULL, *pre = L->next;
	if (pre->next != NULL)
		p = pre->next;
	else
		return;
	while (p) {
		if (p->data == pre->data) {
			pre->next = p->next;
			free(p);
			p = pre->next;
		}
		else {
			pre = pre->next;
			p = p->next;
		}
	}
}
int main() {
	LinkedList* L = creat(), *pa = NULL;
	deleteSameElem(L);
	pa = L->next;
	while (pa) {
		printf("%d\t", pa->data);
		pa = pa->next;
	}
	printf("\n");
	return 0;
}