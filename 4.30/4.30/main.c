//采用后缀数组，其中排序使用快排时间复杂度为o(nlogn)，找最长重复子串时间为o(n)，设找到的最长重复子串长度为i,则kmp的
//时间复杂度为o(n+i),所以最后的时间复杂度为o(nlogn)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXV 1000
char ca[MAXV][MAXV];
int compare(char* s, char* t) {//s和t拥有相同的后缀，因此只需比较他们的前缀即可
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
		printf("最长的重复子串为%.*s\n", maxLen, ca[maxi]);
		st = (char*)malloc(sizeof(char)*maxLen);
		for (i = 0; i < maxLen; i++)
			st[i] = ca[maxi][i];
		st[i] = '\0';
		printf("第一次出现的位置在%d\n", kmp(s, st));
	}
}
int main() {
	getLongestString("herrro");
	return 0;
}