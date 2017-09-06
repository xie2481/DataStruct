#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTEX_SIZE 20
typedef enum { unvisited, visited }VisitIf;
typedef struct EBox {
	VisitIf mark;//���ʱ��
	int ivex, jvex;//�洢��ǰ�ߵ��±�
	struct EBox* ilink, *jlink;//�ֱ�ָ��������2���������һ����
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
			//����iΪ��β�ı�
			arc->ilink = g->adjmulist[i].ilink;
			g->adjmulist[i].ilink = arc;
			//������jΪ��ͷ�ı�
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
void removeArcFromList(AMLGraph* g, int v, int w) {//Ĭ��û���ظ���
	//ɾ����<v-1,w-1>,��g[v-1]��ʼ
	EBox* p = g->adjmulist[v - 1].ilink;
	EBox* pre = NULL;
	if (p&&p->jvex == w - 1) {//�׽�����������
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
	//��g[w-1]��ʼ��ɾ����<v-1,w-1>
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
	//�ָ���ʼ״̬
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