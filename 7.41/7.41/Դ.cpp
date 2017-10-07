#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
typedef struct AdjNode {
	int index;
	struct AdjNode* next;
	int weight;//´æ´¢±ßµÄÈ¨Öµ
}AdjNode;
typedef struct {
	char data;
	AdjNode* firstnodeOut;
	AdjNode* firstnodeIn;
	int indegree;
}GraphNode;
typedef struct {
	GraphNode graph[MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
int getWeight(char* s, int i) {
	int len = strlen(s);
	int w = 0;
	while (i < len&&s[i]>='0'&&s[i]<='9') {
		w *= 10;
		w += s[i] - '0';
		i++;
	}
	return w;
}
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	Graph* g = (Graph*)malloc(sizeof(Graph));
	char buffer[100];
	int i = 0;
	g->vexnum = 0, g->edgenum = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++) {
		g->graph[i].firstnodeOut = NULL;
		g->graph[i].indegree = 0;
		g->graph[i].firstnodeIn = NULL;
	}
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum = buffer[0] - '0';
		else if (g->edgenum == 0)
			g->edgenum = buffer[0] - '0';
		else {
			int i = buffer[0] - '0' - 1, j = buffer[2] - '0'-1,weight=getWeight(buffer,4);
			AdjNode* p = (AdjNode*)malloc(sizeof(AdjNode));
			AdjNode* p1 = (AdjNode*)malloc(sizeof(AdjNode));
			p->index = j;
			p->weight = weight;
			p1->index = i;
			p1->weight = weight;
			p->next = g->graph[i].firstnodeOut;
			g->graph[i].firstnodeOut = p;
			p1->next = g->graph[j].firstnodeIn;
			g->graph[j].firstnodeIn = p1;
			g->graph[j].indegree++;
		}
	}
	fclose(f);
	return g;
}
int* getIndegree(Graph* g) {
	int* indegree = (int*)malloc(sizeof(int)*g->vexnum);
	int i = 0;
	for (i = 0; i < g->vexnum; i++)
		indegree[i] = g->graph[i].indegree;
	return indegree;
}
void topSort(Graph* g) {
	int* indegree = getIndegree(g);
	int* dist = (int*)malloc(sizeof(int)*g->vexnum);
	int* path = (int*)malloc(sizeof(int)*g->vexnum);
	int* stack = (int*)malloc(sizeof(int)*g->vexnum);
	int top = -1,i=0,maxi=0,max=0;
	memset(dist, 0, sizeof(int)*g->vexnum);
	for (i = 0; i < g->vexnum; i++)
		if (!indegree[i])
			stack[++top] = i;
	while (top != -1) {
		int k = stack[top--];
		AdjNode* p = g->graph[k].firstnodeOut;
		while (p) {
			if (--indegree[p->index] == 0) {
				stack[++top] = p->index;
				if (dist[p->index] <= dist[k] + p->weight)
					dist[p->index] = dist[k] + p->weight;
			}
			p = p->next;
		}
	}
	for (i = 0; i < g->vexnum; i++)
		if (max < dist[i]) max = dist[i], maxi = i;
	i = 0;
	path[i] = maxi;
	while (1) {
		if (dist[path[i]] == 0)
			break;
		AdjNode* p = g->graph[path[i]].firstnodeIn;
		while (p) {
			if (dist[path[i]] == dist[p->index] + p->weight) {
				path[++i] = p->index;
				break;
			}
			p = p->next;
		}
	}
	while (i >= 0) {
		printf("%d\t", path[i--] + 1);
	}
}
int main() {
	Graph* g = creat();
	topSort(g);
}
