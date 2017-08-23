#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char p[100];
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
		int i = 0, len = strlen(inOrder);
		char ch = preOrder[0];
		node->data = preOrder[0];
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
char* toString(char ch) {
	char* temp = (char*)malloc(sizeof(char) * 2);
	temp[0] = ch;
	temp[1] = '\0';
	return temp;
}
void getValue(Tree* t) {//ch记录返回的值
	if (t != NULL) {
		strcat(p, toString(t->data));
		getValue(t->left);
		getValue(t->right);
	}
}
int main() {
	Tree* node = creat("abcdhge", "chdgbae");
	memset(p, '\0', sizeof(char) * 100);
	getValue(node);
	printf("%c", p[6]);
}