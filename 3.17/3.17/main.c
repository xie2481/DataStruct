#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
int compare(char* s) {
	int i = 0,length=(int)strlen(s);
	if (((length - 2) & 1) != 0)//���Ȳ���
		return FALSE;
	while (i < length-1) {
		if (s[i] == '&')
			break;
		i++;
	}
	if (i == length-1)//����&����
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
	printf("������һ����@�ַ����н���������\n");
	gets(s);
	if (compare(s) == TRUE) {
		printf("�ô����ϸ�ʽ\n");
	}
	else {
		printf("�ô������ϸ�ʽ\n");
	}
	return 0;
}