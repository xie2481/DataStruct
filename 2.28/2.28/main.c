#include <stdio.h>
#include <stdlib.h>
#define MAXV 10
typedef int Elem;
typedef struct LinkedList {
	Elem data;
	struct LinkedList* next;
}LinkedList;
LinkedList* creat(int* A, int length) {
	LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList)),*ptail=L;
	int i = 0;
	L->next = NULL;
	for (i = 0; i < length; i++) {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->data = A[i];
		node->next = NULL;
		ptail->next = node;
		ptail = node;
	}
	return L;
}
LinkedList* getSort(LinkedList* La, LinkedList* Lb) {
	LinkedList* pa = La->next, *pb = Lb->next;
	LinkedList* preA = La, *preB = Lb;
	LinkedList* Lc = (LinkedList*)malloc(sizeof(LinkedList)),*ptail=Lc;
	Lc->next = NULL;
	int isTrue = 0;
	while (pa) {
		isTrue = 0;
		while (pb) {
			if (pa->data < pb->data) {
				isTrue = 0;
				break;
			}
			if (pa->data == pb->data) {
				isTrue = 1;
				break;
			}
			pb = pb->next;
			preB = preB->next;
		}
		if (isTrue == 0) {
			preA->next = pa->next;
			free(pa);
			pa = preA->next;
		}
		else {
			preA->next = pa->next;
			pa->next = NULL;
			if (ptail->data != pa->data) {
				ptail->next = pa;
				ptail = pa;
			}
			else {
				free(pa);
			}
			pa = preA->next;
		}
		preB = Lb;
		pb = preB->next;
	}
	return Lc;
}
int main() {
	int A[MAXV] = { 1,2,3,3,5,6,7,8,9,10 };
	int B[MAXV] = { 3,3,5,7,8,9,10,11,12,13 };
	LinkedList* La = creat(A, MAXV);
	LinkedList* Lb = creat(B, MAXV);
	LinkedList* Lc = getSort(La, Lb);
	LinkedList* p = Lc->next;
	while (p) {
		printf("%d\t", p->data);
		p = p->next;
	}
}