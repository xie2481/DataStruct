#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
	int data;
	struct Node* pright;
	struct Node* pdown;
}Node;
typedef struct {
	struct Node* pright;//存储行数组
	struct Node* pdown;//存储列数组
	int m;//记录列数
	int n;//记录行数
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
		printf("位置有误\n");
		free(node);//当前节点无用
		return;
	}
    //插入行
	if (L->pdown[m].pright == NULL) {//该行没有元素
		L->pdown[m].pright = (Node*)malloc(sizeof(Node));
		L->pdown[m].pright->data = m;//链表头存储位置信息
		L->pdown[m].pright->pright = NULL;
	}
	p = L->pdown[m].pright;
	while (p&&p->pright) {//让p指向该行最后一个元素
		p = p->pright;
	}
	p->pright = node;
	node->pright = L->pdown[m].pright;//构成循环链表
	//插入列
	if (L->pright[n].pdown == NULL) {//该列没有元素
		L->pright[n].pdown = (Node*)malloc(sizeof(Node));
		L->pright[n].pdown->data = n;
		L->pright[n].pdown->pdown = NULL;
	}
	p = L->pright[n].pdown;
	while (p&&p->pdown) {//让p指向该列最后一个元素
		p = p->pdown;
	}
	p->pdown = node;
	node->pdown = L->pright[n].pdown;
}
void print(LinkedList* L) {
	int i = 0;
	for (i = 0; i < L->n; i++) {
		if (L->pright[i].pdown) {//当前列有元素
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
