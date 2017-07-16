#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 10
typedef char Elem;
typedef struct CycleList {
	Elem data;
	struct CycleList* next;
}CycleList;
CycleList* creatByArray(char* A, int length) {
	CycleList* L = (CycleList*)malloc(sizeof(CycleList)),*ptail=L;
	int i = 0;
	L->next = NULL;
	for (i = 0; i < length; i++) {
		CycleList* node = (CycleList*)malloc(sizeof(CycleList));
		node->data = A[i];
		node->next = NULL;
		ptail->next = node;
		ptail = node;
	}
	return L;
}
void splitList(CycleList* L, CycleList* La, CycleList* Lb, CycleList* Lc) {
	CycleList* pa = La, *pb = Lb, *pc = Lc,*p=L->next;
	while (p) {
		if ((p->data >= 'a'&&p->data <= 'z') || (p->data >= 'A'&&p->data <= 'Z')) {
			CycleList* node = (CycleList*)malloc(sizeof(CycleList));
			node->data = p->data;
			node->next = NULL;
			pa->next = node;
			pa = node;
		}
		else if (p->data >= '0'&&p->data <= '9') {
			CycleList* node = (CycleList*)malloc(sizeof(CycleList));
			node->data = p->data;
			node->next = NULL;
			pb->next = node;
			pb = node;
		}
		else {
			CycleList* node = (CycleList*)malloc(sizeof(CycleList));
			node->data = p->data;
			node->next = NULL;
			pc->next = node;
			pc = node;
		}
		p = p->next;
	}
	pa->next = La->next;
	pb->next = Lb->next;
	pc->next = Lc->next;
}
int main() {
	char* s = "45qwrqr#%@!";
	CycleList* L = creatByArray(s, strlen(s));
	CycleList* La = (CycleList*)malloc(sizeof(CycleList)),*pa=NULL;
	CycleList* Lb = (CycleList*)malloc(sizeof(CycleList)),*pb=NULL;
	CycleList* Lc = (CycleList*)malloc(sizeof(CycleList)),*pc=NULL;
	splitList(L, La, Lb, Lc);
	pa = La->next;
	pb = Lb->next;
	pc = Lc->next;
	while (pa&&pa->next != La->next) {
		printf("%c\t", pa->data);
		pa = pa->next;
	}
	if (pa) {
		printf("%c\t", pa->data);
	}
	printf("\n");
	while (pb&&pb->next != Lb->next) {
		printf("%c\t", pb->data);
		pb = pb->next;
	}
	if (pb) {
		printf("%c\t", pb->data);
	}
	printf("\n");
	while (pc&&pc->next != Lc->next) {
		printf("%c\t", pc->data);
		pc = pc->next;
	}
	if (pc) {
		printf("%c\t", pc->data);
	}
	printf("\n");
	return 0;
}
