#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
}Tree;
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
int Max(int a, int b) {
	return a > b ? a : b;
}
int getDepth(Tree* t) {
	if (t) {
		if (!t->left && !t->right)
			return 1;
		else
			return Max(getDepth(t->left) + 1, getDepth(t->right) + 1);
	}
	else
		return 0;
}
int getMaxNode(Tree* t) {
	Tree* queue[100];
	int front = 0, rear = -1,max=0;
	queue[++rear] = t;
	while (front <= rear) {
		int temp = rear;//作为临时队尾
		if (max < rear - front + 1)
			max = rear - front + 1;
		//将该层元素全部出队列
		while (front <= temp) {
			Tree* node = queue[front++];
			if (node->left)
				queue[++rear] = node->left;
			if (node->right)
				queue[++rear] = node->right;
		}
	}
	return max;
}
int getProsperous(Tree* t) {
	return getDepth(t)*getMaxNode(t);
}
int main() {
	Tree* node = creat("abdhecfg", "hdbeafcg");
	printf("%d\n", getProsperous(node));
	return 0;
}