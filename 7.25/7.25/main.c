#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 100
int* inDegree;
typedef struct {
	int s[MAX_GRAPH_SIZE];//在[fst[i],lst[i]]上存放第i个结点的所有后继信息
	int* fst;
	int* lst;
	int n;//记录结点数
}Graph;
Graph* creat() {
	FILE* f = fopen("test.txt", "r");
	Graph* g = (Graph*)malloc(sizeof(Graph));
	char buffer[100];
	memset(g->s, 0, sizeof(int)*MAX_GRAPH_SIZE);
	g->fst = g->lst = NULL;
	while (fgets(buffer, 100, f)) {
		if (g->fst == NULL) {
			int i = 0;
			g->n = buffer[0] - '0';
			g->fst = (int*)malloc(sizeof(int)*(g->n + 1));
			g->lst = (int*)malloc(sizeof(int)*(g->n + 1));
			for (i = 1; i <= g->n; i++) {
				g->fst[i] = i;
				g->lst[i] = i - 1;
			}
		}
		else {
			int i = buffer[0] - '0', j = buffer[2] - '0', k = 0;
			g->s[++g->lst[i]] = j;//第i个结点的后继结点增加，区间上限向后移动一位
			for (k = i + 1; k <= g->n; k++) {//所有后续结点的起始位置都向后移动一位
				int p = g->lst[k] - g->fst[k];//记录偏移量
				g->fst[k] = g->lst[k - 1] + 1;
				g->lst[k] = g->fst[k] + p;
			}
		}
	}
	fclose(f);
	return g;
}
void findInDegree(Graph* g) {
	int i = 0,j=0;
	inDegree = (int*)malloc(sizeof(int)*(g->n + 1));
	memset(inDegree, 0, sizeof(int)*(g->n + 1));
	for (i = 1; i <= g->n; i++) {
		for (j = g->fst[i]; j <= g->lst[i]; j++) {
			inDegree[g->s[j]]++;
		}
	}
}
int isOwnCycle(Graph* g) {
	int i = 0;
	int stack[100];
	int top = -1;
	int count = 0;
	findInDegree(g);//找到所有顶点的入度
	for (i = 1; i <= g->n; i++)//将入度为0的顶点入栈
		if (!inDegree[i])
			stack[++top]=i;
	while (top != -1) {
		int i = stack[top--];
		int j = 0;
		count++;
		for (j = g->fst[i]; j <= g->lst[i]; j++)
			if (!(--inDegree[g->s[j]]))
				stack[++top] = g->s[j];
   }
	return count == g->n ? 0 : 1;
}
int main() {
	Graph* g = creat();
	printf("%d\n", isOwnCycle(g));
}