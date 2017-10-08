/*http://blog.csdn.net/mu399/article/details/50903876*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
typedef struct AdjNode {
	int index;
	struct AdjNode* next;
	int weight;
}AdjNode;
typedef struct {
	char data;
	AdjNode* firstInNode;
	AdjNode* firstOutNode;
}GraphNode;
typedef struct {
	GraphNode graph[MAX_GRAPH_SIZE];
	int vexnum, edgenum;
}Graph;
int getNum(char* s, int start) {
	int total = 0;
	while (s[start] >= '0'&&s[start] <= '9') {
		total *= 10;
		total += s[start++] - '0';
	}
	return total;
}
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	Graph* g = (Graph*)malloc(sizeof(Graph));
	char buffer[100];
	int i = 0;
	for (i = 0; i < MAX_GRAPH_SIZE; i++) {
		g->graph[i].firstInNode = NULL;
		g->graph[i].firstOutNode = NULL;
	}
	g->vexnum = g->edgenum = 0;
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum = buffer[0] - '0';
		else if (g->edgenum == 0)
			g->edgenum = buffer[0] - '0';
		else {
			int i = buffer[0] - '0'-1, j = buffer[2] - '0'-1, weight = getNum(buffer, 4);
			AdjNode* pin = (AdjNode*)malloc(sizeof(AdjNode));
			AdjNode* pout = (AdjNode*)malloc(sizeof(AdjNode));
			pin->index = i;
			pin->weight = weight;
			pout->index = j;
			pout->weight = weight;
			pout->next = g->graph[i].firstOutNode;
			g->graph[i].firstOutNode = pout;
			pin->next = g->graph[j].firstInNode;
			g->graph[j].firstInNode = pin;
		}
	}
	fclose(f);
	return g;
}
int* getShortestPath_DIJ(Graph* g, int v0) {
	int* Final = (int*)malloc(sizeof(int)*g->vexnum);//¼ÇÂ¼S¼¯ºÏ
	int* dist = (int*)malloc(sizeof(int)*g->vexnum);
	int i = 0; 
	int v = v0;
	memset(Final, 0, sizeof(int)*g->vexnum);
	memset(dist,100, sizeof(int)*g->vexnum);
	dist[v0] = 0;
	for (i = 1; i < g->vexnum; i++) {
		int min = INT_MAX,minindex=0;
		Final[v] = 1;
		AdjNode* p = g->graph[v].firstOutNode;
		while (p) {
			if (!Final[p->index]) {
				if (dist[p->index] > dist[v] + p->weight) {
					dist[p->index] = dist[v] + p->weight;
				}
				if (min > dist[p->index]) min = dist[p->index], minindex = p->index;
			}
			p = p->next;
		}
		v = minindex;
	}
	return dist;
}
int main() {
	Graph* g = creat();
	int* d = getShortestPath_DIJ(g, 0);
	for (int i = 0; i < g->vexnum; i++)
		printf("%d\t", d[i]);
}