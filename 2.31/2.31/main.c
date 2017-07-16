#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXV 10
typedef int Elem;
typedef struct CycleList {
	Elem data;
	struct CycleList* next;
}CycleList;
CycleList* creat(int* A, int length) {
	CycleList* L = NULL,*ptail=NULL,*ps=NULL;//ps存储随机返回的s指针
	int i = 0,s=0;
	srand(time(NULL));
	s = rand() % length;
	for (i = 0; i < length; i++) {
		if (L == NULL) {
			L = (CycleList*)malloc(sizeof(CycleList));
			L->data = A[i];
			L->next = NULL;
			ptail = L;
		}
		else {
			CycleList* node = (CycleList*)malloc(sizeof(CycleList));
			node->data = A[i];
			node->next = NULL;
			ptail->next = node;
			ptail = node;
		}
		if (s == i)
			ps = ptail;
	}
	ptail->next = L;
	return ps;
}
void delete(CycleList* s) {
	CycleList* p = s, *pre = NULL;//p为s前驱，pre为p前驱
	while (p->next != s) {
		pre = p;
		p = p->next;
	}
	pre->next = p->next;
	free(p);
}
int main() {
	int A[MAXV] = { 1,2,3,4,5,6,7,8,9,10 };
	CycleList* s = creat(A, MAXV),*pt=s;
	int i = 0;
	printf("当前序列为:\t");
	while (i++<MAXV) {
		printf("%d\t", pt->data);
		pt = pt->next;
	}
	printf("\n");
	delete(s);
	printf("删除后序列为:\t");
	pt = s;
	i = 0;
	while (i++ < MAXV - 1) {
		printf("%d\t", pt->data);
		pt = pt->next;
	}
	return 0;
}