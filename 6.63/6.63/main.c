/*创建的树为书6.13的树*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_SIZE 100
typedef struct CTNode {
	int child;//记录孩子结点的序号
	struct CTNode* next;
}ChildPtr;
typedef struct {
	char data;
	ChildPtr* firstChild;
}CTBox;
typedef struct {
	CTBox nodes[MAX_TREE_SIZE];
	int n, r;//结点数和根的位置
}CTree;
CTree* init() {
	CTree* t = (CTree*)malloc(sizeof(CTree));
	int i = 0;
	t->n = 10;
	t->r = 0;
	t->nodes[0].data = 'R';
	t->nodes[0].firstChild = NULL;
	for (i = 1; i < 9; i++) {
		t->nodes[i].data = 'A' + i - 1;
		t->nodes[i].firstChild = NULL;
	}
	t->nodes[9].data = 'K';
	t->nodes[9].firstChild = NULL;
	return t;
}
void insert(CTBox* node, int i) {//序号为i的孩子
	ChildPtr* child = (ChildPtr*)malloc(sizeof(ChildPtr));
	child->child = i;
	child->next = NULL;
	if (node->firstChild == NULL)
		node->firstChild = child;
	else {
		child->next = node->firstChild;
		node->firstChild = child;
	}
}
void creat(CTree* t) {
	insert(&t->nodes[0], 1);//R--->A
	insert(&t->nodes[0], 2);//R--->B
	insert(&t->nodes[0], 3);//R--->C
	insert(&t->nodes[1], 4);//A--->D
	insert(&t->nodes[1], 5);//A--->E
	insert(&t->nodes[3], 6);//C--->F
	insert(&t->nodes[6], 7);//F--->G
	insert(&t->nodes[6], 8);//F--->H
	insert(&t->nodes[6], 9);//F--->K
}
int getDepth(CTree* t,int i) {//结点序号为i的树的高度
	if (t->nodes[i].firstChild) {
		ChildPtr* p = t->nodes[i].firstChild;
		int max = 0;
		while (p) {
			int temp = getDepth(t, p->child);
			if (temp > max)
				max = temp;
			p = p->next;
		}
		return max + 1;
	}
	else
		return 1;
}
int main() {
	CTree* t = init();
	creat(t);
	printf("%d\n", getDepth(t,t->r));
	return 0;
}