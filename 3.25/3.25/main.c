#include <stdio.h>
#include <stdlib.h>
int FwithRecursion(int n) {
	if (n == 0)
		return 1;
	else
		return n*FwithRecursion(n / 2);
}
int FwithNoRecursion(int n) {
	int* F = (int*)malloc(sizeof(int)*(n + 1));
	F[0] = 1;
	int i = 1;
	for (i = 1; i <= n; i++) {
		F[i] = i*F[i / 2];
	}
	return F[n];
}
int main() {
	int n = 0;
	printf("请输入n的值\n");
	scanf("%d", &n);
	printf("递归版本的F(n)=%d\n", FwithRecursion(n));
	printf("非递归版本的F(n)=%d\n", FwithNoRecursion(n));
	return 0;
}