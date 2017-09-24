#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
int* visited;
typedef struct AdjNode {
	int index;
	struct AdjNode* next;
}AdjNode;
typedef struct GraphNode {
	char data;
	int number;//记录编号
	int indegree;//记录入度
	AdjNode* firstNode;
}GraphNode;
typedef struct {
	GraphNode graph[MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
Graph* creat() {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	char buffer[100];
	int i = 0;
	FILE* f = fopen("test.txt", "r");
	for (i = 0; i < MAX_GRAPH_SIZE; i++) {
		g->graph[i].firstNode = NULL;
		g->graph[i].indegree = 0;
	}
	g->vexnum = g->edgenum = 0;
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0) {
			g->vexnum = atoi(buffer);
		}
		else if (g->edgenum == 0)
			g->edgenum =atoi(buffer);
		else {
			int i = buffer[0] - '0' - 1, j = buffer[2] - '0' - 1;
			AdjNode* p = (AdjNode*)malloc(sizeof(AdjNode));
			p->index = j;
			g->graph[i].data = 'A' + i;
			g->graph[j].data = 'A' + j;
			g->graph[j].indegree++;
			p->next = g->graph[i].firstNode;
			g->graph[i].firstNode = p;
		}
	}
	fclose(f);
	return g;
}
void getInDegree(Graph* g,int* indegree) {
	int i = 0;
	for (i = 0; i < g->vexnum; i++)
		indegree[i] = g->graph[i].indegree;
}
int topSort(Graph* g) {
	int* indegree = (int*)malloc(sizeof(int)*g->vexnum);
	getInDegree(g, indegree);
	int* s = (int*)malloc(sizeof(int)*g->vexnum);
	int top = -1,i=0,count=0;
	for (i = 0; i < g->vexnum; i++) {//找到入度为0的顶点的集合，加入栈s中
		if (indegree[i] == 0)
			s[++top] = i;
	}
	while (top != -1) {
		int t = s[top--];
		g->graph[t].number = count++;
		AdjNode* p = g->graph[t].firstNode;
		while (p) {
			if (--indegree[p->index] == 0)
				s[++top] = p->index;
			p = p->next;
		}
	}
	return count == g->vexnum;
}
void dfs(Graph* g, int i) {
	visited[i] = 1;
	printf("%c %d\n", g->graph[i].data, g->graph[i].number);
	AdjNode* p = g->graph[i].firstNode;
	while (p) {
		if (!visited[p->index])
			dfs(g, p->index);
		p = p->next;
	}
}
void travel(Graph* g) {
	visited = (int*)malloc(sizeof(int)*g->vexnum);
	memset(visited, 0, sizeof(int)*g->vexnum);
	int i = 0;
	for (i = 0; i < g->vexnum; i++) {
		if (!visited[i])
			dfs(g, i);
	}
}
int main() {
	Graph* g = creat();
	topSort(g);
	travel(g);
}

