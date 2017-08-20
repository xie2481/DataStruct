#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* L;
char* R;
void init(int n) {
	L = (char*)malloc(sizeof(char)*(n + 1));
	R = (char*)malloc(sizeof(char)*(n + 1));
	memset(L, -1, sizeof(char)*(n + 1));
	memset(R, -1, sizeof(char)*(n + 1));//-1��ʾ��ǰ���δ��ȷ��
}
char* subString(char* s, int i, int j) {
	int len = strlen(s);
	if (i < j&&i >= 0 && j <=len) {
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
void creat(char* preOrder, char* inOrder,int p) {//��p������������
	if (preOrder != NULL) {
		int len = strlen(inOrder);
		char ch = preOrder[0];
		int i = 0;
		while (i < len) {
			if (ch == inOrder[i])
				break;
			i++;
		}
		if (i - 1 < 0) {//û�����֧
			L[p] = '0';
			R[p] = preOrder[i + 1];
		} 
		if (i + 1 >= len) {//û���ҷ�֧
			R[p] = '0';
			L[p] = preOrder[1];
		}
		if (i - 1 >= 0 && i + 1 < len) {//���ҷ�֧����
			L[p] = preOrder[1];
			R[p] = preOrder[i + 1];
		}
		if (i - 1 < 0 && i + 1 >= len) {//���ҷ�֧��û��
			R[p] = '0';
			L[p] = '0';
		}
		creat(subString(preOrder, 1, i + 1), subString(inOrder, 0, i), p + 1);
		creat(subString(preOrder, i + 1, strlen(preOrder)), subString(inOrder, i + 1, strlen(inOrder)),p+2);
	 }
}
int isChild(char u, char v) {//�ж�u�Ƿ�Ϊv������(Ĭ��u��v��������)
	if (L[v - '0'] == u || R[v - '0'] == u)
		return 1;
	else {
		int resultL = 0, resultR = 0;
		if (L[v - '0'] != '0')
			resultL = isChild(u, L[v- '0']);
		if (R[v - '0'] != '0')
			resultR = isChild(u, R[v - '0']);
		if (resultL || resultR)
			return 1;
		else
			return 0;
	}
}
int main(){
	int i = 0;
	init(3);
	char* preOrder = "123";
	char* inOrder = "213";
	L[0] = R[0] =preOrder[0];//�洢�����
	creat(preOrder,inOrder,1); 
	printf("%d\n", isChild('2', '1'));
}