#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
	int rear;
	int length;
	int queue[10];
}Queue;
Queue* init() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->rear = 0;
	q->length = 0;
	return q;
}
void inQueue(Queue* q, int data) {
	if (q->length < 10) {//����δ��
		q->queue[q->rear] = data;
		q->rear = (q->rear + 1) % 10;
		q->length++;
	}
	else {
		printf("��������\n");
	}
}
int deQueue(Queue* q) {
	if (q->length != 0) {//���в�Ϊ��
		int front = (q->rear - q->length) % 10 >= 0 ? (q->rear - q->length) % 10 :
			10 - (int)fabs((q->rear - q->length) % 10);
		q->length--;
		return q->queue[front];
	}
	else {
		printf("����Ϊ��\n");
		return 0;
	}
}
int main() {
	Queue* q = init();
	int i = 0;
	for (i = 0; i < 8; i++) {
		inQueue(q, i);
	}
	for (i = 0; i < 10; i++) {
		printf("%d\t", deQueue(q));
	}
	printf("\n");
	return 0;
}
