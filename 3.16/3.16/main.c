#include <stdio.h>
#include <stdlib.h>
int main() {
	int n=0,top=-1,i=0;//ָʾջ��
	char box = 0;
	printf("��������ܹ��ĳ���n\n");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		printf("�����뵱ǰ���������(H��ʾӲ��,S��ʾ����)\n");
		getchar();
		scanf("%c", &box);
		if (box == 'S' || box == 's') {
			printf("push pop\n");
		}
		else {
			printf("push\n");
			top++;
		}
	}
	if (top != -1) {
		while (top >= 0) {
			printf("pop\n");
			top--;
		}
	}
	return 0;
}