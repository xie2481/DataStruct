#include <stdio.h>
#include <stdlib.h>
typedef struct Tree {
	char data;
	struct Tree* child;
	struct Tree* brother;
}Tree;
void insert(Tree* par, Tree* node) {
	if (par->child == NULL)
		par->child = node;
	else {
		node->brother = par->child->brother;
		par->child->brother = node;
	}
}
int getThisNodeDegree(Tree* node) {
	if (node->child) {
		int total = 0;
		Tree* p = node->child;
		while (p) {
			total++;
			p = p->brother;
		}
		return total;
	}
	else
		return 0;
}
int getTreeDegree(Tree* node) {
	int i = 0, max = 0;
	for (i = 0; i < 10; i++) {
		int temp = getThisNodeDegree(&node[i]);
		if (temp > max)
			max = temp;
	}
	return max;
}
int main() {
	//测试用例为书上的6.13
	Tree node[10];
	int i = 0;
	node[0].data = 'R';
	node[0].child = node[0].brother = NULL;
	for (i = 1; i < 9; i++) {
		node[i].data = 'A' + i - 1;
		node[i].child = node[i].brother = NULL;
	}
	node[9].data = 'K';
	node[9].brother = node[9].child = NULL;
	insert(&node[0], &node[1]);//R--->A
	insert(&node[0], &node[2]);//R--->B
	insert(&node[0], &node[3]);//R--->C
	insert(&node[1], &node[4]);//A--->D
	insert(&node[1], &node[5]);//A--->E
	insert(&node[3], &node[6]);//C--->F
	insert(&node[6], &node[7]);//F--->G
	insert(&node[6], &node[8]);//F--->H
	insert(&node[6], &node[9]);//F--->K
	printf("%d\n", getTreeDegree(&node[0]));
	return 0;
}