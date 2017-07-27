#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int* queue;
	int front;
	int rear;
	int maxSize;
}Queue;
Queue* init(int k) {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->queue = (int*)malloc(sizeof(int)*(k));
	q->front = q->rear = 0;
	q->maxSize = k;
	return q;
}
void inQueue(Queue* q, int data) {
		q->queue[q->rear] = data;
		q->rear = (q->rear + 1) % q->maxSize;
}
int main() {
	int max = 0, k = 0,i=1;
	Queue* q = NULL;
	printf("请输入最大值以及k值\n");
	scanf("%d%d", &max, &k);
	q = init(k);
	inQueue(q, 0);//k>=2
	inQueue(q, 1);
	while (1) {
		int f = q->queue[q->front] + q->queue[(q->front + 1) % q->maxSize];
		if (f > max)
			break;
		else {
			q->queue[q->rear] = f;
			q->rear = (q->rear + 1) % q->maxSize;
			q->front = (q->front + 1) % q->maxSize;
		}
	}
	//获取队列前一个元素的值
	q->front = q->front == 0 ? q->maxSize - 1 : q->front - 1;
	for (i = 0; i < k; i++) {
		printf("%d\t", q->queue[q->front]);
		q->front = (q->front + 1) % q->maxSize;
	}
	return 0;
}