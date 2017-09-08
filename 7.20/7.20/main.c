#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 10
int graph[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
int visited[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
void init() {
	int i = 0, j = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++) {
		memset(graph[i], 0, MAX_GRAPH_SIZE);
		memset(visited[i], 0, MAX_GRAPH_SIZE);
	}
}
void creat() {
	FILE* f = fopen("test.txt", "r");
	char buffer[100];
	init();
	while (fgets(buffer, 100, f)) {
		int i = buffer[0] - '0', j = buffer[2] - '0';
		graph[i][j] = 1;
	}
	fclose(f);
}
int ifTrans() {
	int trans = 1;
	int i = 0, j = 0,k=0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++) {
		for (j = 0; j < MAX_GRAPH_SIZE; j++) {
			if (graph[i][j]) {
				for (k = 0; k < MAX_GRAPH_SIZE; k++) {
					if (k == i)
						continue;
					if (graph[j][k]&&!graph[i][k])
						trans = 0;
				}
			}
		}
	}
	return trans;
}
int main() {
	creat();
	printf("%d", ifTrans());
	return 0;
}