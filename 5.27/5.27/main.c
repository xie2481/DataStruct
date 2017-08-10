//默认插入的元素按行序排列
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
	struct Node* pright;//存储行数组
	struct Node* pdown;//存储列数组
	int m;//记录列数
	int n;//记录行数
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
		printf("位置有误\n");
		free(node);//当前节点无用
		return;
	}
	//插入行
	if (L->pdown[m].pright == NULL) {//该行没有元素
		L->pdown[m].pright = (Node*)malloc(sizeof(Node));
		L->pdown[m].pright->data = m;//链表头存储位置信息
		L->pdown[m].pright->pright = L->pdown[m].pright;
		L->pdown[m].pright->pdown= NULL;
	}
	p = L->pdown[m].pright->pright;
	while (p!=L->pdown[m].pright&&p->pright!= L->pdown[m].pright) {//让p指向该行最后一个元素
		if (p->pdown&&p->pdown->data == n) {
			printf("该元素已存在\n");
			return;
		}
		p = p->pright;
	}
	p->pright = node;
	node->pright = L->pdown[m].pright;//构成循环链表
     //插入列
	if (L->pright[n].pdown == NULL) {//该列没有元素
		L->pright[n].pdown = (Node*)malloc(sizeof(Node));
		L->pright[n].pdown->data = n;
		L->pright[n].pdown->pdown =L->pright[n].pdown;
		L->pright[n].pdown->pright = NULL;
	}
	p = L->pright[n].pdown->pdown;
	while (p!= L->pright[n].pdown&&p->pdown!= L->pright[n].pdown) {//让p指向该列最后一个元素,之前在插入行时已经进行过重复元素的检查
		p = p->pdown;
	}
	p->pdown = node;
	node->pdown = L->pright[n].pdown;
}
LinkedList* add(LinkedList* L1, LinkedList* L2) {
	if (L1->m == L2->m&&L1->n&&L2->n) {//矩阵可加
		int i = 0;
		LinkedList* L3 = init(L1->m,L1->n);
		for (i = 0; i < L1->n; i++) {
			if (L1->pright[i].pdown && L2->pright[i].pdown) {//当前2个矩阵在该列都有非零元
				Node* p1 = L1->pright[i].pdown->pdown,*p2= L2->pright[i].pdown->pdown;
				while (p1 != L1->pright[i].pdown&&p2 !=L2->pright[i].pdown) {
					if (p1->i==p2->i&&p1->data + p2->data) {//处于相同位置的元素
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
				while (p1 != L1->pright[i].pdown) {//插入当前列中p1未插入元素
					insert(L3, p1->data, p1->i, i);
					p1 = p1->pdown;
				}
				while (p2 != L2->pright[i].pdown) {//插入当前列中p1未插入元素
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
		if (L->pright[i].pdown) {//当前列有元素
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
		printf("矩阵不合法\n");
	return 0;
}


