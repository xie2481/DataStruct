#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 100
int* inDegree;
typedef struct {
	int s[MAX_GRAPH_SIZE];//��[fst[i],lst[i]]�ϴ�ŵ�i���������к����Ϣ
	int* fst;
	int* lst;
	int n;//��¼�����
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
			g->s[++g->lst[i]] = j;//��i�����ĺ�̽�����ӣ�������������ƶ�һλ
			for (k = i + 1; k <= g->n; k++) {//���к���������ʼλ�ö�����ƶ�һλ
				int p = g->lst[k] - g->fst[k];//��¼ƫ����
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
	findInDegree(g);//�ҵ����ж�������
	for (i = 1; i <= g->n; i++)//�����Ϊ0�Ķ�����ջ
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