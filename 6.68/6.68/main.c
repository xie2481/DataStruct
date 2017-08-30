/*测试用例为6.67的示例树*/
#include <stdio.h>
#include <stdlib.h>
typedef struct CBNode {
	char data;
	struct CBNode* brother;
	struct CBNode* firstChild;
}CBNode;
typedef struct {
	CBNode* node;
	int degree;//当前结点的度
}Paired;
Paired* initPaired(CBNode* node, int degree) {
	Paired* p = (Paired*)malloc(sizeof(Paired));
	p->node = node;
	p->degree = degree;
	return p;
}
CBNode* creat() {
	FILE* f = fopen("test.txt", "r");
	char buffer[100];
	CBNode* root = NULL;
	Paired* queue[100];
	int front = 0, rear = -1;
	while (fgets(buffer, 100, f)) {
		if (root == NULL) {
			root = (CBNode*)malloc(sizeof(CBNode));
			root->data = buffer[0];
			root->brother = root->firstChild = NULL;
			if (buffer[1] - '0' != 0)
				queue[++rear] = initPaired(root, buffer[1] - '0');
			else
				break;
		}
		else {
			CBNode* node = (CBNode*)malloc(sizeof(CBNode));
			node->data = buffer[0];
			node->brother = node->firstChild = NULL;
			if (buffer[1] - '0' != 0)
				queue[++rear] = initPaired(node, buffer[1] - '0');
			if (queue[front]->node->firstChild == NULL)
				queue[front]->node->firstChild = node;
			else {
				node->brother = queue[front]->node->firstChild;
				queue[front]->node->firstChild = node;
			}
			queue[front]->degree--;
			if (!queue[front]->degree)
				front++;
		}
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