#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;
char* substring(char* s, int i, int j) {
	if (i >=j)
		return NULL;
	int k = 0;
	char* t = (char*)malloc(sizeof(char)*(j - i));
	for (k = 0; k < j - i; k++)
		t[k] = s[i + k];
	t[k] = '\0';
	return t;
}
TreeNode* creat(char* preOrder,char* inOrder){
	if (preOrder) {
		TreeNode* p = (TreeNode*)malloc(sizeof(TreeNode));
		int i = 0,len=strlen(preOrder);
		p->data = preOrder[0];
		while (preOrder[0] != inOrder[i]) i++;
		p->left = creat(substring(preOrder, 1, i+1),substring(inOrder,0,i));
		p->right = creat(substring(preOrder, i + 1, len), substring(inOrder, i + 1, len));
		return p;
	}
	else
		return NULL;
}
void dfs(TreeNode* p) {
	if(p) dfs(p->left), dfs(p->right), printf("%c", p->data);
}
int main() {
	TreeNode* p = creat("*2-35", "2*3-5");
	dfs(p);
}