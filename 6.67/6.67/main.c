/*测试用例为题目所示的树*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_SIZE 100
typedef struct CBNode {
	char data;
	struct CBNode* brother;
	struct CBNode* firstChild;
}CBNode;
CBNode* creat() {
	FILE* f = fopen("test.txt", "r");
	char buffer[100];
	CBNode* root = NULL;
	CBNode* queue[100];
	int front = 0, rear = -1;
	while (fgets(buffer, 100, f)!=NULL) {
		if (buffer[0] == '^'&&buffer[1] != '^') {//为根结点
			root = (CBNode*)malloc(sizeof(CBNode));
			root->data = buffer[1];
			root->firstChild = root->brother = NULL;
			queue[++rear] = root;
		}
		else if(buffer[0]!='^'&&buffer[1]!='^'){
			CBNode* node = (CBNode*)malloc(sizeof(CBNode));
			node->data = buffer[1];
			node->brother = node->firstChild = NULL;
			while (queue[front]->data != buffer[0])
				front++;
			if (queue[front]->firstChild == NULL) 
				queue[front]->firstChild = node;
			else {
				node->brother = queue[front]->firstChild;
				queue[front]->firstChild = node;
			}
			queue[++rear] = node;
		}
		else
			break;
	}
	fclose(f);
	return root;
}
void printCBTree(CBNode* t) {
	if (t) {
		printf("%c", t->data);
		printCBTree(t->firstChild);
		printCBTree(t->brother);
	}
}
int main() {
	CBNode* t = creat();
	printCBTree(t);
	printf("\n");
	return 0;
}