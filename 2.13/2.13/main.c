//返回线性表中第一个与e满足compare（)的数据元素的位序。若这样的数据元素不存在，则返回0
#include <stdio.h>
#include <stdlib.h>
typedef int Elem;
int compare(Elem a, Elem b) {
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	else
		return -1;
}
typedef struct LinkedList {
	Elem data;
	struct LinkedList* next;
}LinkedList;
LinkedList* creat() {
	LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList));
	L->next = NULL;
	int A[10] = { 10,9,8,7,6,5,4,3,2,1 },i=0;
	for (i = 0; i < 10; i++) {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->data = A[i];
		node->next = L->next;
		L->next = node;
	}
	return L;
}
int Locate(LinkedList* L, Elem x, int(*p)(Elem a, Elem b)) {
	LinkedList* pt = L->next;
	int poisition = 0;
	while (pt) {
		if (p(pt->data, x) == 0) {
			return ++poisition;
		}
		else {
			pt = pt->next;
			poisition++;
		}
	}
	return 0;
}
int main() {
	LinkedList* L = creat();
	int(*p)(Elem a, Elem b);
	p = compare;
	printf("%d\n", Locate(L, 10, p));
	return 0;
}