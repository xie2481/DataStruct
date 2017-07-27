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
	if (data == P) {//Ӳ������ͷ
		printf("EP\n");
		q->queue[q->front++] = data;
	}
	else if (data == H) {//Ӳ�Խ���β
		printf("AH\n");
		q->queue[q->rear--] = data;
	}
	else {//����Ӳ������ͷ�˳�����,�����ٽ�����
		q->front--;//ָ��ͷ�˶��е�β��
		while (q->queue[q->front] == P) {
			q->front--;
			printf("DP\n");
		}
		q->front++;
		q->queue[q->front++] = data;
		printf("ES\n");
	}
}
void deQueue(Queue* q) {//��0λ�ÿ�ʼ��˳����Ӽ���
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
	printf("������𳵵�����\n");
	scanf("%d", &total);
	while (total-- > 0) {
		char ch = 0;
		getchar();
		printf("������𳵳��������(P��ʾӲ��,H��ʾӲ��,S��ʾ����)\n");
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
