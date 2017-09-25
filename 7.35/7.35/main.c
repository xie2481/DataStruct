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
	int indegree;//记录当前顶点的入度
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
	for (i = 0; i < MAX_GRAPH_SIZE; i++) {
		g->graph[i].firstNode = NULL;
		g->graph[i].indegree = 0;
	}
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
char getRoot(Graph* g) {
	int* indegree = getIndegree(g);
	int* stack = (int*)malloc(sizeof(int)*g->vexnum);
	int top = -1,i=0;
	for (i = 0; i < g->vexnum; i++) {//找到入度为0的顶点集
		if (indegree[i] == 0)
			stack[++top] = i;
	}
	if (top == 0) {//此时可能存在根
		char root = g->graph[stack[0]].data;
		int count = 0;
		while (top != -1) {
			int k = stack[top--];
			count++;
			AdjNode* p = g->graph[k].firstNode;
			while (p) {
				if (--indegree[p->index] == 0)
					stack[++top] = p->index;
				p = p->next;
			}
		}
		if (count == g->vexnum)
			return root;
		else
			return 0;
	}
	else
		return 0;
}
int main() {
	Graph* g = creat();
	char root = getRoot(g);
	if (root != 0)
		printf("%c\n", root);
	else
		printf("不存在根\n");
}