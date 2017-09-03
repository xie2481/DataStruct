#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
int visited[MAX_VERTEX_NUM];
typedef struct {
	int g[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum, arcnum;
}Graph;
Graph* creat() {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	int i = 0, j = 0;
	FILE* f = fopen("test.txt", "r");
	char buffer[100];
	memset(visited, 0, sizeof(int)*MAX_VERTEX_NUM);
	g->vexnum = g->arcnum = 0;
	for (i = 0; i < MAX_VERTEX_NUM; i++)
		for (j = 0; j < MAX_VERTEX_NUM; j++)
			g->g[i][j] = 0;
	while (fgets(buffer, 100, f)) {
		if (!g->vexnum)
			g->vexnum = buffer[0] - '0';
		else if (!g->arcnum)
			g->arcnum = buffer[0] - '0';
		else if (buffer[0] != '0') {
			int index1 = buffer[0] - '0' - 1, index2 = buffer[2] - '0' - 1;
			g->g[index1][index2] = 1;
		}
		else
			break;
	}
	fclose(f);
	return g;
}
void InsertVex(Graph* g, int v) {
	g->vexnum++;
}
void InsertArc(Graph* g, int v, int w) {
	g->g[v][w] = 1;
}
DeleteVex(Graph* g, int v) {
	int i = 0,j=0;
	for(i=0;i<g->vexnum;i++)
		for (j = 0; j < g->vexnum; j++) {
			if (i == v || j == v) {
				g->g[i][j] = 0;
				g->arcnum--;
			}
		}
	g->vexnum--;
}
DeleteArc(Graph* g, int v, int w) {
	g->g[v][w] = 0;
}
void dfs(Graph*g, int v) {
	int w = 0;
	visited[v] = 1;
	printf("%d", v);
	for (w = 0; w < g->vexnum; w++)
		if (g->g[v][w] && !visited[w])
			dfs(g, w);
}
void dfstravel(Graph* g) {
	int i = 0;
	for (i = 0; i < g->vexnum; i++)
		if (!visited[i])
			dfs(g, i);
}
int main() {
	Graph* g = creat();
	dfstravel(g);
	return 0;
}