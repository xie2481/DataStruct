#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int tag;//tagΪ1�����������0Ϊ��
	int queue[10];
	int front;//ָʾ��ͷָ��
	int rear;//ָʾ��βָ��
}Queue;
Queue* init() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->tag = 0;
	q->front = 0;
	q->rear = 0;
	return q;
}
void inQueue(Queue* q,int data) {
	if (q->tag != 1) {//����δ��
		q->queue[q->rear] = data;
		q->rear = (q->rear + 1) % 10;
		if (q->rear == q->front)
			q->tag = 1;
	}
	else {
		printf("������\n");
	}
}
int deQueue(Queue* q) {
	if (q->tag != 0) {//������в�Ϊ��
		int temp = q->queue[q->front];
		q->front = (q->front + 1) % 10;
		if (q->front == q->rear)
			q->tag = 0;
		return temp;
	}
	else {
		printf("����Ϊ��\n");
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