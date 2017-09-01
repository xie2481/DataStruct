#include <stdio.h>
#include <stdlib.h>
typedef struct CBTree {
	char data;
	struct CBTree* firstChild;
	struct CBTree* brother;
}CBTree;
CBTree* creat() {
	FILE* f = fopen("test.txt","r");
	CBTree* root = NULL;
	CBTree* queue[100];
	int front = 0, rear = -1;
	char buffer[100];
	while (fgets(buffer, 100, f)) {
		if (buffer[0]=='^'&&buffer[1]!='^') {//当前结点为根结点
			root = (CBTree*)malloc(sizeof(CBTree));
			root->data = buffer[1];
			queue[++rear] = root;
			root->firstChild = root->brother = NULL;
		}
		else if(buffer[0]!='^'&&buffer[1]!='^'){
			CBTree* node = (CBTree*)malloc(sizeof(CBTree));
			node->data = buffer[1];
			node->firstChild = node->brother = NULL;
			while (queue[front]->data != buffer[0])
				front++;
			if (queue[front]->firstChild == NULL) {
				queue[front]->firstChild = node;
			}
			else {
				CBTree* ptail = queue[front]->firstChild;
				while (ptail->brother)
					ptail = ptail->brother;
				ptail->brother = node;
			}
			queue[++rear] = node;
		}
	}
	fclose(f);
	return root;
}
void print(CBTree* t,int space) {
	if (t) {
		int i = 0;
		for (i = 0; i < space; i++)
			printf(" ");
		printf("%c\n", t->data);
		print(t->firstChild, space + 1);
		print(t->brother, space);
	}
}
int main() {
	CBTree* t = creat();
	print(t,0);
	return 0;
}