#include <stdio.h>
#include <stdlib.h>
#define MAX_GRAPH_SIZE 20
int* visited;
int length;
typedef struct AdjBox {
	int i;
	struct AdjBox* next;
}AdjBox;
typedef struct {
	char data;
	AdjBox* firstEdge;
}GraphNode;
typedef struct Graph {
	GraphNode graph[MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	char buffer[100];
	int i = 0;
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->vexnum = g->edgenum = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++)
		g->graph[i].firstEdge = NULL;
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum = buffer[0] - '0';
		else if (g->edgenum == 0)
			g->edgenum = buffer[0] - '0';
		else {
			int i = buffer[0] - '0' - 1, j = buffer[2] - '0' - 1;
			AdjBox* p = (AdjBox*)malloc(sizeof(AdjBox));
			p->i = j;
			p->next = g->graph[i].firstEdge;
			g->graph[i].data = 'A' + i;
			g->graph[j].data = 'A' + j;
			g->graph[i].firstEdge = p;
		}
	}
	fclose(f);
	return g;
}
void dfs(Graph* g,int i,int w,int k,int l) {
	visited[i] = 1;
	l++;
	if (i == w) {
		if (l == k)
			length = l;
	}
	AdjBox* p = g->graph[i].firstEdge;
	if (length != k) {
		while (p) {
			if (!visited[p->i]) {
				dfs(g, p->i, w, k, l);
				visited[p->i] = 0;
			}
			p = p->next;
		}
	}
}
int isHavePath(Graph* g, int v, int w,int k) {//查询结点v->w之间是否存在一条长度为k的路径
	visited = (int*)malloc(sizeof(int)*g->vexnum);
	memset(visited, 0, sizeof(int)*g->vexnum);
	length = 0;
	dfs(g, v - 1, w-1, k, -1);
	return length == k;
}
int main() {
	Graph* g = creat();
	printf("%d\n", isHavePath(g, 1, 3, 3));
}