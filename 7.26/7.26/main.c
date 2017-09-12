/*必要性:因为该有向图不含回路，所以只存在i->j的通路，不存在j->i的通路，所以可以写成下三角的形式，同时因为不存在i->i
的通路，所以主对角线为0;充分性:因为该邻接矩阵为下三角形，上三角全为0，说明只存在i->j的通路，不存在j->i的通路，否则上三角
必然会出现非0元素，同时因为主对角线为0，所以不存在闭环，综上，该有向图不含回路，得证*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
typedef struct {
	int graph[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	char buffer[100];
	int i = 0;
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->vexnum = g->edgenum = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++)
		memset(g->graph[i], 0, sizeof(int)*MAX_GRAPH_SIZE);
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
void changeIndex(Graph* g) {//将所有上三角部分的边的弧尾和弧头的编号进行交换
	int i = 0,j=0;
	for(i=0;i<g->vexnum;i++)
		for (j = i + 1; j < g->vexnum; j++) {
			if (g->graph[i][j]) {
				g->graph[i][j] = 0;
				g->graph[j][i] = 1;
				printf("%d-->%d\n", i, j);
				printf("%d-->%d\n", j, i);
			}
		}
}
int main() {
	Graph* g = creat();
	changeIndex(g);
	return 0;
}