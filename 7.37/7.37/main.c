#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
typedef struct AdjNode {
	int index;
	struct AdjNode* next;
}AdjNode;
typedef struct GraphNode {
	char data;
	int indegree;
	AdjNode* firstNode;
}GraphNode;
typedef struct {
	GraphNode graph[MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
Graph* create() {
	FILE* f = fopen("test.txt", "r");
	Graph* g = (Graph*)malloc(sizeof(Graph));
	char buffer[100];
	int i = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++) {
		g->graph[i].firstNode = NULL;
		g->graph[i].indegree = 0;
	}
	g->vexnum = g->edgenum = 0;
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum =atoi(buffer);
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
int* getindegree(Graph* g) {
	int* indegree = (int*)malloc(sizeof(int)*g->vexnum);
	int i = 0;
	for (i = 0; i < g->vexnum; i++)
		indegree[i] = g->graph[i].indegree;
	return indegree;
}
int getMaxIndex(int* num, int size) {
	int i = 0,max=INT_MIN,index=0;
	for(i=0;i<size;i++)
		if (max < num[i]) {
			max = num[i];
			index = i;
		}
	return index;
}
int isAdjNode(Graph* g, int i, int j) {
	AdjNode* p = g->graph[i].firstNode;
	while (p) {
		if (p->index == j)
			return 1;
		p = p->next;
	}
	return 0;
}
void getMaxPath(Graph* g) {
	int* indegree = getindegree(g);
	int* stack = (int*)malloc(sizeof(int)*g->vexnum);
	int* dist = (int*)malloc(sizeof(int)*g->vexnum);
	int top = -1;
	int i = 0;
	for (i = 0; i < g->vexnum; i++)
		if (!indegree[i]) {
			stack[++top] = i;
			dist[i] = 0;
		}
		else
			dist[i] = INT_MIN;
	while (top != -1) {
		int j = stack[top--];
		AdjNode* p = g->graph[j].firstNode;
		while (p) {
			if (--indegree[p->index]==0) {
				stack[++top] = p->index;
				if (dist[j] + 1 > dist[p->index]) {
					dist[p->index] = dist[j] + 1;
				}
			}
			p = p->next;
		}
	}
	int start = getMaxIndex(dist, g->vexnum);//得到逆拓扑的初始结点
	stack[++top] = start;
	for (i = 0; i < g->vexnum; i++) {
		if (dist[i] + 1 == dist[start] && isAdjNode(g,i, start)) {
			stack[++top] = i;
			start = i;
			i = -1;
		}
	}
	while (top != -1) {
		printf("%c", g->graph[stack[top--]].data);
	}
}
int main() {
	Graph* g = create();
	getMaxPath(g);
}