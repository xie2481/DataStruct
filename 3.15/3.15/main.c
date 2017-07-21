#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAXV 20
typedef struct {
	int data[20];
	int p1;//ָʾ����ջ��
	int p2;//ָʾ����ջ��
}stack,*STACK;
STACK initstack() {
	STACK tws = (STACK)malloc(sizeof(stack));
	memset(tws->data, 0, MAXV);
	tws->p1 = -1;
	tws->p2 = MAXV;
	return tws;
}
void push(STACK tws, int i, int x) {
	if (tws->p1 != tws->p2-1) {
		if (!i)
			tws->data[++tws->p1] = x;
		else
			tws->data[--tws->p2] = x;
	}
}
int pop(STACK tws, int i) {
	if (!i&&tws->p1!=-1) {
		return tws->data[tws->p1--];
	}
	else if (i&&tws->p2 != MAXV) {
		return tws->data[tws->p2++];
	}
	else
		return INT_MAX;
}
int main() {
	STACK s = initstack();
	push(s, 0, 5);
	push(s, 0, 4);
	push(s, 1, 7);
	push(s, 1, 8);
	printf("����ջ��ջ:\n");
	printf("%d\t", pop(s, 0));
	printf("%d\n", pop(s, 0));
	printf("����ջ��ջ:\n");
	printf("%d\t", pop(s, 1));
	printf("%d\n", pop(s, 1));
	return 0;
}