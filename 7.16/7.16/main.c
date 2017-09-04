#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 100
int visited[MAX_GRAPH_SIZE];
typedef struct ArcNode {
	int i;
	struct ArcNode* next;
}ArcNode;
typedef struct VNode {
	char data;
	ArcNode* firstArc;
}VNode;
typedef struct Graph {
	VNode graph[MAX_GRAPH_SIZE];
	int vertexnum, arcnum;
}Graph;
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	Graph* g = (Graph*)malloc(sizeof(Graph));
	char buffer[100];
	int i = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++) {
		g->graph[i].firstArc = NULL;
		visited[i] = 0;
	}
	g->vertexnum = g->arcnum = 0;
	while (fgets(buffer, 100, f)) {
		if (!g->vertexnum)
			g->vertexnum = buffer[0] - '0';
		else if (!g->arcnum)
			g->arcnum = buffer[0] - '0';
		else if (buffer[0] != '^') {
			int index1 = buffer[0] - '0' - 1;
			int index2 = buffer[2] - '0' - 1;
			ArcNode* node = (ArcNode*)malloc(sizeof(ArcNode));
			g->graph[index1].data = 'A' + index1;
			g->graph[index2].data = 'A' + index2;
			node->i = index2;
			node->next = NULL;
			if (g->graph[index1].firstArc == NULL)
				g->graph[index1].firstArc = node;
			else {
				node->next = g->graph[index1].firstArc;
				g->graph[index1].firstArc = node;
			}
		}
		else
			break;
	}
	fclose(f);
	return g;
}
void InsertVex(Graph* g, int v) {
	g->graph[g->vertexnum].data = 'A' + v - 1;
	g->graph[g->vertexnum].firstArc = NULL;
	g->vertexnum++;
}
void InsertArc(Graph* g, int v, int w) {
	if (v <= g->vertexnum&&w <= g->vertexnum) {
		ArcNode* node = (ArcNode*)malloc(sizeof(ArcNode));
		node->i = w - 1;
		if (g->graph[v - 1].firstArc) {
			node->next = g->graph[v - 1].firstArc;
			g->graph[v - 1].firstArc = node;
		}
		else
			g->graph[v - 1].firstArc = node;
	}
	g->arcnum++;
}
void DeleteNode(Graph* g, int w,int v) {
	if (g->graph[w].firstArc&&g->graph[w].firstArc->i == v) {
		ArcNode* t = g->graph[w].firstArc->next;
		free(g->graph[w].firstArc);
		g->graph[w].firstArc = t;
	}
	else if(g->graph[w].firstArc){
		ArcNode* pre = g->graph[w].firstArc;
		ArcNode* p = g->graph[w].firstArc->next;
		while (p) {
			if (p->i == v) {
				pre->next = p->next;
				free(p);
				g->arcnum--;
				break;
			}
			p = p->next;
			pre = pre->next;
		}
	}
}
void DeleteVex(Graph* g, int v) {
	int i = 0;
	for (i = 0; i < g->vertexnum; i++) {
		if (i == v - 1)
			continue;
		DeleteNode(g, i, v-1);
	}
	ArcNode* node = g->graph[v - 1].firstArc;
	while (node) {
		g->arcnum--;
		node = node->next;
	}
	free(g->graph[v - 1].firstArc);
	g->graph[v - 1].firstArc = NULL;
	for (i = v; i < g->vertexnum; i++)
		g->graph[i - 1] = g->graph[i];
	g->vertexnum--;
	for (i = 0; i < g->vertexnum; i++) {
		ArcNode* p = g->graph[i].firstArc;
		while (p) {
			if (p->i > v - 1)
				p->i--;
			p = p->next;
		}
	}
}
void DeleteArc(Graph* g, int v, int w) {
	DeleteNode(g, v, w);
}
void dfs(Graph* g, int v) {
	ArcNode* node = g->graph[v].firstArc;
	visited[v] = 1;
	printf("%c", g->graph[v].data);
	while (node) {
		if (!visited[node->i])
			dfs(g, node->i);
		node = node->next;
	}
}
void dfstravel(Graph* g) {
	int i = 0;
	for (i = 0; i < g->vertexnum; i++) {
		if (!visited[i])
			dfs(g, i);
	}
	memset(visited, 0, sizeof(int)*MAX_GRAPH_SIZE);
}
int main() {
	Graph* g = creat();
	InsertVex(g, 5);
	InsertArc(g, 1, 5);
	DeleteVex(g, 3);
	printf("%d\n", g->arcnum);
	dfstravel(g);
}