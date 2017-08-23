#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
	struct TreeNode* parent;
}Tree;
char* subString(char* s, int i, int j) {
	if (i < j&&i >= 0 && j <= strlen(s)) {
		char* temp = (char*)malloc(sizeof(char)*(j - i));
		int k = 0;
		for (k = 0; k < j - i; k++)
			temp[k] = s[k + i];
		temp[k] = '\0';
		return  temp;
	}
	else
		return NULL;
}
Tree* creat(Tree* parent, char* preOrder, char* inOrder) {
	if (preOrder) {
		Tree* node = (Tree*)malloc(sizeof(Tree));
		char ch = preOrder[0];
		int i = 0, len = strlen(inOrder);
		node->data = preOrder[0];
		node->parent = parent;
		while (i < len) {
			if (ch == inOrder[i])
				break;
			i++;
		}
		node->left = creat(node, subString(preOrder, 1, i + 1), subString(inOrder, 0, i));
		node->right = creat(node, subString(preOrder, i + 1, strlen(preOrder)),
			subString(inOrder, i + 1, strlen(inOrder)));
		return node;
	}
	else
		return NULL;
}
void printByNoRecursion(Tree* t) {
	Tree* pre=NULL;
	while (t) {
		if (t->right == pre) {//t结点右子树访问结束，回溯回上一个结点
			pre = t;
			t = t->parent;
		}
		else if (pre != t->left) {//t结点的左子树未被访问
			while (t->left) {
				pre = t;
				t = t->left;
			}
			printf("%c", t->data);
			if (t->right&&t->right != pre) {//存在右子树且右子树未被访问
				pre = t;
				t = t->right; 
				continue;
			}
			else if(t->right==NULL){//当前结点右子树不存在
				pre = t;
				t = t->parent;
			}
			else {//右子树被访问过
				pre = t;
				t = t->parent;
			}
		}
		else {//访问t结点的右子树或者回溯
			printf("%c", t->data);
			if (t->right&&t->right != pre) {//右子树存在，且未被访问过
				pre = t;
				t = t->right;
			}
			else {
				pre = t;
				if (t->parent)//t不是根结点
					t = t->parent;
				else
					t = t->right;
			}
		}
	}
}
int main() {
	Tree* node = creat(NULL,"abcdhge", "chdgbae");
	printByNoRecursion(node);
	printf("\n");
	return 0;
}