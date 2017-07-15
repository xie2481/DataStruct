#include <stdio.h>
#include <limits.h>
#define MAXV 10
void getSort(int* A, int* B, int* C) {
	int i = 0, j = 0, k = 0, isTrue = 0;;
	for (i = 0; i < MAXV; i++) {
		isTrue = 0;
		for (j = 0; j < MAXV; j++) {
			if (A[i] < B[j])
				break;
			if (A[i] == B[j]) {
				for (k = 0; k < MAXV; k++) {
					if (A[i] < C[k])
						break;
					if (A[i] == C[k])
						isTrue = 1;
				}
			}
		}
		if (isTrue == 0) {
			int temp = A[i];
			A[i] = INT_MAX;
			int t = i + 1;
			if (t < MAXV) {
				while (A[t] == temp) {
					A[t] = INT_MAX;
					t++;
				}
				i = t-1;
			}
		}
		else {
			int t = i + 1;
			if (t < MAXV) {
				while (A[t++] == A[i])
					;
				i = t-2;
			}
		}
	}
}
int main() {
	int A[MAXV] = { 1,2,3,4,5,5,7,8,9,10 };
	int B[MAXV] = { 3,3,5,7,9,10,11,12,13,14 };
	int C[MAXV] = { 4,5,9,10,11,12,13,14,15,16 };
	int i = 0;
	getSort(A, B, C);
	for (i = 0; i < MAXV; i++) {
		if (A[i] != INT_MAX)
			printf("%d\t", A[i]);
	}
	printf("\n");
	return 0;
}