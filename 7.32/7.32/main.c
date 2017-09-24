#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
typedef struct {
	int adjvex[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
typedef struct TreeNode {
	char data;
	struct TreeNode* brother;
	struct TreeNode* child;
}TreeNode;
typedef struct {
	TreeNode* tree;
	int vexnum;
}Tree;
typedef struct {
	int lowcost;
	int adjvex;
}CloseEdge;
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	char buffer[100];
	int i = 0,j=0;
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->vexnum = g->edgenum = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++)
		for (j = 0; j < MAX_GRAPH_SIZE; j++) {
			g->adjvex[i][j] = INT_MAX;
		}
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0) {
			g->vexnum = buffer[0] - '0';
		}
		else if (g->edgenum == 0) {
			g->edgenum = buffer[0] - '0';
		}
		else {
			int i = buffer[0] - '0' - 1, j = buffer[2] - '0' - 1, w = buffer[4] - '0';
			g->adjvex[i][j] = g->adjvex[j][i] = w;
		}
	}
	fclose(f);
	return g;
}
int minmum(CloseEdge* closeEdge, int size) {
	int i = 0,min=INT_MAX,index=0;
	for(i=0;i<size;i++)
		if (closeEdge[i].lowcost && closeEdge[i].lowcost<min) {
			min = closeEdge[i].lowcost;
			index = i;
		}
	return index;
}
void insert(TreeNode* p, TreeNode* q) {
	if (p->child == NULL)
		p->child = q;
	else {
		q->brother = p->child->brother;
		p->child->brother = q;
	}
}
Tree* getMinSpanTree(Graph* g,int u) {//从第u个顶点开始构造最小生成树
	Tree* t = (Tree*)malloc(sizeof(Tree));
	int i = 0,j=0;
	CloseEdge* closeedge = (CloseEdge*)malloc(sizeof(CloseEdge)*g->vexnum);
	t->tree = (TreeNode*)malloc(sizeof(TreeNode)*g->vexnum);
	for (i = 0; i < g->vexnum; i++) {
		t->tree[i].data = 'A' + i;
		t->tree[i].brother = t->tree[i].child = NULL;
	}
	for (i = 0; i < g->vexnum; i++) {
		if (i != u) {
			closeedge[i].adjvex = u;
			closeedge[i].lowcost = g->adjvex[u][i];
		}
	}
	closeedge[u].lowcost = 0;//将u加入集合当中;
	for (i = 0; i < g->vexnum; i++) {
		int k = minmum(closeedge, g->vexnum);
		closeedge[k].lowcost = 0;
		if (k != u) {
			insert(&t->tree[closeedge[k].adjvex], &t->tree[k]);
			for (j = 0; j < g->vexnum; j++) {
				if (g->adjvex[k][j] < closeedge[j].lowcost) {
					closeedge[j].lowcost = g->adjvex[k][j];
					closeedge[j].adjvex = k;
				}
			}
		} 
	}
	return t;
}
void dfsTree(TreeNode* t) {
	if (t) {
		TreeNode* p = t->brother;
		printf("%c", t->data);
		dfsTree(t->child);
		dfsTree(t->brother);
	}
}
int main() {
	Graph* g = creat();
	Tree* t = getMinSpanTree(g, 0);
	dfsTree(&t->tree[0]);
}
