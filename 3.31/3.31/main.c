#include <stdio.h>
#include <string.h>
int main() {
	char s[100];
	int i = 0,j=0,flag=1;
	gets(s);
	i= strlen(s)-2;
	while (j < i) {
		if (s[j] != s[i]) {
			flag = 0;
			break;
		}
		j++;
		i--;
	}
	if (flag) {
		printf("是回文串\n");
	}
	else {
		printf("不是回文串\n");
	}
	return 0;
}