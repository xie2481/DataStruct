#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
}Tree;
char* subString(char* s, int i, int j) {
	int len = strlen(s);
	if (i < j&&i >= 0 && j <= len) {
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
		node->data = preOrder[0];
		char ch = preOrder[0];
		int i = 0,len=strlen(inOrder);
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
void printTree(Tree* t) {
	if (t) {
		printTree(t->left);
		printf("%c", t->data);
		printTree(t->right);
	}
}
int isSimilar(Tree* b1, Tree* b2) {
	if (b1 == NULL&&b2 == NULL)
		return 1;
	else if (b1&&b2&&isSimilar(b1->left, b2->left) && isSimilar(b1->right, b2->right))
		return 1;
	else
		return 0;
}
int main() {
	Tree* t = creat("123", "213");
	Tree* t1 = creat("1", "1");
	printTree(t);
	printf("\n");
	printf("%d\n", isSimilar(t, t1));
	return 0;
}