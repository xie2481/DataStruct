/*时间复杂度为o(n^2)*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
	int DescNum;
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
int getChildNum(Tree* t) {
	if (t) {
		if (!t->left&&!t->right)
			return 0;
		else
			return getChildNum(t->left) +(t->left?1:0)+ getChildNum(t->right)+(t->right?1:0);
	}
	else
		return 0;
}
void setDescNum(Tree* t) {
	if (t) {
		t->DescNum = getChildNum(t);
		setDescNum(t->left);
		setDescNum(t->right);
	}
}
void printChildNum(Tree* t) {
	if (t) {
		printf("%c %d\n",t->data, t->DescNum);
		printChildNum(t->left);
		printChildNum(t->right);
	}
}
int main() {
	Tree* node = creat("abdec", "dbeac");
	setDescNum(node);
	printChildNum(node);
	return 0;
}
