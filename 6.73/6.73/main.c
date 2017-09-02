#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct CBTreeNode {
	char data;
	struct CBTreeNode* brother;
	struct CBTreeNode* firstChild;
}CBTree;
int spilt(char* s, int low, int high) {//split the string to find a child of current node
	int i = low,brace=0;
	if (low == high)//the last match element
		return low+1;
	while (s[i]!=','||brace) {
		if (s[i] == '(')
			brace++;
		if (s[i] == ')')
			brace--;
		i++;
	}
	return i;
}
CBTree* creat(char* s, int low, int high) {
	if (low <= high) {
		CBTree* node = (CBTree*)malloc(sizeof(CBTree)), *ptail =NULL;
		int i = low+2;
		node->data = s[low];
		node->firstChild = node->brother = NULL;
		//find all children of current node
		while (i <= high - 1) {
			int sp = spilt(s, i, high - 1);
			if (node->firstChild == NULL) {
				node->firstChild = creat(s, i, sp - 1);
				node->firstChild->brother = NULL;
				ptail = node->firstChild;
			}
			else {
				ptail->brother = creat(s, i, sp - 1);
				ptail->brother->brother = NULL;
				ptail = ptail->brother;
			}
			i = sp + 1;
		}
		return node;
	}
	else
		return NULL;
}
void print(CBTree* t) {
	if (t) {
		printf("%c", t->data);
		print(t->firstChild);
		print(t->brother);
	}
}
int main() {
	char* s = "A(B(E,F),C(G),D)";
	CBTree* t = creat(s, 0, strlen(s) - 1);
	print(t);
	return 0;
}