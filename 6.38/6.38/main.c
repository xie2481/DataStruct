/*²Î¿¼²©¿Íhttp://blog.csdn.net/zww0815/article/details/51275335*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
}Tree;
typedef struct {
	Tree* node;
	int visited;
}Paired;
Paired* init(Tree* t,int boolean) {
	Paired* pair = (Paired*)malloc(sizeof(Paired));
	pair->node = t;
	pair->visited = boolean;
}
char* subString(char* s, int i, int j) {
	if (i < j&&i >= 0 && j <= strlen(s)) {
		char* temp = (char*)malloc(sizeof(char)*(j - i));
		int k = 0;
		for (k = 0; k < j - i; k++)
			temp[k] = s[k + i];
		temp[k] = '\0';
		return temp;
	}
	else
		return NULL;
}
Tree* creat(char* preOrder, char* inOrder) {
	if (preOrder) {
		Tree* node = (Tree*)malloc(sizeof(Tree));
		node->data = preOrder[0];
		char ch = preOrder[0];
		int i = 0, len = strlen(inOrder);
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
void printByNoRecursion(Tree* t) {
	Paired* stack[100];
	int k = -1;
	stack[++k] = init(t,FALSE);
	while (k != -1) {
		int visited = stack[k]->visited;
		t = stack[k]->node;
		k--;
		if (t == NULL)
			continue;
		if (visited)
			printf("%c", t->data);
		else {
			stack[++k] = init(t,TRUE);
			stack[++k] = init(t->right, FALSE);
			stack[++k] = init(t->left, FALSE);
		}
	}
}
int main() {
	Tree* node = creat("abc", "bac");
	printByNoRecursion(node);
	printf("\n");
	return 0;
}