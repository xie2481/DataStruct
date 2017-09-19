#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
int* visited;
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
Graph* g;
Graph* gt;//gµÄÄæÍ¼
int stack1[100], stack2[100];
int top1 = -1, top2 = -1;
void creat() {
	FILE* f = fopen("test.txt","r");
	char buffer[100];
	int i = 0;
	g = (Graph*)malloc(sizeof(Graph));
	gt = (Graph*)malloc(sizeof(Graph));
	for (i = 0; i < MAX_GRAPH_SIZE; i++) {
		g->graph[i].firstNode = NULL;
		gt->graph[i].firstNode = NULL;
	}
	g->vexnum = gt->vexnum = g->edgenum = gt->edgenum = 0;
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0) {
			g->vexnum = buffer[0] - '0';
			gt->vexnum = buffer[0] - '0';
		}
		else if (g->edgenum == 0) {
			g->edgenum = buffer[0] - '0';
			gt->edgenum = buffer[0] - '0';
		}
		else {
			int i = buffer[0] - '0' - 1, j = buffer[2] - '0' - 1;
			AdjNode* p1 = (AdjNode*)malloc(sizeof(AdjNode));
			AdjNode* p2 = (AdjNode*)malloc(sizeof(AdjNode));
			g->graph[i].data = 'A' + i;
			g->graph[j].data = 'A' + j;
			gt->graph[i].data = 'A' + i;
			gt->graph[j].data = 'A' + j;
			p1->index = j;
			p2->index = i;
			p1->next = g->graph[i].firstNode;
			g->graph[i].firstNode = p1;
			p2->next = gt->graph[j].firstNode;
			gt->graph[j].firstNode = p2;
		}
	}
	fclose(f);
}
void dfs1(int v) {
	visited[v] = 1;
	AdjNode* p = gt->graph[v].firstNode;
	while (p) {
		if (!visited[p->index])
			dfs1(p->index);
		p = p->next;
	}
	stack1[++top1] =v;
}
void dfs2(int v) {
	visited[v] = 1;
	AdjNode* p = g->graph[v].firstNode;
	while (p) {
		if (!visited[p->index])
			dfs2(p->index);
		p = p->next;
	}
	stack2[++top2] =v;
}
int main() {
	int i = 0, cnt = 0;
	creat();
	visited = (int*)malloc(sizeof(int)*g->vexnum);
	memset(visited, 0, sizeof(int)*g->vexnum);
	for (i = 0; i < gt->vexnum; i++) {
		if (!visited[i])
			dfs1(i);
	}
	memset(visited, 0, sizeof(int)*g->vexnum);
	while (top1 >= 0) {
		int t = stack1[top1--];
		if (!visited[t]) {
			dfs2(t);
			cnt++;
			printf("Group %d:", cnt);
			while (top2 >= 0) {
				printf("%c", g->graph[stack2[top2--]].data);
			}
			printf("\n");
		}
	}
	return 0;
}
