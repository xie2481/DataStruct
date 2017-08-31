#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
}Tree;
char pre[100];
int node=0;
char* subString(char* s, int i, int j) {
	if (i < j&&i >= 0 && j <= strlen(s)) {
		char* temp = (char*)malloc(sizeof(char)*(j - i));
		int k = 0;
		for (k = 0; k < j - i; k++)
			temp[k] = s[i + k];
		temp[k] = '\0';
		return temp;
	}
	else
		return NULL;
}
Tree* creat(char* preOrder, char* inOrder) {
	if (preOrder) {
		Tree* node = (Tree*)malloc(sizeof(Tree));
		char ch = preOrder[0];
		int i = 0, len = strlen(inOrder);
		node->data = ch;
		while (i < len) {
			if (ch == inOrder[i])
				break;
			i++;
		}
		node->left = creat(subString(preOrder, 1, i + 1), subString(inOrder, 0, i));
		node->right = creat(subString(preOrder, i + 1, len), subString(inOrder, i + 1, len));
		return node;
	}
	else
		return NULL;
}
void getPreOrder(Tree* t) {
	if (t) {
		getPreOrder(t->left);
		pre[node++] = t->data;
		getPreOrder(t->right);
	}
}
int Max(int a, int b) {
	return a > b ? a : b;
}
void getDepth(Tree* t,Tree* node,int n,int* i) {//得到node结点的层次
	if (t) {
		getDepth(t->left, node, n + 1, i);
		if (t == node)
			*i = n;
		getDepth(t->right, node, n + 1, i);
	}
}
void printByTreeShape(Tree* t) {
	char** a = NULL;
	int i = 0,j=0;
	Tree* queue[100];
	int front = 0, rear = -1;
	queue[++rear] = t;
	getPreOrder(t);
	pre[node] = '\0';
	a = (char**)malloc(sizeof(char*)*node);
	for (i = 0; i < node; i++) {
		a[i] = (char*)malloc(sizeof(char)*node);
		memset(a[i], '0', sizeof(char)*node);
	}
	while (front <= rear) {
		Tree* temp = queue[front++];
		if (!temp)
			continue;
		i = 0;
		while (i < node&&pre[i] != temp->data)
			i++;
		j = 0;
		getDepth(t, temp, 0, &j);
		a[node - i - 1][j] = temp->data;
		queue[++rear] = temp->left;
		queue[++rear] = temp->right;
	}
	//打印矩阵
	for (i = 0; i < node; i++) {
		for (j = 0; j < node; j++) {
			if (a[i][j]!='0')
				printf("%c", a[i][j]);
			else
				printf(" ");
		}
		printf("\n");
	}
}
int main() {
	Tree* t = creat("ABDCEF", "BDAEFC");
	printByTreeShape(t);
}