//���ú�׺���飬��������ʹ�ÿ���ʱ�临�Ӷ�Ϊo(nlogn)������ظ��Ӵ�ʱ��Ϊo(n)�����ҵ�����ظ��Ӵ�����Ϊi,��kmp��
//ʱ�临�Ӷ�Ϊo(n+i),��������ʱ�临�Ӷ�Ϊo(nlogn)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXV 1000
char ca[MAXV][MAXV];
int compare(char* s, char* t) {//s��tӵ����ͬ�ĺ�׺�����ֻ��Ƚ����ǵ�ǰ׺����
	int i = 0;
	while (*s && (*s++ == *t++)) {
		++i;
	}
	return i;
}
int* getNext(char* s) {
	int i = 0, j = -1,len=strlen(s),*next=(int*)malloc(sizeof(int)*len);
	next[i] = -1;
	while (i < len-1) {
		if (j == -1 || s[i] == s[j]) {
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
	return next;
}
int kmp(char* s, char* t) {
	int i = 0, j = 0, lens = strlen(s), lent = strlen(t),*next=NULL;
	next = getNext(t);
	while (i < lens&&j < lent) {
		if (j == -1 || s[i] == t[j]) {
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j == lent)
		return i - lent + 1;
	else
		return -1;
}
void getLongestString(char* s) {
	int i = 0, len = strlen(s), temp = 0, maxLen = 0, maxi = 0;
	char* st = NULL;
	for (i = 0; i < len; i++)
		strcpy(ca[i],&s[i]);
	qsort(ca, len, sizeof(char)*MAXV,strcmp);
	for (i = 0; i < len - 1; i++) {
		temp = compare(ca[i], ca[i + 1]);
		if (temp > maxLen) {
			maxLen = temp;
			maxi = i;
		}
	}
	if (maxLen != 0) {
		printf("����ظ��Ӵ�Ϊ%.*s\n", maxLen, ca[maxi]);
		st = (char*)malloc(sizeof(char)*maxLen);
		for (i = 0; i < maxLen; i++)
			st[i] = ca[maxi][i];
		st[i] = '\0';
		printf("��һ�γ��ֵ�λ����%d\n", kmp(s, st));
	}
}
int main() {
	getLongestString("herrro");
	return 0;
}