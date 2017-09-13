#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
int* visited;
typedef struct AdjBox {
	int index;
	struct AdjBox* next;
}AdjBox;
typedef struct {
	char data;
	AdjBox* firstNode;
}GraphNode;
typedef struct {
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
		g->graph[i].firstNode = NULL;
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
			p->next = g->graph[i].firstNode;
			g->graph[i].firstNode = p;
		}
	}
	fclose(f);
	return g;
}
void dfs(Graph* g, int i,int w,int* path,int length) {
	visited[i] = 1;
	path[length++] = g->graph[i].data;
	if (i ==w) {
		int j = 0;
		for (j = 0; j < length; j++)
			printf("%c ",path[j] );
	}
	AdjBox* p = g->graph[i].firstNode;
	while (p) {
		if (!visited[p->index]) {
			dfs(g, p->index, w,path,length);
			visited[p->index] = 0;
		}
		p = p->next;
	}
}
void printAllPath(Graph* g, int v, int w) {
	char* path = (int*)malloc(sizeof(char)*g->vexnum);
	visited = (int*)malloc(sizeof(int)*g->vexnum);
	memset(visited, 0, sizeof(int)*g->vexnum);
	dfs(g, v - 1, w - 1,path,0);
}
int main() {
	Graph* g = creat();
	printAllPath(g, 1, 8);
}