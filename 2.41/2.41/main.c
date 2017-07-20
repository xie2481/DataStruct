#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int coef;
	int exp;
}PolyTerm;
typedef struct PolyNode {
	PolyTerm data;
	struct PolyNode* next;
}PolyNode,*PolyLink;
typedef PolyLink LinkedPoly;
LinkedPoly creat(int* C, int* E, int length) {
	LinkedPoly p = (LinkedPoly)malloc(sizeof(PolyNode)), ptail =p;
	int i = 0;
	for (i = 0; i < length; i++) {
		LinkedPoly node = (LinkedPoly)malloc(sizeof(PolyNode));
		node->data.coef = C[i];
		node->data.exp = E[i];
		node->next = NULL;
		ptail->next = node;
		ptail = node;
	}
	ptail->next = p;
	return p;
}
void getDerivedFunction(LinkedPoly p) {
	LinkedPoly pt = p->next,pre=p;
	while(pt!=p){
		if (pt->data.exp == 0) {//当前为常数项，求导后删除该项
			pre->next = pt->next;
			free(pt);
			pt = pre->next;
		}
		else {
			pt->data.coef *= pt->data.exp;
			pt->data.exp--;
			pt = pt->next;
			pre = pre->next;
		}
	}
}
void getOddAndEvenFunction(LinkedPoly p,LinkedPoly pAdd,LinkedPoly pEven) {
	LinkedPoly pAtail=pAdd;
	LinkedPoly pEtail=pEven;
	LinkedPoly q = p->next;
	while (q != p) {
		LinkedPoly ptemp = q;
		q = q->next;
		if (ptemp->data.exp & 1) {//奇数项
			pAtail->next = ptemp;
			pAtail = ptemp;
		}
		else {//偶数项
			pEtail->next = ptemp;
			pEtail = ptemp;
		}
	}
	pAtail->next = pAdd;
	pEtail->next = pEven;
}
int main() {
	int C[5] = { 1,2,3,4,5 };
	int E[5] = { 1,2,3,4,5 };
	LinkedPoly p = creat(C, E, 5),s=NULL;
	LinkedPoly pAdd = (LinkedPoly)malloc(sizeof(PolyNode));
	LinkedPoly pEven = (LinkedPoly)malloc(sizeof(PolyNode));
	getDerivedFunction(p);
	s = p->next;
	while (s != p) {
		printf("%dx^%d ", s->data.coef, s->data.exp);
		if (s->next != p)
			printf("+ ");
		s = s->next;
	}
	printf("\n");
	getOddAndEvenFunction(p, pAdd, pEven);
	printf("奇数项如下：\n");
	s = pAdd->next;
	while (s != pAdd) {
		printf("%dx^%d ", s->data.coef, s->data.exp);
		if (s->next != pAdd)
			printf("+ ");
		s = s->next;
	}
	printf("\n");
	printf("偶数项如下：\n");
	s = pEven->next;
	while (s != pEven) {
		printf("%dx^%d ", s->data.coef, s->data.exp);
		if (s->next != pEven)
			printf("+ ");
		s = s->next;
	}
	printf("\n");
	return 0;
}