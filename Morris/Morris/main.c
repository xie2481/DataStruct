/*不使用栈和递归，同时不添加parent节点遍历整棵树，参考博客http://blog.csdn.net/laojiu_/article/details/50820093*/
/*http://blog.csdn.net/mxw976235955/article/details/39829973*/
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
void inTravel(Tree* t) {//实现中序遍历
	Tree* cur = t;
	Tree* pre = NULL;
	while (cur) {
		if (cur->left == NULL) {//当前结点没有前驱元素
			printf("%c", cur->data);
			cur = cur->right;
		}
		else {
			//找到cur的前驱
			pre = cur->left;
			while (pre->right&&pre->right!=cur)
				pre = pre->right;
			if (pre->right == NULL) {//将前驱与其后继cur结点连接起来
				pre->right = cur;
				cur = cur->left;
			}
			else {//还原树的结构
				pre->right = NULL;
				printf("%c", cur->data);
				cur = cur->right;
			}
		}
	}
}
void preTravel(Tree* t) {//先序遍历
	Tree* cur = t;
	Tree* post = NULL;
	while (cur) {
		if (cur->left == NULL) {//cur不存在左子树
			printf("%c", cur->data);
			cur = cur->right;
		}
		else {
			post = cur->left;//找cur结点遍历左子树时最后一个访问的结点
			while (post->right&&post->right != cur)
				post = post->right;
			if (post->right == NULL) {
				post->right = cur;
				printf("%c", cur->data);
				cur = cur->left;
			}
			else {
				cur = cur->right;
				post->right = NULL;
			}
		}
	}
}
void postTravel(Tree* t) {
	Tree* cur = t;
	Tree* dump = NULL, *pre = NULL;
	while (cur) {
		dump = cur;
		if (cur->left == NULL)
			cur = cur->right;
		else {
			pre = cur->left;
			while (pre->right&&pre->right != cur)
				pre = pre->right;
			if (pre->right == NULL) {
				pre->right = cur;
				cur = cur->left;
			}
			else {
				char stack[100];
				int k = -1;
				pre->right = NULL;
				//倒序输出cur左子树到前驱结点路径上的所有结点
				dump = dump->left;
				while (dump) {
					stack[++k] = dump->data;
					dump = dump->right;
				}
				while (k != -1) {
					printf("%c", stack[k--]);
				}
				if (cur->right) {
					if (!cur->right->left && !cur->right->right) {//当前结点的右子树仅有一个叶子结点，无法回溯，直接输出
						printf("%c", cur->right->data);
						if(cur!=t)
							printf("%c", cur->data);
					}
				}
				cur = cur->right;
			}
		}
	}
	//补充根结点的输出
	printf("%c", t->data);
}
int main() {
	Tree* node = creat("abcdghef", "bdcgaehf");
	//preTravel(node);
	postTravel(node);
	printf("\n");
	return 0;
}