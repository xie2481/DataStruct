#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
int compare(char* s) {
	int i = 0,length=(int)strlen(s);
	if (((length - 2) & 1) != 0)//长度不符
		return FALSE;
	while (i < length-1) {
		if (s[i] == '&')
			break;
		i++;
	}
	if (i == length-1)//不含&符号
		return FALSE;
	if (i* 2 == length - 2) {
		int j = length - 2;
		int k = 0;
		while (k < i) {
			if (s[k] != s[j])
				return FALSE;
			k++;
			j--;
		}
		return TRUE;
	}
	else
		return FALSE;
}
int main() {
	char s[100];
	printf("请输入一个以@字符序列结束的序列\n");
	gets(s);
	if (compare(s) == TRUE) {
		printf("该串符合格式\n");
	}
	else {
		printf("该串不符合格式\n");
	}
	return 0;
}