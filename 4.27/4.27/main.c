/*书上的算法在比较a^nb,a^kb(n>=k)时，需要比较(k+1)^(n-1)次，当前程序算法需要比较(k-1)^(n-2)+k次*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char* SString;
SString StrAssign(char* s) {
	int i = 0,len=strlen(s);
	SString t = (char*)malloc(sizeof(char)*(len+1));
	t[0] = len;
	for (i = 1; i <= len; i++)
		t[i] = s[i - 1];
	return t;
}
int Index(SString S, SString T, int pos) {
	int i = pos, j = 1;
	while (i <= S[0] && j <= T[0]) {
		if (j == 1 && (S[i] != T[j] || S[i + T[0] - 1] != T[T[0]])) {
			i++;
			continue;
		}
		else {
			i++;
			j++;
		}
		if (i<=S[0]&&S[i] == T[j]) {
			i++;
			j++;
		}
		else if(j<=T[0]){
			i = i - j + 2;
			j = 1;
		}
	}
	if (j > T[0])
		return i - T[0];
	else
		return 0;
}
int main() {
	SString s = StrAssign("haaaebo");
	SString t = StrAssign("ab");
	printf("%d\n", Index(s, t, 1));
}