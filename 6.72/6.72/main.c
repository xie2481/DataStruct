#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_SIZE 100
typedef struct ChildPtr {
	int i;
	struct ChildPtr* next;
}ChildPtr;
typedef struct CTreeNode {
	char data;
	struct ChildPtr* child;
}CTreeNode;
typedef struct {
	CTreeNode* t[MAX_TREE_SIZE];
	int r, n;
}CTree;
void insert(CTree* t,int i,int j) {
	if (t->t[i]->child == NULL) {
		t->t[i]->child = (ChildPtr*)malloc(sizeof(ChildPtr));
		t->t[i]->child->i = j;
		t->t[i]->child->next = NULL;
	}
	else {
		ChildPtr* node = (ChildPtr*)malloc(sizeof(ChildPtr)),*ptail=t->t[i]->child;
		node->i = j;
		node->next = NULL;
		while (ptail->next)
			ptail = ptail->next;
		ptail->next = node;
	}
}
CTree* creat() {
	CTree* root = (CTree*)malloc(sizeof(CTree));
	int i = 0;
	root->r = 0;
	root->n = 7;
	for (i = root->r; i < root->n; i++) {
		CTreeNode* node = (CTreeNode*)malloc(sizeof(CTreeNode));
		node->data = 'A' + i;
		node->child = NULL;
		root->t[i] = node;
	}
	insert(root,0,1);//A-->B
	insert(root,0,2);//A-->C
	insert(root,0,3);//A-->D
	insert(root,1,4);//B-->E
	insert(root,1,5);//B-->F
	insert(root,2,6);//C-->G
	return root;
}
void print(CTree* t,int space,int r) {
	int i = 0;
	ChildPtr* ptemp =t->t[r]->child;
	for (i = 0; i < space; i++)
		printf(" ");
	printf("%c\n",t->t[r]->data);
	while (ptemp) {
		print(t, space + 1, ptemp->i);
		ptemp = ptemp->next;
	}
	
}
int main() {
	CTree* t = creat();
	print(t,0,t->r);
}