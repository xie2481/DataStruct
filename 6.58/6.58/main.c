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
void insert(ThreadTree* p, ThreadTree* x) {//�˴���x���Ϊ�����������������
	//�˴�x�ǲ���p������������xֻ������������x�����ĺ����Զ����x���亢�ӣ�����Ӱ�쵽p
	if (p->LTag == THREAD) {//p���ԭ��û��������
		ThreadTree* temp = p->left;//��¼ԭ��p��ǰ��
		p->LTag = LINK;
		p->left = x;
		x->right = p;
		//�ҵ�x�������ʵĵ�һ�����
		while (x->LTag == LINK)
			x = x->left;
		x->left = temp;

	}
	else {//���pԭ����������
		ThreadTree* temp = p->left;//��ʱ�洢p��������
		p->left = x;
		x->right = temp;
	}
}
int main() {
	ThreadTree* node = creat("abcd", "bcad");
	ThreadTree* x = creat("gh", "hg");
	node = Thread(node);
	x = Thread(x);
	//insert(node->left->left, x->left);//���뵽b�����
	insert(node->left, x->left);//���뵽a�����
	print(node);
}