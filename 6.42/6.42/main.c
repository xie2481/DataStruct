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
		char ch = preOrder[0];
		int i = 0,len=strlen(inOrder);
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
void getLeafNum(Tree* t, int* num) {
	if (t) {
		if (!t->left && !t->right)
			(*num)++;
		getLeafNum(t->left,num);
		getLeafNum(t->right,num);
	}
}
int main() {
	Tree* node = creat("abcdhge", "chdgbae");
	int num = 0;
	getLeafNum(node, &num);
	printf("%d\n", num);
	return 0;
}