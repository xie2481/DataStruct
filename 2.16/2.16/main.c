#include <stdio.h>
#include <stdlib.h>
typedef int Elem;
typedef struct LinkedList {
	Elem data;
	struct LinkedList* next;
}LinkedList;
LinkedList* creat() {
	LinkedList* L = NULL;
	int A[10] = { 1,10,9,8,7,6,5,4,3,2 }, i = 0;
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
int deleteAndInsertSub(LinkedList* la, LinkedList* lb, int i, int j, int len) {
	LinkedList* p=NULL, *q=NULL, *s=NULL;
	int k = 0;
	if (i < 0 || j < 0 || len < 0)
		return 1;
	p = la;
	k = 1;
	while (k < i) {
		p = p->next;
		k++;
	}
	q = p;
	while (k <len+i-1) {
		q = q->next;
		k++;
	}
	s = lb;
	k = 1;
	while (k < j-1) {
		s = s->next;
		k++;
	}
	q->next = s->next;
	s->next = p;
}
int main() {
	LinkedList* la = creat();
	LinkedList* lb = creat();
	deleteAndInsertSub(la, lb, 5, 2, 3);
	LinkedList* pa = la;
	LinkedList* pb = lb;
	/*while (pa) {
		printf("%d\t", pa->data);
		pa = pa->next;
	}*/
	printf("\n");
	while (pb) {
		printf("%d\t", pb->data);
		pb = pb->next;
	}
	printf("\n");
	return 0;
}