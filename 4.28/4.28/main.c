#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct LinkedList {
	char chdata;
	struct LinkedList* succ;
	struct LinkedList* next;
}LinkedList;
LinkedList* init() {
	LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList));
	L->succ = NULL;
	L->next = L;
	return L;
}
void StrAssign(LinkedList* L, char* s) {
	int i = 0;
	LinkedList* ptail = L;
	L->chdata = (char)strlen(s);
	while (s[i] != '\0') {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->chdata = s[i];
		node->succ = NULL;
		ptail->succ = node;
		node->next = ptail;
		ptail = node;
		i++;
	}
}
void getNext(LinkedList* L) {
	if (L->succ) {//²»ÊÇ¿Õ´®
		LinkedList* p = L,*ps=L->succ;
		L->succ->next = L;
		while (p&&p->succ&&ps->succ) {
			if (p == L || ps->chdata == p->chdata) {
				ps = ps->succ;
				p = p->succ;
				ps->next = p;
			}
			else {
				p = p->next;
			}
		}
	}
}
int index_KMP(LinkedList* S, LinkedList* T, int pos) {
	LinkedList* p = S,*pt=T->succ;
	int i = 0;
	for (i = 0; i < pos; i++) {
		p = p->succ;
	}
	i = pos;
	while (p&&pt) {
		if (pt == T || pt->chdata == p->chdata) {
			p = p->succ;
			pt = pt->succ;
			++i;
		}
		else {
			pt = pt->next;
		}
	}
	if (pt == NULL)
		return i - T->chdata;
	else
	 return 0;
}
int main() {
	LinkedList* L = init(),*T=init(),*p=NULL;
	StrAssign(L, "abaabc");
	StrAssign(T, "aa");
	getNext(T);
	p = T->succ;
	while (p) {
		if (p->next!=T)
			printf("%c\t", p->next->chdata);
		else
			printf("%c\t", p->chdata);
		p = p->succ;
	}
	printf("\n");
	printf("%d\n",index_KMP(L, T,1));
	return 0;
}