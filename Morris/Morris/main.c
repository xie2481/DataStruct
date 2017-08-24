/*��ʹ��ջ�͵ݹ飬ͬʱ�����parent�ڵ�������������ο�����http://blog.csdn.net/laojiu_/article/details/50820093*/
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
void inTravel(Tree* t) {//ʵ���������
	Tree* cur = t;
	Tree* pre = NULL;
	while (cur) {
		if (cur->left == NULL) {//��ǰ���û��ǰ��Ԫ��
			printf("%c", cur->data);
			cur = cur->right;
		}
		else {
			//�ҵ�cur��ǰ��
			pre = cur->left;
			while (pre->right&&pre->right!=cur)
				pre = pre->right;
			if (pre->right == NULL) {//��ǰ��������cur�����������
				pre->right = cur;
				cur = cur->left;
			}
			else {//��ԭ���Ľṹ
				pre->right = NULL;
				printf("%c", cur->data);
				cur = cur->right;
			}
		}
	}
}
void preTravel(Tree* t) {//�������
	Tree* cur = t;
	Tree* post = NULL;
	while (cur) {
		if (cur->left == NULL) {//cur������������
			printf("%c", cur->data);
			cur = cur->right;
		}
		else {
			post = cur->left;//��cur������������ʱ���һ�����ʵĽ��
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
				//�������cur��������ǰ�����·���ϵ����н��
				dump = dump->left;
				while (dump) {
					stack[++k] = dump->data;
					dump = dump->right;
				}
				while (k != -1) {
					printf("%c", stack[k--]);
				}
				if (cur->right) {
					if (!cur->right->left && !cur->right->right) {//��ǰ��������������һ��Ҷ�ӽ�㣬�޷����ݣ�ֱ�����
						printf("%c", cur->right->data);
						if(cur!=t)
							printf("%c", cur->data);
					}
				}
				cur = cur->right;
			}
		}
	}
	//������������
	printf("%c", t->data);
}
int main() {
	Tree* node = creat("abcdghef", "bdcgaehf");
	//preTravel(node);
	postTravel(node);
	printf("\n");
	return 0;
}