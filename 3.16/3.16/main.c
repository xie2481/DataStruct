#include <stdio.h>
#include <stdlib.h>
int main() {
	int n=0,top=-1,i=0;//指示栈顶
	char box = 0;
	printf("请输入火车总共的车厢n\n");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		printf("请输入当前车厢的类型(H表示硬座,S表示软座)\n");
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