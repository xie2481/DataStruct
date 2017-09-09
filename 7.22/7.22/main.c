#include <stdio.h>
#include <stdlib.h>
#define MAX_GRAPH_SIZE 20
int visited[MAX_GRAPH_SIZE];
typedef struct AdjBox {
	int index;
	struct AdjBox* next;
}AdjBox;
typedef struct GraphNode {
	char data;
	struct AdjBox* firstAdj;
}GraphNode;
typedef struct Graph {
	GraphNode graph[MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	Graph* g = (Graph*)malloc(sizeof(Graph));
	char buffer[100];
	int i = 0;
	g->vexnum = g->edgenum = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++) {
		g->graph[i].firstAdj = NULL;
		visited[i] = 0;
	}
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum = buffer[0] - '0';
		else if (g->edgenum == 0)
			g->edgenum = buffer[0] - '0';
		else {
			int i = buffer[0] - '0' - 1, j = buffer[2] - '0' - 1;
			AdjBox* p = (AdjBox*)malloc(sizeof(AdjBox));
			g->graph[i].data = 'A' + i;
			g->graph[j].data = 'A' + j;
			p->index = j;
			p->next = g->graph[i].firstAdj;
			g->graph[i].firstAdj = p;
		}
	}
	fclose(f);
	return g;
}
void dfs(Graph* g, int i,int w,int* isPass) {
	if (!visited[i]) {
		if (i == w)
			*isPass = 1;
	}
	visited[i] = 1;
	AdjBox* p = g->graph[i].firstAdj;
	if (!(*isPass)) {
		while (p) {
			if (!visited[p->index])
				dfs(g, p->index, w, isPass);
			p = p->next;
		}
	}
}
int searchPath(Graph* g,int v,int w) {
	AdjBox* p = g->graph[v - 1].firstAdj;
	int isPass = 0;
	while (p) {
		if (!visited[p->index])
			dfs(g, p->index, w-1, &isPass);
		p = p->next;
	}
	return isPass;
}
int main() {
	Graph* g = creat();
	printf("%d\n", searchPath(g,1, 4));
}