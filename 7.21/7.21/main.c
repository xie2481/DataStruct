#include <stdio.h>
#include <stdlib.h>
#define MAX_GRAPH_SIZE 20
int visited[MAX_GRAPH_SIZE];
typedef struct AdjNode {
	int index;
	struct AdjNode* next;
}AdjNode;
typedef struct GraphNode {
	char data;
	AdjNode* adjList;
}GraphNode;
typedef struct Graph {
	GraphNode graph[MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
Graph* creat() {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	FILE* f = fopen("test.txt", "r");
	char buffer[100];
	int i = 0;
	g->edgenum = g->vexnum = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++) {
		g->graph[i].adjList = NULL;
		visited[i] = 0;
	}
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum = buffer[0] - '0';
		else if (g->edgenum == 0)
			g->edgenum = buffer[0] - '0';
		else {
			int i = buffer[0] - '0' - 1, j = buffer[2] - '0' - 1;
			AdjNode* p = (AdjNode*)malloc(sizeof(AdjNode));
			g->graph[i].data = 'A' + i;
			g->graph[j].data = 'A' + j;
			p->index = j;
			p->next = g->graph[i].adjList;
			g->graph[i].adjList = p;
		}
	}
	fclose(f);
	return g;
}
int isTrans(Graph* g) {
	int trans = 1,i=0;
	for (i = 0; i < g->vexnum; i++) {
		AdjNode* p = g->graph[i].adjList;
		while (p) {
			if (p->index != i) {
				AdjNode* pt = g->graph[p->index].adjList;
				while (pt) {
					AdjNode* px = g->graph[i].adjList;
					while (px) {
						if (pt->index == px->index)
							break;
						px = px->next;
					}
					if (px == NULL)
						trans = 0;
					pt = pt->next;
				}
			}
			p = p->next;
		}
	}
	return trans;
}
void dfs(Graph* g,int i) {
	AdjNode* p = g->graph[i].adjList;
	visited[i] = 1;
	printf("%c", g->graph[i].data);
	while (p) {
		if (!visited[p->index])
			dfs(g, p->index);
		p = p->next;
	}
}
void dfstravel(Graph* g) {
	int i = 0;
	for (i = 0; i < g->vexnum; i++) {
		if (!visited[i])
			dfs(g, i);
	}
}
int main() {
	Graph* g = creat();
	printf("%d", isTrans(g));
}