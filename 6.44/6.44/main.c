#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
}Tree;
Tree* node;
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
		node->right = creat(subString(preOrder, i + 1, strlen(preOrder)), subString(inOrder, i + 1, strlen(inOrder)));
		return node;
	}
	else
		return NULL;
}
void getNode(Tree* t,char x) {//得到以结点值为x根的子树
	if (t) {
		if (t->data == x)
			node = t;
		else {
			getNode(t->left, x);
			getNode(t->right, x);
		}
	}
}
int Max(int a, int b) {
	return a > b ? a : b;
}
int getDepth(Tree* t) {
	if (t) {
		if (!t->left && !t->right)
			return 1;
		else
			return Max(getDepth(t->left)+1, getDepth(t->right)+1);
	}
	else
		return 0;
}
int main() {
	Tree* t = creat("abcdhge", "chdgbae");
	getNode(t,'c');
	printf("%d\n", getDepth(node));
	return 0;
}