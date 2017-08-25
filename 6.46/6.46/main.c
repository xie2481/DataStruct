#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
}Tree;
typedef struct {
	int visited;
	Tree* t;
}Paired;
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
Paired* initPair(Tree* t, int visited) {
	Paired* p = (Paired*)malloc(sizeof(Paired));
	p->t = t;
	p->visited = visited;
	return p;
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
Tree* copy(Tree* t) {
	if (t) {
		Tree* stack_tree[100];
		Tree* stack_newTree[100];
		int top1 = -1,top2=-1;
		Tree* tree = (Tree*)malloc(sizeof(Tree));
		tree->data = t->data;
		stack_tree[++top1] = t;
		stack_newTree[++top2] = tree;
		while (top1 != -1) {
			Tree* oldNode = stack_tree[top1--];
			Tree* newNode = stack_newTree[top2--];
			if (oldNode == NULL)
				continue;
			else {
				stack_tree[++top1] = oldNode->right;
				stack_tree[++top1] = oldNode->left;
				if (oldNode->right == NULL) {
					newNode->right = NULL;
					stack_newTree[++top2] = NULL;
				}
				else {
					Tree* node = (Tree*)malloc(sizeof(Tree));
					node->data = oldNode->right->data;
					newNode->right = node;
					stack_newTree[++top2] = node;
				}
				if (oldNode->left == NULL) {
					newNode->left = NULL;
					stack_newTree[++top2] = NULL;
				}
				else {
					Tree* node = (Tree*)malloc(sizeof(Tree));
					node->data = oldNode->left->data;
					newNode->left = node;
					stack_newTree[++top2] = node;
				}
			}
		}
		return tree;
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
	Tree* node = creat("abcdgh", "bdcgah");
	Tree* copyTree = copy(node);
	print(copyTree);
	printf("\n");
	return 0;
}