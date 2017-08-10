//Ĭ�ϲ����Ԫ�ذ���������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
	int data;
	int i;
	int j;
	struct Node* pright;
	struct Node* pdown;
}Node;
typedef struct {
	struct Node* pright;//�洢������
	struct Node* pdown;//�洢������
	int m;//��¼����
	int n;//��¼����
}LinkedList;
LinkedList* init(int m, int n) {
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
	node->i = m;
	node->j = n;
	if (m < 0 || m >= L->m || n < 0 || n >= L->n) {
		printf("λ������\n");
		free(node);//��ǰ�ڵ�����
		return;
	}
	//������
	if (L->pdown[m].pright == NULL) {//����û��Ԫ��
		L->pdown[m].pright = (Node*)malloc(sizeof(Node));
		L->pdown[m].pright->data = m;//����ͷ�洢λ����Ϣ
		L->pdown[m].pright->pright = L->pdown[m].pright;
		L->pdown[m].pright->pdown= NULL;
	}
	p = L->pdown[m].pright->pright;
	while (p!=L->pdown[m].pright&&p->pright!= L->pdown[m].pright) {//��pָ��������һ��Ԫ��
		if (p->pdown&&p->pdown->data == n) {
			printf("��Ԫ���Ѵ���\n");
			return;
		}
		p = p->pright;
	}
	p->pright = node;
	node->pright = L->pdown[m].pright;//����ѭ������
     //������
	if (L->pright[n].pdown == NULL) {//����û��Ԫ��
		L->pright[n].pdown = (Node*)malloc(sizeof(Node));
		L->pright[n].pdown->data = n;
		L->pright[n].pdown->pdown =L->pright[n].pdown;
		L->pright[n].pdown->pright = NULL;
	}
	p = L->pright[n].pdown->pdown;
	while (p!= L->pright[n].pdown&&p->pdown!= L->pright[n].pdown) {//��pָ��������һ��Ԫ��,֮ǰ�ڲ�����ʱ�Ѿ����й��ظ�Ԫ�صļ��
		p = p->pdown;
	}
	p->pdown = node;
	node->pdown = L->pright[n].pdown;
}
LinkedList* add(LinkedList* L1, LinkedList* L2) {
	if (L1->m == L2->m&&L1->n&&L2->n) {//����ɼ�
		int i = 0;
		LinkedList* L3 = init(L1->m,L1->n);
		for (i = 0; i < L1->n; i++) {
			if (L1->pright[i].pdown && L2->pright[i].pdown) {//��ǰ2�������ڸ��ж��з���Ԫ
				Node* p1 = L1->pright[i].pdown->pdown,*p2= L2->pright[i].pdown->pdown;
				while (p1 != L1->pright[i].pdown&&p2 !=L2->pright[i].pdown) {
					if (p1->i==p2->i&&p1->data + p2->data) {//������ͬλ�õ�Ԫ��
						insert(L3, p1->data + p2->data, p1->i, i);
						p1 = p1->pdown;
						p2 = p2->pdown;
					}
					else if (p1->i < p2->i) {
						insert(L3, p1->data, p1->i, i);
						p1 = p1->pdown;
					}
					else if (p1->i > p2->i) {
						insert(L3, p2->data, p2->i, i);
						p2 = p2->pdown;
					}
					else {
						p1 = p1->pdown;
						p2 = p2->pdown;
					}
				}
				while (p1 != L1->pright[i].pdown) {//���뵱ǰ����p1δ����Ԫ��
					insert(L3, p1->data, p1->i, i);
					p1 = p1->pdown;
				}
				while (p2 != L2->pright[i].pdown) {//���뵱ǰ����p1δ����Ԫ��
					insert(L3, p2->data, p2->i, i);
					p2 = p2->pdown;
				}
			}
		}
		return L3;
	}
	else
		return NULL;
}
void print(LinkedList* L) {
	int i = 0;
	for (i = 0; i < L->n; i++) {
		if (L->pright[i].pdown) {//��ǰ����Ԫ��
			Node* p = L->pright[i].pdown->pdown;
			while (p != L->pright[i].pdown) {
				printf("%d %d %d\n", p->i, i, p->data);
				p = p->pdown;
			}
		}
	}
}
int main() {
	LinkedList* L1 = init(5, 6);
	LinkedList* L2 = init(5, 6);
	LinkedList* L3 = NULL;
	insert(L1, 10, 0, 3);
	insert(L1, 50, 1, 5);
	insert(L2, 20, 0, 3);
	insert(L2, 40, 2, 3);
	insert(L2, 40, 1, 5);
	insert(L2, 40, 3, 3);
	//print(L2);
	L3=add(L1, L2);
	if (L3)
		print(L3);
	else
		printf("���󲻺Ϸ�\n");
	return 0;
}


