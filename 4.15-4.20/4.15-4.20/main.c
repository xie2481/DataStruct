#include <stdio.h>
#include <stdlib.h>
#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN + 1];//0号单元存储串的长度
void StrAssign(SString t, char* chars) {
	int i = 1, len = 0;
	while (chars[len++] != '\0')
		;
	t[0] = len-1;
	while (i <=t[0]) {
		t[i] = chars[i - 1];
		i++;
	}
	t[i] = '\0';
}
int StrCompare(SString S, SString T) {
	int i = 1, j = 1;
	while (i <= S[0] && j <= T[0]) {
		if (S[i] < T[j])
			return -1;
		else if (S[i] > T[j])
			return 1;
		i++;
		j++;
	}
	if (i <=S[0] && j-1 == T[0])
		return 1;
	else if (i-1 == S[0] && j <=T[0])
		return -1;
	else
		return 0;

}
void Replace(SString S, SString T, SString V) {
	int i = 0,j=0,flag=0;
	for (i = 1; i <= S[0]; i++) {
		flag = 1;
		for (j = 1; j <= T[0]; j++) {
			if (S[i + j-1] != T[j])
				flag = 0;
		}
		if (flag == 1) {//符合替换条件
			if (T[0] < V[0]) {
				for (j =S[0]+1; j >= i+T[0]; j--) {
					S[j + V[0] - T[0]] = S[j];
				}
			}
			for (j = 1; j <= V[0]; j++) {
				S[i + j - 1] = V[j];
			}
			if (T[0] > V[0]) {
				for (j = i + T[0]; j <= S[0] + 1; j++) {
					S[j + V[0] - T[0]] = S[j];
				}
			}
			i = i + V[0];//重新调整i指向的位置
			S[0] = S[0] - T[0] + V[0];
		}
	}
}
int* getDifferentChar(SString S) {
	int* number = (int*)malloc(sizeof(int) * (MAXSTRLEN+2)),i=1;
	for (i = 0; i <=MAXSTRLEN+1; i++) {
		number[i] = 0;
	}
	for (i = 1; i <= S[0]; i++) {
		if (number[S[i]+1] == 0)
			number[0]++;
		number[S[i]+1]++;
	}
	return number;
}
int* getNewString(SString s, SString t, SString r) {
	int i = 0, j = 0,flag=0,*number=(int*)malloc(sizeof(int)*(MAXSTRLEN+1));
	r[0] = 0;
	for (i = 0; i <= MAXSTRLEN; i++)
		number[i] = 0;
	for (i = 1; i <= s[0]; i++) {
		flag = 1;
		for (j = 1; j <= t[0]; j++) {
			if (s[i] == t[j])
				flag = 0;
		}
		if (flag) {//满足条件
			r[0]++;
			r[r[0]] = s[i];
			if (number[s[i]] == 0)
				number[s[i]] = i;
		}
	}
	r[r[0] + 1] = '\0';
	return number;
}
void Delete(SString s, SString t) {
	int i = 0, j = 0, flag = 0;
	for (i = 1; i <= s[0]; i++) {
		flag = 1;
		for (j = 1; j <= t[0]; j++) {
			if (s[i] != t[j])
				flag = 0;
		}
		if (flag) {//是相同的串
			for (j = i + t[0]; j <= s[0] + 1; j++)
				s[j - t[0]] = s[j];
		}
	}
}
int main() {
	SString s,T,V,r;
	int i = 0, *number = NULL;
	StrAssign(s, "h");
	StrAssign(T, "hehlh");
	StrAssign(V, "@");
	for (i = 1; i <=T[0]; i++) {
		printf("%c", T[i]);
	}
	printf("\n");
	printf("%d\n", StrCompare(s, T));
	//Replace(T, s, V);
	for (i = 1; i <= T[0]; i++) {
		printf("%c", T[i]);
	}
	printf("\n");
	number = getDifferentChar(T);
	printf("不同的字符数为%d\n", number[0]);
	for (i = 1; i <= MAXSTRLEN + 1; i++) {
		if (number[i] != 0) {
			printf("%c的个数为%d\n", i-1, number[i]);
		}
	}
	number = getNewString(T, s, r);
	for (i = 1; i <= r[0]; i++)
		printf("%c", r[i]);
	printf("\n");
	for(i=0;i<=MAXSTRLEN;i++)
		if (number[i] != 0) {
			printf("%c第一次出现的位置为%d\n", i, number[i]);
		}
	Delete(T, s);
	for (i = 1; i <= T[0]; i++)
		printf("%c", T[i]);
	printf("\n");
	return 0;
}