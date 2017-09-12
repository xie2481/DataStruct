/*��Ҫ��:��Ϊ������ͼ������·������ֻ����i->j��ͨ·��������j->i��ͨ·�����Կ���д�������ǵ���ʽ��ͬʱ��Ϊ������i->i
��ͨ·���������Խ���Ϊ0;�����:��Ϊ���ڽӾ���Ϊ�������Σ�������ȫΪ0��˵��ֻ����i->j��ͨ·��������j->i��ͨ·������������
��Ȼ����ַ�0Ԫ�أ�ͬʱ��Ϊ���Խ���Ϊ0�����Բ����ڱջ������ϣ�������ͼ������·����֤*/
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
void changeIndex(Graph* g) {//�����������ǲ��ֵıߵĻ�β�ͻ�ͷ�ı�Ž��н���
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