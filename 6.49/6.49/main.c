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
/*层次遍历整棵树，如果为完全二叉树，则必然最后一个出队的结点为空,所以要保证当为完全二叉树时，只有最后一个结点及其空兄弟
入队，为此叶子结点的空子树是不能入队的*/
int isCompleteBinaryTree(Tree* t) {
	if (t) {
		Tree* queue[100];
		int front = 0, rear = -1;
		queue[++rear] = t;
		while (front <= rear) {
			Tree* node = queue[front++];
			if (node == NULL) {
				if (front > rear)
					return 1;
				else
					return 0;
			}
			else {
				if (node->left||node->right) {
					queue[++rear] = node->left;
					queue[++rear] = node->right;
				} 
			}
		}
		return 1;
	}
	else
		return 1;
}
int main() {
	Tree* node = creat("abc", "bac");
	printf("%d\n", isCompleteBinaryTree(node));
	return 0;
}