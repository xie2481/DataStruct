#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
//设带有运算符的弧尾一定是数字
typedef struct AdjNode {
	int index;
	struct AdjNode* next;
}AdjNode;
typedef struct GraphNode {
	char data;
	int indegree;
	AdjNode* firstNode;
	int i;//每个顶点的标号
}GraphNode;
typedef struct Graph {
	GraphNode graph[MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	Graph* g = (Graph*)malloc(sizeof(Graph));
	char buffer[100];
	int i = 0;
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
			int i = buffer[0] - '0' - 1, j = buffer[4] - '0' - 1;
			AdjNode* p = (AdjNode*)malloc(sizeof(AdjNode));
			p->index = j;
			g->graph[i].data = buffer[2];
			g->graph[j].data = buffer[6];
			g->graph[i].i = i;
			g->graph[j].i = j;
			g->graph[j].indegree++;
			p->next = g->graph[i].firstNode;
			g->graph[i].firstNode = p;
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
	int* stack = (int*)malloc(sizeof(int)*g->vexnum);
	int* op = (int*)malloc(sizeof(int)*g->vexnum);
	int topop = -1;
	int top = -1;
	int i = 0;
	for (i = 0; i < g->vexnum; i++)
		if (!indegree[i])
			stack[++top] = i;
	int count = 0;//记录打印数字的个数
	while (top != -1) {
		int i = stack[top--];
		if (g->graph[i].data >= '0'&&g->graph[i].data <= '9') {
			printf("%c", g->graph[i].data);
			count++;
			if (count == 2) {
				printf("%c", g->graph[op[topop--]].data);
				count = 0;
			}
		}
		else {
			count = 0;
			op[++topop] = i;
		}
		AdjNode* p = g->graph[i].firstNode;
		while (p) {
			if (--indegree[p->index] == 0)
				stack[++top] = p->index;
			p = p->next;
		}
	}
	while (topop != -1)
		printf("%c", g->graph[op[topop--]].data);
}
int main() {
	Graph* g = creat();
	topSort(g);
	return 0;
}