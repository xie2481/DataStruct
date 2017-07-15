/*算法复杂度只与链表的长度有关，故为o(n)*/
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
void deleteBetweenAToB(LinkedList* L, Elem mink, Elem maxk) {
	LinkedList* p = L->next, *pre = L;
	while (p) {
		if (p->data >= maxk)
			break;
		else if (p->data > mink&&p->data < maxk) {
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
	deleteBetweenAToB(L, 1, 11);
	pa = L->next;
	while (pa) {
		printf("%d\t", pa->data);
		pa = pa->next;
	}
	printf("\n");
	return 0;
}