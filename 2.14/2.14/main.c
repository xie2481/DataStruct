//试写一算法在带头节点的单链表结构上实现线性表操作Length(L)
#include <stdio.h>
#include <stdlib.h>
typedef int Elem;
typedef struct LinkedList {
	Elem data;
	struct LinkedList* next;
}LinkedList;
LinkedList* creat() {
	int A[10] = { 10,9,8,7,6,5,4,3,2,1 };
	int i = 0;
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
int Length(LinkedList* L) {
	LinkedList* p = L->next;
	int length = 0;
	while (p) {
		length++;
		p = p->next;
	}
	return length;
}
int main() {
	LinkedList* L = creat();
	printf("%d\n", Length(L));
	return 0;
}