#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
	int coef;
	int exp;
}PolyTerm;
typedef struct {
	PolyTerm* data;
	int length;
}SqPoly;
SqPoly* creat(int* C,int* E,int length) {
	SqPoly* sq = (SqPoly*)malloc(sizeof(SqPoly));
	int i = 0;
	sq->length = length;
	sq->data = (PolyTerm*)malloc(sizeof(PolyTerm)*length);
	for (i = 0; i < length; i++) {
		sq->data[i].coef = C[i];
		sq->data[i].exp = E[i];
	}
	return sq;
}
int calc(SqPoly* sq,int x0) {
	int i = 0, sum = 0;
	for (i = 0; i < sq->length; i++) {
		sum += (sq->data[i].coef)*(int)pow((double)x0, (double)sq->data[i].exp);
	}
	return sum;
}
SqPoly* minus(SqPoly* p1, SqPoly* p2) {
	SqPoly* p = (SqPoly*)malloc(sizeof(SqPoly));
	int i = 0;
	p->length = max(p1->length,p2->length);
	p->data = (PolyTerm*)malloc(sizeof(PolyTerm)*p->length);
	for (i = 0; i < min(p1->length, p2->length); i++) {
		p->data[i].coef = p1->data[i].coef - p2->data[i].coef;
		p->data[i].exp = p1->data[i].exp;
	}
	if (i == p1->length) {
		while (i < p2->length) {
			p->data[i].coef = -p2->data[i].coef;
			p->data[i].exp = p2->data[i].exp;
			i++;
		}
	}
	if (i == p2->length) {
		while (i < p1->length) {
			p->data[i].coef = p1->data[i].coef;
			p->data[i].exp = p1->data[i].exp;
			i++;
		}
	}
	return p;
}

int main() {
	int C[5] = { 1,2,3,4,5 };
	int E[5] = { 1,2,3,4,5 };
	int A[7] = { 0,1,2,3,4,7,8 };
	int B[7] = { 1,2,3,4,5,6,8 };
	int result = 0,i=0;
	SqPoly* sq = creat(C, E, 5);
	SqPoly* sq2 = creat(A, B, 7);
	SqPoly* p = minus(sq2, sq);
	result = calc(sq, 1);
	printf("%d\n", result);
	for (i = 0; i < p->length-1; i++) {
		printf("%dx^%d + ", p->data[i].coef, p->data[i].exp);
	}
	printf("%dx^%d\n ", p->data[i].coef, p->data[i].exp);
	return 0;
}