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
	if (q->rear->next != q->rear) {//���в�Ϊ��
		Node* p = q->rear->next->next;
		if (p == q->rear) {//������ֻ��һ��Ԫ��
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
		printf("����Ϊ�գ�ɾ��ʧ��\n");
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