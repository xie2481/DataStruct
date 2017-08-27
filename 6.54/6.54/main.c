#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char elem[100];
	int last;
}TreeSequence;
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
}Tree;
TreeSequence* creatSequence() {
	TreeSequence* t = (TreeSequence*)malloc(sizeof(TreeSequence));
	int i = 1;
	t->last = 1;
	memset(t->elem, 0, sizeof(char) * 100);
	for (i = 1; i <= 5; i++) {//创建一棵结点总数为5的完全二叉树
		t->elem[i] = 'a' + i - 1;
	}
	return t;
}
Tree* initNode(char ch) {
	Tree* node = (Tree*)malloc(sizeof(Tree));
	node->data = ch;
	node->left = node->right = NULL;
	return node;
}
Tree* creat(TreeSequence* t) {
	if (t->elem[t->last]) {
		Tree* root =initNode(t->elem[t->last]);
		Tree* queue[100];
		int front = 0, rear = -1;
		t->last++;
		queue[++rear] = root;
		while (t->elem[t->last]) {
			Tree* q = queue[front];
			Tree* node = initNode(t->elem[t->last++]);
			if (!q->left)
				q->left = node;
			else {
				q->right = node;
				front++;
			}
			queue[++rear] = node;
		}
		return root;
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
	Tree* node = creat(creatSequence());
	print(node);
	printf("\n");
	return 0;
}
