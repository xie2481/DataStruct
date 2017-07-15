#include <stdio.h>
#include <stdlib.h>
#define MAXV 10
typedef int Elem;
typedef struct LinkedList {
	Elem data;
	struct LinkedList* next;
}LinkedList;
LinkedList* creat(int* A,int length) {
	LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList));
	L->next = NULL;
	length--;
	while (length >= 0) {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->data = A[length--];
		node->next = L->next;
		L->next = node;
	}
	return L;
}
LinkedList* getSort(LinkedList* A, LinkedList* B) {
	LinkedList* C = (LinkedList*)malloc(sizeof(LinkedList)),*ptail=C,*pa=A->next,*pb=B->next;
	C->next = NULL;
	while (pa) {
		pb = B->next;
		while (pb) {
			if (pa->data == pb->data) {
				LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
				node->data = pa->data;
				node->next = NULL;
				ptail->next = node;
				ptail = node;
			} 
			if (pa->data < pb->data)
				break;
			pb = pb->next;
		}
		pa = pa->next;
	}
	return C;
}
int main() {
	int A[MAXV] = { 1,2,3,4,5,6,7,8,9,10 };
	int B[MAXV] = { 10,11,12,13,14,15,16,17,18,19 };
	LinkedList* La = creat(A, MAXV);
	LinkedList* Lb = creat(B, MAXV);
	LinkedList* Lc = getSort(La, Lb),*pc=Lc->next;
	while (pc) {
		printf("%d\t", pc->data);
		pc = pc->next;
	}
	printf("\n");
	return 0;
}