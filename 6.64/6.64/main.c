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
PTree* init() {
	PTree* t = (PTree*)malloc(sizeof(PTree));
	t->r = 0;
	t->n = 10;
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
int getThisNodeDepth(PTree* t, int i) {//得到i结点所在的层次,从1开始
	if (t->nodes[i].parent != -1) {
		return getThisNodeDepth(t, t->nodes[i].parent)+1;
	}
	else
		return 1;
}
int getDepth(PTree* t) {
	int max = 0,i = t->n - 1;
	for (; i >= 0; i--) {
		int temp = getThisNodeDepth(t, i);
		if (max < temp)
			max = temp;
	}
	return max;
}
int main() {
	PTree* t = init();
	creat(t);
	printf("%d\n", getDepth(t));
	return 0;
}