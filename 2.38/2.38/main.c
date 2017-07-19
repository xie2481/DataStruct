#include <stdio.h>
#include <stdlib.h>
typedef int Elem;
typedef struct CycleLinkedList {
	Elem data;
	int freq;
	struct CycleLinkedList* prior;
	struct CycleLinkedList* next;
}CycleLinkedList;
CycleLinkedList* creat(int* A, int length) {
	CycleLinkedList* L = (CycleLinkedList*)malloc(sizeof(CycleLinkedList)), *ptail = L;
	int i = 0;
	L->next = L->prior = NULL;
	for (i = 0; i < length; i++) {
		CycleLinkedList* node = (CycleLinkedList*)malloc(sizeof(CycleLinkedList));
		node->data = A[i];
		node->next = NULL;
		node->freq = 0;
		node->prior = ptail;
		ptail->next = node;
		ptail = node;
	}
	ptail->next = L;
	L->prior = ptail;
	return L;
}
int Locate(CycleLinkedList* L, Elem x) {
	CycleLinkedList* p = L->next,*pt=L->next;
	int i = 1;
	while (p != L) {
		if (p->data == x) {
			p->freq++;
			break;
		}
		p = p->next;
		i++;
	}
	while (pt != L) {
		if (pt==p)
			break;
		if (p->freq > pt->freq) {
			if (p->prior != pt) {//p不是pt的直接后继
				CycleLinkedList* pret = pt->prior;
				CycleLinkedList* postt = pt->next;
				CycleLinkedList* pre = p->prior;
				CycleLinkedList* post = p->next;
				pret->next = p;
				p->next = postt;
				p->prior = pret;
				postt->prior = p;
				pre->next = pt;
				pt->next = post;
				pt->prior = pre;
				post->prior = pt;
			}
			else {
				CycleLinkedList* pre = pt->prior;
				CycleLinkedList* post = p->next;
				pt->next = post;
				post->prior = pt;
				pt->prior = p;
				p->next = pt;
				pre->next = p;
				p->prior = pre;
			}
			break;
		}
		pt = pt->next;
	}
	return i;
}
int main() {
	int A[10] = { 1,2,3,4,5,6,7,8,9,10 },t=0;
	CycleLinkedList* L = creat(A, 10),*p=NULL;
	Locate(L, 10);
	//Locate(L, 6);
	//Locate(L, 6);
	p = L->next;
	while (p != L) {
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");
	return 0;
}