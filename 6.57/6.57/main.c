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
	//找到第一个访问的结点
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
		if (p->parent == t)//p为二叉树的根结点,没有后继
			p = t;
		else if (p->RTag == THREAD)//p的后继直接被记录(p为其双亲的右孩子或左孩子且没有右子树)
			p = p->right;
		else {//p为其双亲的左孩子，且其双亲的右子树不为空
			//找到其双亲的右子树在后序遍历中第一个访问的结点，即为p的后继
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
ThreadTree* getPostNode(ThreadTree* p) {//得到p结点的后继
	if (p->RTag == THREAD)//p为其所在父节点的右孩子或为其左孩子且其右孩子为空
		return p->right;
	else if (p->parent->parent == NULL)//p为空结点，其后继为空
		return NULL;
	else {//p为其父节点的左孩子且其右孩子不为空
		//找到其父节点右子树在后序遍历中访问的第一个结点，即为p的后继
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
