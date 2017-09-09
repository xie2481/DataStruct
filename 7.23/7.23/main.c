#include <stdio.h>
#include <stdlib.h>
#define MAX_GRAPH_SIZE 20
typedef struct AdjBox {
	int index;
	struct AdjBox* next;
}AdjBox;
typedef struct GraphNode {
	char data;
	AdjBox* firstAdj;
}GraphNode;
typedef struct {
	GraphNode graph[MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	Graph* g = (Graph*)malloc(sizeof(Graph));
	char buffer[100];
	int i = 0;
	g->edgenum = g->vexnum = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++)
		g->graph[i].firstAdj = NULL;
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum = buffer[0] - '0' - 1;
		else if (g->edgenum == 0)
			g->edgenum = buffer[0] - '0' - 1;
		else {
			int i = buffer[0] - '0' - 1, j = buffer[2] - '0' - 1;
			AdjBox* p = (AdjBox*)malloc(sizeof(AdjBox));
			p->index = j;
			g->graph[i].data = 'A' + i;
			g->graph[j].data = 'A' + j;
			p->next = g->graph[i].firstAdj;
			g->graph[i].firstAdj = p;
		}
	}
	fclose(f);
	return g;
}
int searchPathByBfs(Graph* g,int v,int w) {
	int queue[100];
	int front = 0, rear = -1,isPass=0;
	queue[++rear] = v - 1;
	while (front <= rear) {
		int f = queue[front];
		AdjBox* p = g->graph[f].firstAdj;
		if (f == w - 1) {
			isPass = 1;
			break;
		}
		while (p) {
			queue[++rear] = p->index;
			p = p->next;
		}
		front++;
	}
	return isPass;
}
int main() {
	Graph* g = creat();
	printf("%d\n", searchPathByBfs(g, 1, 4));
}