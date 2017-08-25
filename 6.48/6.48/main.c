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
		node->right = creat(subString(preOrder, i + 1, strlen(preOrder)), subString(inOrder, i + 1, strlen(inOrder)));
		return node;
	}
	else
		return NULL;
}
Tree* getParentNode(Tree* t,Tree* q,Tree* p) {//通过层次遍历寻找祖先结点
	if (t) {
		Tree* queue[100];
		Tree* parent = NULL;
		int front = 0, rear = -1;
		queue[++rear] = t;
		while (front <= rear) {
			Tree* node = queue[front++];
			if (node->left == q || node->right == q
				|| node->left == p || node->right == p) {//当前结点为q或p的一个父节点
				parent = node;
				break;
			}
			if (node->left)
				queue[++rear] = node->left;
			if (node->right)
				queue[++rear] = node->right;
		}
		return parent;
	}
	else
		return NULL;
}
int main() {
	/*树为 a
	      b  d
		   c
		  d g*/
	Tree* t = creat("abcdgh", "bdcgah");
	Tree* p = t->left->right;//p为c
	Tree* q = t->left->right->left;//q为d
	printf("%c", getParentNode(t, p, q)->data);
}