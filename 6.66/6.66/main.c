/*使用书中6.13的树*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_SIZE 100
typedef struct PTNode {
	char data;
	int parent;
}PTNode;
typedef struct {
	PTNode nodes[MAX_TREE_SIZE];
	int r, n;
}PTree;
typedef struct Node {
	int brother;
	struct Node* next;
}Node;
typedef struct CBNode {
	char data;
	struct CBNode* brother;
	struct CBNode* firstChild;
}CBNode;
typedef struct CBTree {
	CBNode tree[MAX_TREE_SIZE];
	int r, n;
}CBTree;
PTree* init() {
	PTree* t = (PTree*)malloc(sizeof(PTree));
	t->r = 0;
	t->n = 10;
	return t;
}
CBTree* initCBTree(int r, int n) {
	CBTree* t = (CBTree*)malloc(sizeof(CBTree));
	int i = 0;
	t->n = n;
	t->r = r;
	for (i = r; i < t->n; i++)
		t->tree[i].firstChild = t->tree[i].brother = NULL;
	return t;
}
void creat(PTree* t) {
	int i = 0;
	t->nodes[0].data = 'R';
	t->nodes[0].parent = -1;
	for (i = 1; i < t->n - 1; i++) {
		t->nodes[i].data = 'A' + i - 1;
	}
	t->nodes[t->n - 1].data = 'K';
	t->nodes[1].parent = t->nodes[2].parent = t->nodes[3].parent = 0;//R--->A,B,C
	t->nodes[4].parent = t->nodes[5].parent = 1;//A--->D,E
	t->nodes[6].parent = 3;//C--->F
	t->nodes[7].parent = t->nodes[8].parent = t->nodes[9].parent = 6;//F--->G,H,K
}
void insert(CBNode* u,CBNode* v) {//将结点v作为结点u的孩子插入
	if (u->firstChild == NULL) {
		u->firstChild = v;
		v->brother = NULL;
	}
	else {
		v->brother = u->firstChild;
		u->firstChild = v;
	}
}
CBTree* creatCBTreeByPTree(PTree* t) {
	CBTree* tree = initCBTree(t->r, t->n);
	int i = 0;
	for (i = 0; i < t->n; i++) {
		tree->tree[i].data = t->nodes[i].data;
		if (t->nodes[i].parent != -1)
			insert(&tree->tree[t->nodes[i].parent], &tree->tree[i]);
	}
	return tree;
}
void printCBTree(CBNode* t) {
	if (t) {
		printf("%c", t->data);
		printCBTree(t->firstChild);
		printCBTree(t->brother);
	}
}
int main() {
	PTree* t = init();
	CBTree* p = NULL;
	creat(t);
	p = creatCBTreeByPTree(t);
	printCBTree(&p->tree[p->r]);
	printf("\n");
	return 0;
}