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
		if (t->right == pre) {//t������������ʽ��������ݻ���һ�����
			pre = t;
			t = t->parent;
		}
		else if (pre != t->left) {//t����������δ������
			while (t->left) {
				pre = t;
				t = t->left;
			}
			printf("%c", t->data);
			if (t->right&&t->right != pre) {//������������������δ������
				pre = t;
				t = t->right; 
				continue;
			}
			else if(t->right==NULL){//��ǰ���������������
				pre = t;
				t = t->parent;
			}
			else {//�����������ʹ�
				pre = t;
				t = t->parent;
			}
		}
		else {//����t�������������߻���
			printf("%c", t->data);
			if (t->right&&t->right != pre) {//���������ڣ���δ�����ʹ�
				pre = t;
				t = t->right;
			}
			else {
				pre = t;
				if (t->parent)//t���Ǹ����
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