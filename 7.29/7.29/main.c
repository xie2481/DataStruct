#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
int* visited;
int count;
typedef struct {
	int graph[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	char buffer[100];
	int i = 0;
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->edgenum = g->vexnum = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++)
		memset(g->graph[i], 0, sizeof(int)*MAX_GRAPH_SIZE);
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum = buffer[0] - '0';
		else if (g->edgenum == 0)
			g->edgenum = buffer[0] - '0';
		else {
			int i = buffer[0] - '0' - 1, j = buffer[2] - '0' - 1;
			g->graph[i][j] = 1;
		}
	}
	fclose(f);
	return g;
}
void dfs(Graph* g, int i, int w, int k,int l) {
	int j = 0;
	visited[i] = 1;
	l++;
	if (i == w) {
		if (l == k)
			count++;
	}
	for (j = 0; j < g->vexnum; j++) {
		if (g->graph[j] && !visited[j]) {
			dfs(g, j, w, k, l);
			visited[j] = 0;
		}
	}
}
int getAllPath(Graph* g, int v, int w, int k) {
	visited = (int*)malloc(sizeof(int)*g->vexnum);
	memset(visited, 0, sizeof(int)*g->vexnum);
	dfs(g, v - 1, w - 1, k, -1);
	return count;
}
int main() {
	Graph* g = creat();
	printf("%d\n", getAllPath(g, 1, 3, 2));
}