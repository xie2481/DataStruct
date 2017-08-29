#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
}Tree;
Tree* creat(char* preOrder, int a, int b, char* inOrder, int c, int d) {
	if (a < b) {
		Tree* node = (Tree*)malloc(sizeof(Tree));
		char ch = preOrder[a];
		int i = c;
		while (i < d) {
			if (ch == inOrder[i])
				break;
			i++;
		}
		node->data =ch;
		node->left = creat(preOrder, a + 1,a+1+i-c, inOrder, c, i);
		node->right = creat(preOrder, a+1+i-c, b, inOrder, c+i + 1, d);
		return node;
	}
	else
		return NULL;
}
void print(Tree* t) {
	if (t) {
		printf("%c", t->data);
		print(t->left);
		print(t->right);
	}
}
int main() {
	Tree* t = creat("abdc",0,4, "bdac",0,4);
	print(t);
}