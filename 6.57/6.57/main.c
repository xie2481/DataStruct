#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum{LINK,THREAD}Flag;
typedef struct ThreadTreeNode {
	char data;
	struct ThreadTreeNode* left;
	struct ThreadTreeNode* right;
	struct ThreadTreeNode* parent;
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
ThreadTree* creat(ThreadTree* parent,char* preOrder, char* inOrder) {
	if (preOrder) {
		ThreadTree* node = (ThreadTree*)malloc(sizeof(ThreadTree));
		char ch = preOrder[0];
		int i = 0, len = strlen(inOrder);
		node->data = ch;
		node->LTag = node->RTag = LINK;
		node->parent = parent;
		while (i < len) {
			if (ch == inOrder[i])
				break;
			i++;
		}
		node->left = creat(node,subString(preOrder, 1, i+1), subString(inOrder, 0, i));
		node->right = creat(node,subString(preOrder, i + 1, len), subString(inOrder, i + 1, len));
		return node;
	}
	else
		return NULL;
}
void postThread(ThreadTree* t) {
	if (t) {
		postThread(t->left);
		postThread(t->right);
		if (!t->left) {
			t->LTag = THREAD;
			t->left = pre;
		}
		if (!pre->right) {
			pre->RTag = THREAD;
			pre->right = t;
		}
		pre = t;
	}
}
ThreadTree* Thread(ThreadTree* bt) {
	ThreadTree* thrt = (ThreadTree*)malloc(sizeof(ThreadTree));
	thrt->LTag = LINK;
	thrt->RTag = THREAD;
	thrt->right = thrt;
	thrt->parent = NULL;
	if (!bt)
		thrt->left = thrt;
	else {
		thrt->left = bt;
		bt->parent = thrt;
		pre = thrt;
		postThread(bt);
		thrt->right = pre;
	}
	return thrt;
}
void print(ThreadTree* t) {
	ThreadTree* p = t->left;
	//�ҵ���һ�����ʵĽ��
	while (1) {
		while (p->LTag == LINK)
			p = p->left;
		if (p->RTag == LINK)
			p = p->right;
		else
			break;
	}
	while (p != t) {
		printf("%c", p->data);
		if (p->parent == t)//pΪ�������ĸ����,û�к��
			p = t;
		else if (p->RTag == THREAD)//p�ĺ��ֱ�ӱ���¼(pΪ��˫�׵��Һ��ӻ�������û��������)
			p = p->right;
		else {//pΪ��˫�׵����ӣ�����˫�׵���������Ϊ��
			//�ҵ���˫�׵��������ں�������е�һ�����ʵĽ�㣬��Ϊp�ĺ��
			ThreadTree* ps = p->parent;
			while (ps->RTag == LINK) {
				ps = ps->right;
				while (ps->LTag == LINK)
					ps = ps->left;
			}
			p = ps;
		}
	}
}
ThreadTree* getNode(ThreadTree* t,char ch) {
	ThreadTree* node = NULL;
	if (t->data == ch)
		node = t;
	if (!node&&t->LTag == LINK)
		node = getNode(t->left, ch);
	if (!node&&t->RTag == LINK)
		node = getNode(t->right, ch);
	return node;
}
ThreadTree* getPostNode(ThreadTree* p) {//�õ�p���ĺ��
	if (p->RTag == THREAD)//pΪ�����ڸ��ڵ���Һ��ӻ�Ϊ�����������Һ���Ϊ��
		return p->right;
	else if (p->parent->parent == NULL)//pΪ�ս�㣬����Ϊ��
		return NULL;
	else {//pΪ�丸�ڵ�����������Һ��Ӳ�Ϊ��
		//�ҵ��丸�ڵ��������ں�������з��ʵĵ�һ����㣬��Ϊp�ĺ��
		p = p->parent;
		while (p->right == LINK) {
			p = p->right;
			while (p->left == LINK)
				p = p->left;
		}
		return p;
	}
}
int main() {
	ThreadTree* node = creat(NULL,"abcd", "bcad");
	node = Thread(node);
	ThreadTree* p = getNode(node,'c');
	ThreadTree* post = getPostNode(p);
	printf("%c", post->data);
}
