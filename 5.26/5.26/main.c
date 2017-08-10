#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
	int data;
	struct Node* pright;
	struct Node* pdown;
}Node;
typedef struct {
	struct Node* pright;//�洢������
	struct Node* pdown;//�洢������
	int m;//��¼����
	int n;//��¼����
}LinkedList;
LinkedList* init(int m,int n) {
	LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList));
	L->pright = (Node*)malloc(sizeof(Node)*n);
	L->pdown = (Node*)malloc(sizeof(Node)*m);
	memset(L->pright, NULL, sizeof(Node)*n);
	memset(L->pdown, NULL, sizeof(Node)*m);
	L->m = m;
	L->n = n;
	return L;
}
void insert(LinkedList* L, int data, int m, int n) {
	int i = 0, j = 0;
	Node* node = (Node*)malloc(sizeof(Node));
	Node* p = NULL;
	node->data = data;
	if (m < 0 || m >= L->m || n < 0 || n >= L->n) {
		printf("λ������\n");
		free(node);//��ǰ�ڵ�����
		return;
	}
    //������
	if (L->pdown[m].pright == NULL) {//����û��Ԫ��
		L->pdown[m].pright = (Node*)malloc(sizeof(Node));
		L->pdown[m].pright->data = m;//����ͷ�洢λ����Ϣ
		L->pdown[m].pright->pright = NULL;
	}
	p = L->pdown[m].pright;
	while (p&&p->pright) {//��pָ��������һ��Ԫ��
		p = p->pright;
	}
	p->pright = node;
	node->pright = L->pdown[m].pright;//����ѭ������
	//������
	if (L->pright[n].pdown == NULL) {//����û��Ԫ��
		L->pright[n].pdown = (Node*)malloc(sizeof(Node));
		L->pright[n].pdown->data = n;
		L->pright[n].pdown->pdown = NULL;
	}
	p = L->pright[n].pdown;
	while (p&&p->pdown) {//��pָ��������һ��Ԫ��
		p = p->pdown;
	}
	p->pdown = node;
	node->pdown = L->pright[n].pdown;
}
void print(LinkedList* L) {
	int i = 0;
	for (i = 0; i < L->n; i++) {
		if (L->pright[i].pdown) {//��ǰ����Ԫ��
			Node* p = L->pright[i].pdown->pdown;
			while (p!=L->pright[i].pdown) {
				printf("%d %d %d\n" ,p->pright->data,i ,p->data);
				p = p->pdown;
			}
		}
	}
}
int main() {
	LinkedList* L=init(5, 6);
	insert(L, 10, 0, 3);
	insert(L, 50, 1, 5);
	print(L);
	return 0;
}
