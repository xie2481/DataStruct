#include <stdio.h>
#include <stdlib.h>
typedef int Elem;
typedef struct CycleLinkedList {
	Elem data;
	struct CycleLinkedList* prior;
	struct CycleLinkedList* next;
}CycleLinkedList;
CycleLinkedList* creat(int* A,int length) {
	CycleLinkedList* L = (CycleLinkedList*)malloc(sizeof(CycleLinkedList)),*ptail=L;
	int i = 0;
	L->next =L->prior=NULL;
	for (i = 0; i < length; i++) {
		CycleLinkedList* node = (CycleLinkedList*)malloc(sizeof(CycleLinkedList));
		node->data = A[i];
		node->next = NULL;
		node->prior = ptail;
		ptail->next = node;
		ptail = node;
	}
	ptail->next = L;
	L->prior = ptail;
	return L;
}
void fixUp(CycleLinkedList* L) {
	CycleLinkedList* Lt = (CycleLinkedList*)malloc(sizeof(CycleLinkedList)), *p = NULL, *p2 = L->next->next;
	Lt->next =Lt;
	p = L->next;
	while (p != L&&p->next !=L) {
		CycleLinkedList* ptemp = p->next;
		p->next = p->next->next;
		p->next->next->prior = p;
		L->prior = p;
		Lt->next->prior = ptemp;
		ptemp->next = Lt->next;
		Lt->next = ptemp;
		p = p->next;
	}
	if (Lt->next != Lt) {//在不止一个元素的前提下
		L->prior->next = Lt->next;
		Lt->next->prior = L->prior;
		p2->next = L;
		L->prior = p2;
	}
}
int main() {
	int A[10] = { 1,2,3,4,5,6,7,8,9,10 };
	CycleLinkedList* L = creat(A, 1),*pa=NULL;
	fixUp(L);
	pa = L->next;
	while (pa != L) {
		printf("%d\t", pa->data);
		pa = pa->next;
	}
	return 0;
}