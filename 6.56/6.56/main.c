/*存储结构如ThreadTree结构体定义所示*/
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
			if(ch==inOrder[i])
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
void preThread(ThreadTree* p) {
	if (p) {
		if (!p->left) {
			p->LTag = THREAD;
			p->left = pre;
		}
		if (!pre->right) {
			pre->RTag = THREAD;
			pre->right = p;
		}
		pre = p;
		if (p->LTag ==LINK)
			preThread(p->left);
		if(p->RTag==LINK)
			preThread(p->right);
	}
}
ThreadTree* Thread(ThreadTree* bt) {
	ThreadTree* thrt = (ThreadTree*)malloc(sizeof(ThreadTree));
	thrt->LTag = LINK;
	thrt->RTag = THREAD;
	thrt->right = thrt;
	if (!bt)
		thrt->left = thrt;
	else {
		thrt->left = bt;
		pre = thrt;
		preThread(bt);
		pre->RTag = THREAD;
		pre->right = thrt;
		thrt->right = pre;
	}
	return thrt;
}
ThreadTree* getNode(ThreadTree* t, char ch) {
	ThreadTree* p = t->left;
	ThreadTree* node = NULL;
	while (p != t) {
		if (p->data == ch)
			node = p;
		if (p->LTag == LINK)
			p = p->left;
		else
			p = p->right;
	}
	return node;
}
ThreadTree* getPostNode(ThreadTree* p) {
	if (p&&p->LTag == LINK)
		return p->left;
	else
		return p->right;
}
int main() {
	ThreadTree* node = creat("abcd", "bcad");
	node = Thread(node);
	ThreadTree* p = getNode(node,'c');
	p = getPostNode(p);
	printf("%c", p->data);
}
