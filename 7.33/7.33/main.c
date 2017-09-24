#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 20
typedef struct {
	int start;
	int end;
	int weight;
}Pair;
typedef struct {
	int parent;
	char data;
}Set;
typedef struct {
	Pair edge[MAX_GRAPH_SIZE];
	int edgenum;
	int vexnum;
}EdgeSetType;
typedef struct TreeNode {
	char data;
	struct TreeNode* child;
	struct TreeNode* brother;
}TreeNode;
typedef struct Tree {
	TreeNode tree[MAX_GRAPH_SIZE];
	int vexnum;
	int start;
}Tree;
void quickSort(EdgeSetType* s,int low,int high) {
	if (low >= high)
		return;
	Pair key = s->edge[low];
	int i = low, j = high;
	while (i < j) {
		while (i < j&&s->edge[j].weight <= key.weight)
			j--;
		s->edge[i] = s->edge[j];
		while (i < j&&s->edge[i].weight >= key.weight)
			i++;
		s->edge[j] = s->edge[i];
	}
	s->edge[i] = key;
	quickSort(s, low, i - 1);
	quickSort(s, i + 1, high);
}
EdgeSetType* creat() {
	FILE* f = fopen("test.txt", "r");
	EdgeSetType* set = (EdgeSetType*)malloc(sizeof(EdgeSetType));
	char buffer[100];
	int count = 0;
	set->edgenum = 0;
	set->vexnum = 0;
	while (fgets(buffer, 100, f)) {
		if (set->vexnum == 0)
			set->vexnum = atoi(buffer);
		else if (set->edgenum == 0)
			set->edgenum = atoi(buffer);
		else {
			int i = buffer[0] - '0' - 1, j = buffer[2] - '0' - 1;
			if (i > j) {
				i = i^j;
				j = i^j;
				i = i^j;
			}
			set->edge[count].start = i;
			set->edge[count].end = j;
			set->edge[count++].weight = buffer[4] - '0';
		}
	}
	fclose(f);
	quickSort(set, 0, set->edgenum - 1);
	return set;
}
int getMinEdge(EdgeSetType* set, int* u, int* v) {
	if (set->edgenum == 0)
		return 0;
	else {
		*u = set->edge[set->edgenum - 1].start;
		*v = set->edge[set->edgenum - 1].end;
		return 1;
	}
}
int delMinEdge(EdgeSetType* set) {
	if (set->edgenum == 0)
		return 0;
	else {
		set->edgenum--;
		return 1;
	}
}
void insert(TreeNode* p, TreeNode* q) {
	if (p->child == NULL)
		p->child = q;
	else {
		q->brother = p->child->brother;
		p->child->brother = q;
	}
}
int find(Set* t,int x){
	while (x != t[x].parent&&t[x].parent>=0)
		x = t[x].parent;
	return x;
}
void fix(Set* t, int i) {
	int x = find(t, i);
	int k = i;
	while (k != x) {
		int j = t[k].parent;
		t[k].parent = x;
		k = j;
	}
}
void merge(Set* t, int x, int y) {
	t[x].parent = y;
	fix(t, x);
}
Tree* getMinSpanTree(EdgeSetType* s) {//先使用并查集生成最小树，再将其存储结构转换成孩子-兄弟结构
	Set* set = (Set*)malloc(sizeof(Set)*s->vexnum);
	int i = 0;
	Tree* t = (Tree*)malloc(sizeof(Tree));
	t->vexnum = s->vexnum;
	for (i = 0; i < s->vexnum; i++) {
		set[i].parent = -1;
		set[i].data = 'A' + i;
		t->tree[i].child = t->tree[i].brother = NULL;
		t->tree[i].data = 'A' + i;
	}
	int x = 0, y = 0;
	while (getMinEdge(s, &x, &y)) {
		x = find(set, x);
		y = find(set, y);
		if (x != y) 
			merge(set, x, y);
		delMinEdge(s);
	}
	for (i = 0; i < s->vexnum; i++) {
		if (set[i].parent != -1)
			insert(&t->tree[set[i].parent], &t->tree[i]);
		else
			t->start = i;
	}
	return t;
}
void dfs(TreeNode* root) {
	if (root) {
		printf("%c", root->data);
		dfs(root->child);
		dfs(root->brother);
	}
}
int main() {
	EdgeSetType* s = creat();
	Tree* t=getMinSpanTree(s);
	dfs(&t->tree[t->start]);
}