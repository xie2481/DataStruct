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
	int indegree;
	int mpl;
	AdjNode* firstNode;
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
		g->graph[i].mpl = 0;
	}
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum = buffer[0] - '0';
		else if (g->edgenum == 0)
			g->edgenum =atoi(buffer);
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
	int i =0;
	for (i = 0; i < g->vexnum; i++)
		indegree[i] = g->graph[i].indegree;
	return indegree;
}
void getAllLongestPath(Graph* g) {
	int* indegree = getIndegree(g);
	int* stack = (int*)malloc(sizeof(int)*g->vexnum);
	int* list = (int*)malloc(sizeof(int)*g->vexnum);
	int k = 0;
	int top = -1;
	int i = 0;
	for (i = 0; i < g->vexnum; i++)
		if (!indegree[i])
			stack[++top] = i;
	while (top != -1) {
		int j = stack[top--];
		list[k++] = j;
		AdjNode* p = g->graph[j].firstNode;
		int flag = 0;
		while (p) {
			if (--indegree[p->index] == 0) {
				stack[++top] = p->index;
				flag = 1;
			}
			p = p->next;
		}
		if (flag) {
			int t = 0;
			for (t = 0; t < k; t++) {//找出多个顶点对应一个顶点的情况(此处包含一对一的情况)
				AdjNode* p = g->graph[list[t]].firstNode;
				while (p) {
					if (p->index == stack[top]&&g->graph[list[t]].mpl==0)//判断0是为了防止重复增加路径长度
						g->graph[list[t]].mpl++;
					p = p->next;
				}
			}
			//更新所有顶点的mpl
			for (t =k-1; t>=0; t--) {
				AdjNode* p = g->graph[list[t]].firstNode;
				while (p) {
					if (g->graph[list[t]].mpl < g->graph[p->index].mpl + 1)
						g->graph[list[t]].mpl = g->graph[p->index].mpl + 1;
					p = p->next;
				}
			}
		}
	}
}
void dfs(Graph* g, int i) {
	visited[i] = 1;
	printf("%c %d\n", g->graph[i].data, g->graph[i].mpl);
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
	getAllLongestPath(g);
	travel(g);
	return 0;
}