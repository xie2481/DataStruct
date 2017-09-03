#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTEX_NUM 20
int* visited;
typedef struct ArcNode {
	int adjvex;//�û���ָ��Ķ����λ��
	struct ArcNode* nextarc;//ָ����һ������ָ��
}ArcNode;
typedef struct VNode {
	char data;//������Ϣ
	ArcNode* firstarc;//ָ���һ�������ڸö���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;//ͼ�ĵ�ǰ�������ͻ���
}ALGraph;
ALGraph* creat() {
	ALGraph* graph = (ALGraph*)malloc(sizeof(ALGraph));
	FILE* f = fopen("test.txt", "r");
	char buffer[100];
	int i = 0;
	for (i = 0; i < MAX_VERTEX_NUM; i++) {
		graph->vertices[i].firstarc = NULL;
	}
	graph->vexnum = 0;
	graph->arcnum = 0;
	while (fgets(buffer, 100, f)) {
		if (graph->vexnum == 0) {//������Ϊ0
			graph->vexnum = buffer[0] - '0';
		}//�˴�Ĭ�϶�����С��10�����㴦��
		else if (graph->arcnum == 0)  //����Ϊ0
			graph->arcnum = buffer[0] - '0';
		else if(buffer[0]!='^'){
			int index = buffer[0] - '0';
			ArcNode* node = (ArcNode*)malloc(sizeof(ArcNode));
			graph->vertices[index-1].data = 'A' + index - 1;
			graph->vertices[buffer[2] - '0' - 1].data = 'A' + buffer[2] - '0' - 1;
			node->adjvex = buffer[2]-'0'-1;
			node->nextarc = NULL;
			if (graph->vertices[index-1].firstarc == NULL)
				graph->vertices[index-1].firstarc = node;
			else {
				node->nextarc = graph->vertices[index-1].firstarc;
				graph->vertices[index-1].firstarc = node;
			}
		}
		else
			break;
	}
	fclose(f);
	return graph;
}
void printG(ALGraph* g,int v) {
	ArcNode* node = g->vertices[v].firstarc;
	visited[v] = 1;
	printf("%c", g->vertices[v].data);
	while (node) {
		if (!visited[node->adjvex])
			printG(g, node->adjvex);
		node = node->nextarc;
	}
}
int main() {
	ALGraph* gl = creat();
	visited = (int*)malloc(sizeof(int)*gl->vexnum);
	memset(visited, 0, sizeof(int)*gl->vexnum);
	printG(gl, 0);
	return 0;
}
