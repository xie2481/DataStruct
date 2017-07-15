#include <stdio.h>
#include <limits.h>
#define MAXV 10
int length = MAXV;//定义A表的长度
void getSort(int* A, int* B) {//因为A表单调递增，所以只需判断A[i]和A[i-1]，若2者相等，则A[i]重复不用与B表进行对比,直接删除
	int i = 0, j = 0, isTrue = 0;
	for (i = 0; i < MAXV; i++) {
		isTrue = 0;
		for (j = 0; j < MAXV; j++) {
			if (A[i] < B[j])
				break;
			if (A[i] == B[j])
				isTrue = 1;
		}
		if (isTrue == 0||(i<MAXV-1&&A[i]==A[i+1]&&A[i]!=INT_MAX))
			A[i] = INT_MAX;
	}
}
int main() {
	int A[MAXV] = { 1,2,3,3,5,6,7,8,9,10 };
	int B[MAXV] = { 3,3,5,7,8,9,10,11,12,13};
	int i = 0;
	getSort(A, B);
	for (i = 0; i < MAXV; i++) {
		if(A[i]!=INT_MAX)
			printf("%d\t", A[i]);
	}
}