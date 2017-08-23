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
void getNode(Tree* t, char x) {
	if (t) {
		if (t->data == x)
			node = t;
		else {
			if (t->left&&t->left->data == x) {
				node = t->left;
				t->left = NULL;
			}
			else if (t->right&&t->right->data == x) {
				node = t->right;
				t->right = NULL;
			}
			else {
				getNode(t->left, x);
				getNode(t->right, x);
			}
		}
	}
}
void Delete(Tree* t) {
	if (t) {
		Delete(t->left);
		Delete(t->right);
		free(t);
		t->left = NULL;
		t->right = NULL;
	}
}
void print(Tree* t) {
	if (t) {
		printf("%c", t->data);
		print(t->left);
		print(t->right);
	}
}
int main() {
	Tree* t = creat("abcdhge", "chdgbae");
	getNode(t, 'c');
	Delete(node);
	print(t);
	printf("\n");
	return 0;
}