#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
typedef struct {
	char graph[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	Graph* g = (Graph*)malloc(sizeof(Graph));
	char buffer[100];
	int i = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++)
		memset(g->graph[i], 0, sizeof(char)*MAX_GRAPH_SIZE);
	g->vexnum = g->edgenum = 0;
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum = buffer[0] - '0';
		else if (g->edgenum == 0)
			g->edgenum = buffer[0] - '0';
		else {
			int i = buffer[0] - '0' - 1, j = buffer[2] - '0' - 1;
			g->graph[i][j] = 1;
		}
	}
	fclose(f);
	return g;
}
void dfsByStack(Graph* g) {//参考第六章的栈递推遍历树
	char stack[100];
	int top = -1;
	char visited[MAX_GRAPH_SIZE];
	memset(visited, 0, sizeof(char)*MAX_GRAPH_SIZE);
	stack[++top] = 0;
	while (top != -1) {
		char index = stack[top--];
		int i = 0;
		if (!visited[index]) {
			int i = 0;
			printf("%c", index + 'A');
			visited[index] = 1;
			for (i = MAX_GRAPH_SIZE - 1; i >= 0; i--)
				if (g->graph[index][i] && !visited[i])
					stack[++top] = i;
		}
	}
}
int main() {
	Graph* g = creat();
	dfsByStack(g);
}