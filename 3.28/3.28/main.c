#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int data;
	struct Node* next;
}Node;
typedef struct {
	Node* rear;
}Queue;
Queue* init() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->rear = (Node*)malloc(sizeof(Node));
	q->rear->next = q->rear;
	return q;
}
void inQueue(Queue* q,int data) {
	Node* node= (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = q->rear->next;
	q->rear->next = node;
	q->rear = node;
}
int deQueue(Queue* q) {
	int data = 0;
	if (q->rear->next != q->rear) {//队列不为空
		Node* p = q->rear->next->next;
		if (p == q->rear) {//队列中只有一个元素
			q->rear = q->rear->next;
			q->rear->next = q->rear;
		}
		else {
			q->rear->next->next = p->next;
		}
		data = p->data;
		free(p);
	}
	else {
		printf("队列为空，删除失败\n");
	}
	return data;
}
int main() {
	Queue* q = init();
	inQueue(q, 5);
	inQueue(q, 4);
	printf("%d\n", deQueue(q));
	printf("%d\n", deQueue(q));
	return 0;
}