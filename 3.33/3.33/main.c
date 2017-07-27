#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 10
typedef struct {
	int queue[MAXSIZE];
	int front;
	int rear;
}Queue;
Queue* init() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->front = 0;
	q->rear = MAXSIZE - 1;
	memset(q->queue, 0, MAXSIZE);
	return q;
}
void inQueue(Queue* q, int data) {
	if ((q->rear==MAXSIZE-1&&q->front==0)||
		data < (q->queue[q->front-1] + q->queue[q->rear+1]) / 2) {//Ĭ�ϲ��ͷ
		printf("��ǰ��ҵ�������ͷ,���Ե�...\n");
		if (q->front <= q->rear) {
			q->queue[q->front++] = data;
			printf("����ɹ�\n");
		}
		else
			printf("��������\n");
	}
	else {
		printf("��ǰ��ҵ�������β,���Ե�...\n");
		if (q->front <= q->rear) {
			q->queue[q->rear--] = data;
			printf("����ɹ�\n");
		}
		else
			printf("��������\n");
	}
}
int main() {
	int total = 0;
	Queue* q = init();
	printf("��������ҵ������(����Ҫ����%d)\n",MAXSIZE);
	scanf("%d", &total);
	if (total < MAXSIZE) {
		while (total-- > 0) {
			int data = 0;
			printf("�����뵱ǰ��ҵ��ʱ��:\n");
			scanf("%d", &data);
			inQueue(q, data);
		}
	}
	else {
		printf("���벻�Ϸ�\n");
	}
	return 0;
}