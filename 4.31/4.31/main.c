#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int** dp;
int lens, lent;
int* getNext(char* s) {
	int len = strlen(s),i=0,j=-1;
	int* next = (int*)malloc(sizeof(int)*len);
	next[0] = -1;
	while (i < len) {
		if (j == -1 || s[i] == s[j]) {
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
	return next;
}
int getIndex(char* s, char* t,int pos) {
	int i = pos, j = 0, lens = strlen(s), lent = strlen(t);
	int* next = getNext(t);
	while (i < lens&&j < lent) {
		if (j == -1 || s[i] == t[j]) {
			++i;
			++j;
		}
		else
			j = next[j];
	}
	if (j == lent)
		return i - lent;
	else
		return -1;
}
void LIS(char* s, char* t) {//求一个最长公共子串，时间复杂度为o(n^2),求所有公共子串时直接使用kmp,时间复杂度为o(m*(m+子串的长度))
	int i = 0, j = 0;
	lens = strlen(s), lent = strlen(t);
	dp = (int**)malloc(sizeof(int*)*lens);
	for (i = 0; i < lens; i++) {
		dp[i] = (int*)malloc(sizeof(int)*lent);
		memset(dp[i], 0, sizeof(int)*lent);
	}
	for (i =0; i < lens; i++) {
		for (j = 0; j < lent; j++) {
			if (s[i] == t[j]) {
				if (i == 0 || j == 0)
					dp[i][j] = 1;
				else
					dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
				dp[i][j] = 0;
		}
	}
	int max = 0,maxi=0,maxj=0;
	for (i = 0; i < lens; i++) {
		for (j = 0; j < lent; j++) {
			if (dp[i][j] > max) {
				max = dp[i][j];
				maxi = i;
				maxj = j;
			}
		}
	}
	if (max != 0) {
		char* temp = (char*)malloc(sizeof(char)*max);
		int total = 0,j=0,index=-1;//计数变量
		printf("最长公共子串的长度为%d 且为:", max);
		for (i = maxi - max + 1; i <= maxi; i++) {
			printf("%c", s[i]);
			temp[j++] = s[i];
		}
		printf("\n");
		temp[j] = '\0';
		//所有的最长重复子串
		for (i = 0; i < lens; i++) {
			int pindex = getIndex(s, temp, i);
			if (pindex != -1 && pindex != index) {
				printf("第%d个最长重复子串出现在母串的%d的位置\n", ++total, pindex);
				index = pindex;
			}
		}
	}
}
int main() {
	LIS("hellell", "ell");
	return 0;
}