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
			temp[k] = s[k + i];
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
char* Strcat(char* s, char* t) {
	char* temp = (char*)malloc(sizeof(char)*(strlen(s) + strlen(t)));
	strcpy(temp, s);
	strcat(temp, t);
	return temp;
}
char* toString(char ch) {
	char* temp=(char*)malloc(sizeof(char)*2);
	temp[0] = ch;
	temp[1] = '\0';
	return temp;
}
char* getLongestPath(Tree* t) {
	Tree* stack[100];
	int top = -1;
	char* path = "";
	int depth = getDepth(t);
	stack[++top] = t;
	while (top != -1) {
		Tree* node = stack[top--];
		if (node == NULL)
			continue;
		else {
			if (!node->left && !node->right) {
				if (strlen(path) == depth - 1) {
					path = Strcat(path, toString(node->data));
					break;
				}
				else
					path = "";
			}
			else
				path = Strcat(path, toString(node->data));
			stack[++top] = node->right;
			stack[++top] = node->left;
		}
	}
	return path;
}
int main() {
	Tree* node = creat("abdhezcfg", "hdbzeafcg");
	printf("%s\n", getLongestPath(node));
	return 0;
}