#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main() {
	int m = 0, n = 0, i = 0, j = 0, max = INT_MIN, min = INT_MAX, **A = NULL, mi = -1, mj = -1,k=0;
	scanf("%d%d", &m, &n);
	A = (int**)malloc(sizeof(int*)*m);
	for (i = 0; i < m; i++)
		A[i] = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	for (i = 0; i < m; i++) {
		min = INT_MAX;
		for (j = 0; j < n; j++) {//�ҳ�ÿһ�е���Сֵ
			if (min > A[i][j]) {
				min = A[i][j];
				mi =i;
				mj =j;
			}
		}
		//�жϸõ��ǲ��Ǹ��е����ֵ
		max = A[mi][mj];
		for (k = 0; k < m; k++) {
			if (max < A[k][mj])
				max = A[k];
		}
		if (max == A[mi][mj])
			printf("����Ϊ%d %d\n", mi, mj);
	}
}