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
void printOperation(Tree* t) {
	if (t) {
		if (t->left&&(t->left->data<'0'||t->left->data>'9')) {
			printf("(");
			printOperation(t->left);
			printf(")");
		}
		else
			printOperation(t->left);
		printf("%c", t->data);
		if (t->right && (t->right->data<'0' || t->right->data>'9')) {
			printf("(");
			printOperation(t->right);
			printf(")");
		}
		else
			printOperation(t->right);
	}
}
int main() {
	Tree* t = creat("*+25-46", "2+5*4-6");
	printOperation(t);
}