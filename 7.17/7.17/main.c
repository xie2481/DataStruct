#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTEX_NUM 20
int visited[MAX_VERTEX_NUM];
typedef struct ArcBox {
	int tailvex, headvex;//定义当前弧的弧尾下标和弧头下标
	struct ArcBox* hlink, *tlink;//分别为弧头相同和弧尾相同的弧的链域
}ArcBox;
typedef struct VexNode {
	char data;
	ArcBox* firstin, *firstout;//分别指向该顶点第一条入弧和出弧
}VexNode;
typedef struct {
	VexNode xList[MAX_VERTEX_NUM];
	int vexnum, arcnum;
}Graph;
Graph* creat() {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	FILE* f = fopen("test.txt", "r");
	char buffer[100];
	int i = 0;
	for (i = 0; i < MAX_VERTEX_NUM; i++)
		g->xList[i].firstin = g->xList[i].firstout = NULL;
	g->vexnum = g->arcnum = 0;
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum = buffer[0] - '0';
		else if (g->arcnum == 0)
			g->arcnum = buffer[0] - '0';
		else if (buffer[0] != '^') {
			int index1 = buffer[0] - '0' - 1;
			int index2 = buffer[2] - '0' - 1;
			ArcBox* p = (ArcBox*)malloc(sizeof(ArcBox));
			g->xList[index1].data = 'A' + index1;
			g->xList[index2].data = 'A' + index2;
			p->tailvex = index1;
			p->headvex = index2;
			p->hlink = g->xList[index2].firstin;
			p->tlink = g->xList[index1].firstout;
			g->xList[index2].firstin = p;
			g->xList[index1].firstout = p;
		}
		else
			break;
	}
	return g;
}
void InsertVex(Graph* g, int v) {
	g->vexnum++;
	g->xList[g->vexnum - 1].data= 'A' + v - 1;
	g->xList[g->vexnum - 1].firstin = g->xList[g->vexnum - 1].firstout = NULL;
}
void InsertArc(Graph* g, int v, int w) {
	ArcBox* p = (ArcBox*)malloc(sizeof(ArcBox));
	p->tailvex = v - 1;
	p->headvex = w - 1;
	p->hlink = g->xList[w-1].firstin;
	p->tlink = g->xList[v - 1].firstout;
	g->xList[w - 1].firstin = p;
	g->xList[v - 1].firstout = p;
	g->arcnum++;
}
void DeleteThisNode(Graph* g, int v,int w) {//删除弧为i，v的结点
	//先删弧头为v的边
	ArcBox* prev = g->xList[v].firstout;
	ArcBox* prew = g->xList[w].firstin;
	//先找v结点的
	if (prev&&prev->headvex == w) {
		g->arcnum--;
		g->xList[v].firstout = g->xList[v].firstout->hlink;
	}
	else if(prev){
		ArcBox* pv = g->xList[v].firstout->hlink;
		while (pv) {
			if (pv->headvex == w) {
				prev->hlink = pv->hlink;
				g->arcnum--;
				break;
			}
			prev = prev->hlink;
			pv = pv->hlink;
		}
	}
	//再找w结点的
	if (prew&&prew->tailvex == v) {
		g->xList[w].firstin = g->xList[w].firstin->tlink;
		free(prew);
	}
	else if(prew){
		ArcBox* pw = g->xList[w].firstin;
		while (pw) {
			if (pw->tailvex == v) {
				prew->tlink = pw->tlink;
				free(pw);
				break;
			}
			pw = pw->tlink;
			prew = prew->tlink;
		}
	}
	
}
void DeleteVex(Graph* g, int v) {
	//先删除v所在的边
	int i = 0;
	for (i = 0; i < g->vexnum; i++) {
		if (i == v - 1)
			continue;
		DeleteThisNode(g, i, v - 1);
	}
	//将v结点删除
	for (i = v; i < g->vexnum; i++)
		g->xList[i] = g->xList[i - 1];
	g->vexnum--;
}
void DeleteArc(Graph* g, int v, int w) {
	DeleteThisNode(g, v - 1, w - 1);
}
void dfs(Graph* g, int i) {
	ArcBox* p = g->xList[i].firstout;
	visited[i] = 1;
	printf("%c", g->xList[i].data);
	while (p) {
		if(!visited[p->headvex])
			dfs(g, p->headvex);
		p = p->hlink;
	}
}
void dfstravel(Graph* g) {
	int i = 0;
	memset(visited, 0, g->vexnum);
	for (i = 0; i < g->vexnum; i++) {
		if (!visited[i])
			dfs(g, i);
	}
}
int main() {
	Graph* g = creat();
	InsertVex(g, 5);
	InsertArc(g, 1, 5);
	//DeleteVex(g, 5);
	//DeleteArc(g, 1, 5);
	dfstravel(g);
}