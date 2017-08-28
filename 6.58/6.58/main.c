#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum{LINK,THREAD}Flag;
typedef struct ThreadTreeNode {
	char data;
	struct ThreadTreeNode* left;
	struct ThreadTreeNode* right;
	Flag LTag;
	Flag RTag;
}ThreadTree;
ThreadTree* pre;
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
ThreadTree* creat(char* preOrder, char* inOrder) {
	if (preOrder) {
		ThreadTree* node = (ThreadTree*)malloc(sizeof(ThreadTree));
		char ch = preOrder[0];
		int i = 0, len = strlen(inOrder);
		node->data = ch;
		node->LTag = node->RTag = LINK;
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
void inThread(ThreadTree* p) {
	if (p) {
		inThread(p->left);
		if (!p->left) {
			p->LTag = THREAD;
			p->left = pre;
		}
		if (!pre->right) {
			pre->RTag = THREAD;
			pre->right = p;
		}
		pre = p;
		inThread(p->right);
	}
}
ThreadTree* Thread(ThreadTree* bt) {
	ThreadTree* thrt = (ThreadTree*)malloc(sizeof(ThreadTree));
	thrt->LTag = LINK;
	thrt->RTag = THREAD;
	if (!bt)
		thrt->left = thrt;
	else {
		thrt->left = bt;
		pre = thrt;
		inThread(bt);
		pre->RTag = THREAD;
		pre->right = thrt;
		thrt->right = pre;
	}
	return thrt;
}
void print(ThreadTree* bt) {
	ThreadTree* p = bt->left;
	while (p != bt) {
		while (p->LTag == LINK)
			p = p->left;
		printf("%c", p->data);
		while (p->RTag == THREAD&&p->right != bt) {
			p = p->right;
			printf("%c", p->data);
		}
		p = p->right;
	}
}
void insert(ThreadTree* p, ThreadTree* x) {//此处的x结点为待插入的线索二叉树
	//此处x是插入p的左子树，且x只含左子树，则x子树的后继永远都是x或其孩子，不会影响到p
	if (p->LTag == THREAD) {//p结点原来没有左子树
		ThreadTree* temp = p->left;//记录原来p的前驱
		p->LTag = LINK;
		p->left = x;
		x->right = p;
		//找到x子树访问的第一个结点
		while (x->LTag == LINK)
			x = x->left;
		x->left = temp;

	}
	else {//如果p原来有左子树
		ThreadTree* temp = p->left;//暂时存储p的左子树
		p->left = x;
		x->right = temp;
	}
}
int main() {
	ThreadTree* node = creat("abcd", "bcad");
	ThreadTree* x = creat("gh", "hg");
	node = Thread(node);
	x = Thread(x);
	//insert(node->left->left, x->left);//插入到b结点下
	insert(node->left, x->left);//插入到a结点下
	print(node);
}