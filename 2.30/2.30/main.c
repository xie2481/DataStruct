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
void insert(LinkedList* ptail, int data) {
	
}
void Delete(LinkedList* pre, LinkedList* p) {
	pre->next = p->next;
	free(p);
}
LinkedList* getSort(LinkedList* La, LinkedList* Lb, LinkedList* Lc) {
	LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList)),*ptail=L;
	LinkedList* pa = La->next,*pb=Lb->next,*pc=Lc->next,*pre=La;
	L->next = NULL;
	while (pa) {
		int isTrue = 0;
		pb = Lb->next;
		while (pb) {
			if (pa->data < pb->data)
				break;
			if (pa->data == pb->data) {
				pc = Lc->next;
				while (pc) {
					if (pa->data == pc->data) {
						isTrue = 1;
						break;
					}
					if (pa->data < pc->data)
						break;
					pc = pc->next;
				}
			}
			pb = pb->next;
		}
		if (isTrue == 0) {//该元素将被删除
			Delete(pre, pa);
			pa = pre->next;
		}
		else {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->data =pa->data;
		node->next = NULL;
		ptail->next = node;
		ptail = node;
		pa = pa->next;
		pre = pre->next;
	}
	}
	return L;
}
int main() {
	int A[MAXV] = { 1,2,3,4,5,5,7,8,9,10 };
	int B[MAXV] = { 3,3,5,7,9,10,11,12,13,14 };
	int C[MAXV] = { 4,5,9,10,11,12,13,14,15,16 };
	LinkedList* La = creat(A, MAXV);
	LinkedList* Lb = creat(B, MAXV);
	LinkedList* Lc = creat(C, MAXV);
	LinkedList* L = getSort(La, Lb, Lc),*p=L->next;
	while (p) {
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");
	return 0;
}