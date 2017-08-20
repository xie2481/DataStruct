#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* L;
char* R;
char* T;
void init(int n) {
	L = (char*)malloc(sizeof(char)*(n + 1));
	R = (char*)malloc(sizeof(char)*(n + 1));
	T = (char*)malloc(sizeof(char)*(n + 1));
	memset(L, -1, sizeof(char)*(n + 1));
	memset(R, -1, sizeof(char)*(n + 1));//-1表示当前结点未被确认
	memset(T, -1, sizeof(char)*(n + 1));
	T[1] = '0';
}
char* subString(char* s, int i, int j) {
	int len = strlen(s);
	if (i < j&&i >= 0 && j <= len) {
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
void creat(char* preOrder, char* inOrder, int p) {//求p结点的左右子树
	if (preOrder != NULL) {
		int len = strlen(inOrder);
		char ch = preOrder[0];
		int i = 0;
		while (i < len) {
			if (ch == inOrder[i])
				break;
			i++;
		}
		if (i - 1 < 0) {//没有左分支
			L[p] = '0';
			R[p] = preOrder[i + 1];
		}
		if (i + 1 >= len) {//没有右分支
			R[p] = '0';
			L[p] = preOrder[1];
		}
		if (i - 1 >= 0 && i + 1 < len) {//左右分支均有
			L[p] = preOrder[1];
			R[p] = preOrder[i + 1];
		}
		if (i - 1 < 0 && i + 1 >= len) {//左右分支均没有
			R[p] = '0';
			L[p] = '0';
		}
		creat(subString(preOrder, 1, i + 1), subString(inOrder, 0, i), p + 1);
		creat(subString(preOrder, i + 1, strlen(preOrder)), subString(inOrder, i + 1, strlen(inOrder)), p + 2);
	}
}
void creatArrayT(int m) {
	int i = 1;
	for (i = 1; i <= m; i++) {
		if (L[i] != '0')//L[i]结点不为空，设置L[i]结点的双亲结点
			T[L[i] - '0'] = i + '0';
		else
			T[L[i] - '0'] = '0';
		if (R[i] != '0')
			T[R[i] - '0'] = i + '0';
		else
			T[R[i] - '0'] = '0';
	}
}
int isChild(int u,int v) {
	while (T[u - '0'] != v&&u!='0')
		u = T[u - '0'];
	if (u != '0')
		return 1;
	else
		return 0;
}
int main() {
	char* preOrder = "123";
	char* inOrder = "213";
	int i = 1;
	init(3);
	creat(preOrder, inOrder, 1);
	creatArrayT(3);
	/*for (i = 1; i <= 3; i++)
		printf("%c", T[i]);*/
	printf("%d", isChild('2', '1'));
	return 0;
}