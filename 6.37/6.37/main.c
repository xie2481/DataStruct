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
		node->data = preOrder[0];
		char ch = preOrder[0];
		int i = 0, len = strlen(inOrder);
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
void printByNoRecursion(Tree* t) {
	Tree* stack[100];
	int k = -1;
	stack[++k] = t;
	while (k != -1) {
		t = stack[k--];
		if (t == NULL)
			continue;
		else {
			printf("%c", t->data);
			stack[++k] = t->right;
			stack[++k] = t->left;
		}
	}
}
int main() {
	Tree* node = creat("abdc", "bdac");
	printByNoRecursion(node);
	return 0;
}