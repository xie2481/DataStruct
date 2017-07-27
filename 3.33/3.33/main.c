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
		data < (q->queue[q->front-1] + q->queue[q->rear+1]) / 2) {//默认插队头
		printf("当前作业将插入队头,请稍等...\n");
		if (q->front <= q->rear) {
			q->queue[q->front++] = data;
			printf("插入成功\n");
		}
		else
			printf("队列已满\n");
	}
	else {
		printf("当前作业将插入队尾,请稍等...\n");
		if (q->front <= q->rear) {
			q->queue[q->rear--] = data;
			printf("插入成功\n");
		}
		else
			printf("队列已满\n");
	}
}
int main() {
	int total = 0;
	Queue* q = init();
	printf("请输入作业的数量(数量要少于%d)\n",MAXSIZE);
	scanf("%d", &total);
	if (total < MAXSIZE) {
		while (total-- > 0) {
			int data = 0;
			printf("请输入当前作业的时间:\n");
			scanf("%d", &data);
			inQueue(q, data);
		}
	}
	else {
		printf("输入不合法\n");
	}
	return 0;
}