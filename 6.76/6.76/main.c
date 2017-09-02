#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	CTreeNode* tree[MAX_TREE_SIZE];
	int r, n;
}CTree;
int spilt(char* s, int low, int high) {
	int i = low, brace = 0;
	if (low == high)
		return low + 1;
	while (s[i] != ',' || brace) {
		if (s[i] == '(')
			brace++;
		if (s[i] == ')')
			brace--;
		i++;
	}
	return i;
}
CTree* init(char* s) {
	int i = 0, len = strlen(s);
	CTree* t = (CTree*)malloc(sizeof(CTree));
	t->r = -1;
	t->n = 0;
	for (i = 0; i < len; i++) {
		if (s[i] >= 'A'&&s[i] <= 'Z') {
			CTreeNode* node = (CTreeNode*)malloc(sizeof(CTreeNode));
			node->data = s[i];
			node->child = NULL;
			t->tree[s[i] - 'A'] = node;
			if (t->r == -1)
				t->r = s[i] - 'A';
			t->n++;
		}
	}
	return t;
}
void creat(CTree* t, char* s, int low, int high) {
	if (low <= high) {
		int i = low + 2;
		ChildPtr* ptail = NULL;
		while (i <= high - 1) {
			int sp = spilt(s, i, high - 1);
			ChildPtr* child = (ChildPtr*)malloc(sizeof(ChildPtr));
			child->i = s[i] - 'A';
			child->next = NULL;
			if (t->tree[s[low] - 'A']->child == NULL) {
				t->tree[s[low] - 'A']->child = child;
				ptail = child;
			}
			else {
				ptail->next = child;
				ptail = child;
			}
			creat(t, s, i, sp - 1);
			i = sp + 1;
		}
	}
}
void printString(CTree* t,int i) {
	printf("%c", t->tree[i]->data);
	ChildPtr* p = t->tree[i]->child;
	if (p) {
		printf("(");
		while (p) {
			printString(t, p->i);
			if (p->next)
				printf(",");
			p = p->next;
		}
		printf(")");
	}
}
int main() {
	char* s = "A(B(E,F),C(G),D)";
	CTree* t = init(s);
	creat(t, s, t->r, strlen(s) - 1);
	printString(t, t->r);
	return 0;
}