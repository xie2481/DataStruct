#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
}Tree;
Tree* creat() {
	FILE* file = fopen("test.txt", "r");
	char buffer[100];
	Tree* queue[100];
	Tree* root = NULL;
	int front = 0, rear = -1;
	while (fgets(buffer, 100, file)) {
		if (buffer[0] == '^'&&buffer[1] != '^') {//Ϊ�����
			root = (Tree*)malloc(sizeof(Tree));
			root->data = buffer[1];
			root->left = root->right = NULL;
			queue[++rear] = root;
		}
		else if(buffer[1]!='^'){//����δ����
			Tree* t = NULL,*node=NULL;
			/*Ѱ�Ҵ�������ĸ��ڵ�*/
			while (queue[front]->data != buffer[0])
				front++;
			t = queue[front];
			node = (Tree*)malloc(sizeof(Tree));
			node->data = buffer[1];
			node->left = node->right = NULL;
			if (buffer[2] == 'L')
				t->left = node;
			else
				t->right = node;
			queue[++rear] = node;
		}
	}
	return root;
}
void print(Tree* t) {
	if (t) {
		printf("%c", t->data);
		print(t->left);
		print(t->right);
	}
}
int main() {
	Tree* t=creat();
	print(t);
	printf("\n");
	return 0;
}