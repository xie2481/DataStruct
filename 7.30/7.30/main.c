/*http://www.docin.com/p-339517781.html*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#define MAX_GRAPH_SIZE 20
int* visited;
char* path;
LinkedList* L;
int currentPathLength;
typedef struct AdjNode {
	int index;
	struct AdjNode* next;
}AdjNode;
typedef struct {
	char data;
	AdjNode* firstNode;
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
			AdjNode* p = (AdjNode*)malloc(sizeof(AdjNode));
			p->index = j;
			g->graph[i].data = 'A' + i;
			g->graph[j].data = 'A' + j;
			p->next = g->graph[i].firstNode;
			g->graph[i].firstNode = p;
		}
	}
	fclose(f);
	return g;
}
void dfs(Graph* g, int i) {
	visited[i] = 1;
	AdjNode* p = g->graph[i].firstNode;
	while (p) {
		if (!visited[p->index] && path[0] < g->graph[p->index].data) {
			currentPathLength++;
			path[currentPathLength] = g->graph[p->index].data;
			dfs(g, p->index);
		}
		if (path[0] == g->graph[p->index].data) {
			path[currentPathLength + 1] = '\0';
			insert(L, path);
		}
		p = p->next;
	}
	visited[path[currentPathLength]] = 0;
	path[0] = '\0';
	currentPathLength--;
}
void getAllCyclePath(Graph* g) {
	int i = 0;
	visited = (int*)malloc(sizeof(int)*g->vexnum);
	path = (char*)malloc(sizeof(char)*g->vexnum);
	memset(visited, 0, sizeof(int)*g->vexnum);
	L = init();
	for (i = 0; i < g->vexnum; i++) {
		path[0] = g->graph[i].data;
		currentPathLength =0;
		dfs(g, i);
	}
}
int main() {
	Graph* g = creat();
	getAllCyclePath(g);
	printList(L);
	return 0;
}