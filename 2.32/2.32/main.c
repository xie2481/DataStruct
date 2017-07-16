#include <stdio.h>
#include <stdlib.h>
#define MAXV 10
typedef int Elem;
typedef struct CycleList {
	Elem data;
	struct CycleList* prior;
	struct CycleList* next;
}CycleList;
CycleList* creat(int* A, int length) {
	CycleList* L = (CycleList*)malloc(sizeof(CycleList)),*ptail=L;
	int i = 0;
	for (i = 0; i < length; i++) {
		CycleList* node = (CycleList*)malloc(sizeof(CycleList));
		node->next =node->prior= NULL;
		node->data = A[i];
		ptail->next = node;
		ptail = node;
	}
	ptail->next = L->next;
	return L;
}
void fixUp(CycleList* L) {
	CycleList* ptail = L->next->next,*p=L->next,*pt=NULL;
	while (ptail!=NULL&&ptail->next != L->next)
		ptail = ptail->next;
	p->prior = ptail;
	p = p->next;
	pt = L->next;
	while (p!=NULL&&p != L->next) {
		p->prior = pt;
		p = p->next;
		pt = pt->next;
	}
}
int main() {
	int A[MAXV] = { 1,2,3,4,5,6,7,8,9,10 };
	CycleList* L = creat(A, MAXV),*p=L->next;
	fixUp(L);
	p =p->prior;
	printf("%d\t", p->data);
	p = p->prior;
	while (p!=NULL&&p!=L->next->prior) {
		printf("%d\t", p->data);
		p = p->prior;
	}
	printf("\n");
	return 0;
}