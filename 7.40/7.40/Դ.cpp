#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
typedef struct AdjNode {
	int index;
	struct AdjNode* next;
}AdjNode;
typedef struct {
	union val {
		int data;
		char op;
	}val;
	int i;
	int indegree;
	AdjNode* firstNode;
}GraphNode;
typedef struct {
	GraphNode graph[MAX_GRAPH_SIZE];
	int vexnum,edgenum;
}Graph;
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	Graph* g = (Graph*)malloc(sizeof(Graph));
	char buffer[100];
	int i = 0;
	g->vexnum = g->edgenum = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++)
		g->graph[i].firstNode = NULL,g->graph[i].indegree=0;
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum = buffer[0] - '0';
		else if (g->edgenum == 0)
			g->edgenum = buffer[0] - '0';
		else {
			int i = buffer[0] - '0' - 1, j = buffer[4] - '0' - 1;
			AdjNode* p = (AdjNode*)malloc(sizeof(AdjNode));
			p->index = j;
			if (buffer[2] >= '0'&&buffer[2] <= '9')
				g->graph[i].val.data = buffer[2] - '0';
			else
				g->graph[i].val.op = buffer[2];

			if (buffer[6] >= '0'&&buffer[6] <= '9')
				g->graph[j].val.data = buffer[6] - '0';
			else
				g->graph[j].val.op = buffer[6];

			g->graph[j].indegree++;
			p->next = g->graph[i].firstNode;
			g->graph[i].firstNode = p;
		}
	}
	fclose(f);
	return g;
}
int* getIndegree(Graph* g) {
	int i = 0;
	int* indegree = (int*)malloc(sizeof(int)*g->vexnum);
	for (i = 0; i < g->vexnum; i++)
		indegree[i] = g->graph[i].indegree;
	return indegree;
}
int calc(int a, int b, char op) {
	switch (op) {
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*':
		return a*b;
		break;
	case '/':
		return a / b;
	}
	return 0;
}
int topSort(Graph* g) {
	int* indegree = getIndegree(g);
	int* stack = (int*)malloc(sizeof(int)*g->vexnum);
	int* num = (int*)malloc(sizeof(int)*g->vexnum);
	char* op = (char*)malloc(sizeof(char)*g->vexnum);
	int top = -1,topop=-1;
	int topnum = -1;
	int i = 0;
	for (i = 0; i < g->vexnum; i++)
		if (!indegree[i])
			stack[++top] = i;
	int count = 0;
	while (top != -1) {
		int i = stack[top--];
		if (g->graph[i].val.data >= 0 && g->graph[i].val.data <= 9) {
			num[++topnum] = g->graph[i].val.data;
			count++;
			if (count == 2) {
				int a = num[topnum--];
				int b = num[topnum--];
				num[++topnum]=calc(b, a, op[topop--]);
				count = 0;
			}
		}
		else {
			count = 0;
			op[++topop] = g->graph[i].val.op;
		}
		AdjNode* p = g->graph[i].firstNode;
		while (p) {
			if (--indegree[p->index] == 0)
				stack[++top] = p->index;
			p = p->next;
		}
	}
	while (topop != -1) {
		int a = num[topnum--];
		int b = num[topnum--];
		num[++topnum] = calc(b, a, op[topop--]);
	}
	return num[0];
}
int main() {
	Graph* g = creat();
	printf("%d\n", topSort(g));
	return 0;
}
