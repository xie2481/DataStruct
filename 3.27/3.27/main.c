#include <stdio.h>
int akmWithRecursion(int m, int n) {
	if (m == 0)
		return n + 1;
	else if(n == 0)
		return akmWithRecursion(m - 1, 1);
	else
		return akmWithRecursion(m - 1, akmWithRecursion(m, n - 1));
}
int akmWithNoRecursion(int m, int n) {
	int stack[100],top=-1;
	stack[++top] = m;
	while (top != -1) {
		m = stack[top--];
		if (!m) {
			n = n + 1;
		}
		else if (n == 0) {
			m = m - 1;
			n = 1;
			stack[++top] = m;
			printf("m=%d n=%d\n", stack[top], n);
		}
		else {
			n = n - 1;
			stack[++top] = m-1;
			printf("m=%d n=%d\n", stack[top], n);
			stack[++top] = m;
			printf("m=%d n=%d\n", stack[top], n);
		}
	}
	return n;
}
int main() {
	int m=0,n = 0;
	printf("请输入m n的值\n");
	scanf("%d%d",&m, &n);
	printf("递归版本的值为%d\n", akmWithRecursion(m,n));
	printf("非递归版本的值为%d\n", akmWithNoRecursion(m,n));
	return 0;
}