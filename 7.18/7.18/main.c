#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTEX_SIZE 20
typedef enum { unvisited, visited }VisitIf;
typedef struct EBox {
	VisitIf mark;//访问标记
	int ivex, jvex;//存储当前边的下标
	struct EBox* ilink, *jlink;//分别指向依附这2个顶点的下一条边
}EBox;
typedef struct VexBox {
	char data;
	EBox* ilink;
	EBox* jlink;
}VexBox;
typedef struct {
	VexBox adjmulist[MAX_VERTEX_SIZE];
	int vexnum, edgenum;
}AMLGraph;
AMLGraph* creat() {
	FILE* f = fopen("test.txt", "r");
	char buffer[100];
	int i = 0;
	AMLGraph* g = (AMLGraph*)malloc(sizeof(AMLGraph));
	g->vexnum = g->edgenum = 0;
	for (i = 0; i < MAX_VERTEX_SIZE; i++)
		g->adjmulist[i].ilink = g->adjmulist[i].jlink = NULL;
	while (fgets(buffer, 100, f)) {
		if (g->vexnum == 0)
			g->vexnum = buffer[0] - '0';
		else if (g->edgenum == 0)
			g->edgenum = buffer[0] - '0';
		else if (buffer[0] != '^') {
			int i = buffer[0] - '0' - 1, j = buffer[2] - '0' - 1;
			EBox* arc = (EBox*)malloc(sizeof(EBox));
			arc->mark = unvisited;
			g->adjmulist[i].data = 'A' + i;
			g->adjmulist[j].data = 'A' + j;
			arc->ivex = i;
			arc->jvex = j;
			//插入i为弧尾的边
			arc->ilink = g->adjmulist[i].ilink;
			g->adjmulist[i].ilink = arc;
			//插入以j为弧头的边
			arc->jlink = g->adjmulist[j].jlink;
			g->adjmulist[j].jlink = arc;
		}
		else
			break;
	}
	fclose(f);
	return g;
}
void InsertVex(AMLGraph* g, int v) {
	g->vexnum++;
	g->adjmulist[v - 1].data = 'A' + v - 1;
}
void InsertArc(AMLGraph* g, int v, int w) {
	EBox* arc = (EBox*)malloc(sizeof(EBox));
	arc->ivex = v - 1;
	arc->jvex = w - 1;
	arc->ilink = g->adjmulist[v - 1].ilink;
	g->adjmulist[v - 1].ilink = arc;
	arc->jlink = g->adjmulist[w - 1].jlink;
	g->adjmulist[w - 1].jlink = arc;
	g->edgenum++;
}
void removeArcFromList(AMLGraph* g, int v, int w) {//默认没有重复边
	//删除边<v-1,w-1>,从g[v-1]开始
	EBox* p = g->adjmulist[v - 1].ilink;
	EBox* pre = NULL;
	if (p&&p->jvex == w - 1) {//首结点就满足条件
		g->adjmulist[v - 1].ilink = p->ilink;
		g->edgenum--;
	}
	else if (p) {
		pre = p;
		p = p->ilink;
		while (p) {
			if (p->jvex == w - 1) {
				pre->ilink = p->ilink;
				g->edgenum--;
				break;
			}
			pre = p;
			p = p->ilink;
		}
	}
	//从g[w-1]开始，删除边<v-1,w-1>
	p = g->adjmulist[w - 1].jlink;
	if (p->ivex == v - 1) {
		g->adjmulist[w - 1].jlink = p->jlink;
		free(p);
	}
	else {
		pre = p;
		p = p->jlink;
		while (p) {
			if (p->ivex == v - 1) {
				pre->jlink = p->jlink;
				free(p);
				break;
			}
			pre = p;
			p = p->jlink;
		}
	}
}
void DeleteArc(AMLGraph* g, int v, int w) {
	removeArcFromList(g, v, w);
}
void DeleteVex(AMLGraph* g, int v) {
	int i = 0;
	for (i = 0; i < g->vexnum; i++) {
		if (i == v - 1)
			continue;
		DeleteArc(g, i+1, v);
		DeleteArc(g, v, i+1);
	}
	for (i = v; i < g->vexnum; i++)
		g->adjmulist[i - 1] = g->adjmulist[i];
	g->edgenum--;
}
void dfsarc(AMLGraph* g) {
	int i = 0;
	for (i = 0; i < g->edgenum; i++) {
		EBox* p = g->adjmulist[i].ilink;
		while (p&&p->mark == unvisited) {
			printf("%c-->%c\n", g->adjmulist[p->ivex].data, g->adjmulist[p->jvex].data);
			p->mark = visited;
			p = p->ilink;
		}
		p = g->adjmulist[i].jlink;
		while (p&&p->mark == unvisited) {
			printf("%c-->%c\n", g->adjmulist[p->ivex].data, g->adjmulist[p->jvex].data);
			p->mark = visited;
			p = p->jlink;
		}
	}
	//恢复初始状态
	for (i = 0; i < g->edgenum; i++) {
		EBox* p = g->adjmulist[i].ilink;
		while (p) {
			p->mark =unvisited;
			p = p->ilink;
		}
		p = g->adjmulist[i].jlink;
		while (p) {
			p->mark = unvisited;
			p = p->jlink;
		}
	}
}
int main() {
	AMLGraph* g = creat();
	//DeleteVex(g, 1);
	dfsarc(g);
}