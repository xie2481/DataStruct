#include <stdio.h>
int main() {
	char s[100];
	int top1=-1, top2=-1,top3=-1,i=0;//ָʾ3��ջ
	gets(s);
	while (s[i] != '\0') {
		if (s[i] == '(')
			top1++;
		else if (s[i] == ')')
			top1--;
		else if (s[i] == '[')
			top2++;
		else if (s[i] == ']')
			top2--;
		else if (s[i] == '{')
			top3++;
		else if (s[i] == '}')
			top3--;
		i++;
	}
	if (top1 == -1 && top2 == -1&&top3==-1) {
		printf("��������ƥ��\n");
	}
	else {
		printf("�������Ų�ƥ��\n");
	}
	return 0;
}