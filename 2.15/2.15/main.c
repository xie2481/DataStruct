/*连接两个链表*/
#include <stdio.h>
#include <stdlib.h>
typedef int Elem;
typedef struct LinkedList {
	Elem data;
	struct LinkedList* next;
}LinkedList;
LinkedList* creat() {
	int A[10] = { 10,9,8,7,6,5,4,3,2,1 };
	int i = 0;
	LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList));
	L->next = NULL;
	for (i = 0; i < 10; i++) {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->data = A[i];
		node->next = L->next;
		L->next = node;
	}
	return L;
}
int Length(LinkedList* L) {
	LinkedList* p = L->next;
	int length = 0;
	while (p) {
		length++;
		p = p->next;
	}
	return length;
}
int compare(Elem a, Elem b) {
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	else
		return -1;
}
LinkedList* link(LinkedList* ha, LinkedList* hb) {
	LinkedList* hc = compare(Length(ha), Length(hb)) > 0 ? ha : hb;
	LinkedList* p = hc;
	while (p->next != NULL)
		p = p->next;
	if (hc == ha) {
		p->next = hb->next;
	}
	else
		p->next = ha->next;
	return hc;
}
int main() {
	LinkedList* ha = creat();
	LinkedList* hb = creat();
	LinkedList* hc = link(ha, hb);
	LinkedList* p = hc->next;
	while (p) {
		printf("%d\t", p->data);
		p = p->next;
	}
	return 0;
}