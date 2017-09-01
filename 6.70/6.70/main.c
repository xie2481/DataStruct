#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
}Tree;
Tree* creat(char* s,int low,int high) {
	if (s[low] == '#')
		return NULL;
	else {
		Tree* node = (Tree*)malloc(sizeof(Tree));
		int len = high - low+1;
		node->data = s[low];
		if (len != 1) {
			int i = low + 2,brace=0;//去掉开始的括号
			while (s[i] != ','||brace) {
				if (s[i] == '(')
					brace++;
				if (s[i] == ')')
					brace--;
				i++;
			}
			node->left = creat(s, low + 2, i - 1);
			node->right = creat(s, i + 1, high - 1);
		}
		else
			node->left = node->right = NULL;
		return node;
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
	char* s = "A(B(#,D),C(E(#,F),#))";
	Tree* t = creat(s, 0, strlen(s) - 1);
	print(t);
}