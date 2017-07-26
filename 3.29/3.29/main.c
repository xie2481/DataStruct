#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int tag;//tag为1代表队列满，0为空
	int queue[10];
	int front;//指示队头指针
	int rear;//指示队尾指针
}Queue;
Queue* init() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->tag = 0;
	q->front = 0;
	q->rear = 0;
	return q;
}
void inQueue(Queue* q,int data) {
	if (q->tag != 1) {//队列未满
		q->queue[q->rear] = data;
		q->rear = (q->rear + 1) % 10;
		if (q->rear == q->front)
			q->tag = 1;
	}
	else {
		printf("队列满\n");
	}
}
int deQueue(Queue* q) {
	if (q->tag != 0) {//如果队列不为空
		int temp = q->queue[q->front];
		q->front = (q->front + 1) % 10;
		if (q->front == q->rear)
			q->tag = 0;
		return temp;
	}
	else {
		printf("队列为空\n");
		return 0;
	}
}
int main() {
	Queue* q = init();
	int i = 0;
	for (i = 0; i < 10; i++) {
		inQueue(q, i);
	}
	for (i = 0; i < 10; i++) {
		printf("%d\t", deQueue(q));
	}
	printf("\n");
	return 0;
}