#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum{ITSELF,RIGHT,LEFT}Flag;
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
	struct TreeNode* parent;
	Flag mark;
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
Tree* creat(Tree* parent,char* preOrder, char* inOrder) {
	if (preOrder) {
		Tree* node = (Tree*)malloc(sizeof(Tree));
		int i = 0,len=strlen(inOrder);
		char ch = preOrder[0];
		node->data = preOrder[0];
		node->parent = parent;
		while (i < len) {
			if (ch == inOrder[i])
				break;
			i++;
		}
		node->left = creat(node, subString(preOrder, 1, i + 1), subString(inOrder,0, i));
		node->right = creat(node, subString(preOrder, i + 1, strlen(preOrder)), 
			subString(inOrder, i + 1, strlen(inOrder)));
		if (node->left)
			node->mark = LEFT;
		else if (node->right)
			node->mark = RIGHT;
		else
			node->mark = ITSELF;
		return node;
	}
	else
		return NULL;
}
void printByNoRecursion(Tree* node) {//根据标记来访问结点，每次访问完，标记减少1，直到标记为访问自身
	while (node->mark!=ITSELF||node->parent) {
		while (node->mark != ITSELF) {
			node->mark--;
			if (node->mark + 1 == LEFT)
				node = node->left;
			else
				node = node->right;
		}
		printf("%c", node->data);
		node = node->parent;
	}
	printf("%c", node->data);
}
int main() {
	Tree* t = creat(NULL,"abdc", "bdac");
	printByNoRecursion(t);
	printf("\n");
	return 0;
}