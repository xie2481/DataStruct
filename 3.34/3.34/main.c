#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 10
#define P 1
#define H 2
#define S 3
typedef struct {
	int queue[MAXSIZE];
	int front;
	int rear;
}Queue;
Queue* init() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	memset(q->queue, 0, MAXSIZE);
	q->front = 0;
	q->rear = MAXSIZE - 1;
	return q;
}
void inQueue(Queue* q, int data) {
	if (data == P) {//硬座进队头
		printf("EP\n");
		q->queue[q->front++] = data;
	}
	else if (data == H) {//硬卧进队尾
		printf("AH\n");
		q->queue[q->rear--] = data;
	}
	else {//所有硬座出从头端出队列,软卧再进队列
		q->front--;//指到头端队列的尾部
		while (q->queue[q->front] == P) {
			q->front--;
			printf("DP\n");
		}
		q->front++;
		q->queue[q->front++] = data;
		printf("ES\n");
	}
}
void deQueue(Queue* q) {//从0位置开始按顺序出队即可
	int i = 0;
	while (i<MAXSIZE) {
		if (q->queue[i] == P) {
			printf("DP\t");
		}
		else if (q->queue[i] == H) {
			printf("DH\t");
		}
		else if (q->queue[i] == S) {
			printf("DS\t");
		}
		i++;
	}
}
int main() {
	Queue* q = init();
	int total = 0;
	printf("请输入火车的数量\n");
	scanf("%d", &total);
	while (total-- > 0) {
		char ch = 0;
		getchar();
		printf("请输入火车车厢的种类(P表示硬座,H表示硬卧,S表示软卧)\n");
		ch = getchar();
		if (ch == 'P') {
			inQueue(q, P);
		} 
		if (ch == 'H') {
			inQueue(q, H);
		}
		if (ch == 'S') {
			inQueue(q, S);
		}
	}
	deQueue(q);
	return 0;
}
