#include <stdio.h>
#include <stdlib.h>
int main() {//һ���ƶ�O(k(n-1)��)��o(n)��
	int n = 0,*A=NULL,i=0,k=0;
	scanf("%d%d", &n,&k);
	A = (int*)malloc(sizeof(int)*(n + 1));
	for (i = 0; i < n; i++)
		A[i] = i;
	k = k%n;//ÿn����λһ��ѭ��
	while (k > 0) {
		A[n] = A[0];//�洢��һ����λ��Ԫ��
		A[0] = A[n - 1];
		for (i = n - 1; i >= 1; i--)
			A[i] = A[i - 1];
		A[1] = A[n];
		k--;
	}
	for (i = 0; i < n; i++)
		printf("%d\t", A[i]);
	printf("\n");
	/*for (i = 0; i < n; i++)
		scanf("%d", &A[i]);*/
	return 0;
}