#include <stdio.h>
#include <stdlib.h>
#define MAXV 10
int* getSort(int * A, int* B,int* length) {
	int* C = (int*)malloc(sizeof(int) * 2 * MAXV), i = 0, j = 0, z = 0;
	for (i = 0; i < MAXV; i++) {
		for (j = 0; j < MAXV; j++) {
			if (A[i] == B[j]) {
				C[z++] = A[i];
				(*length)++;
			}
			if (A[i] < B[j])
				break;
		}
	}
	return C;
}
int main() {
	int A[MAXV] = { 1,2,3,4,5,6,7,8,9,10 };
	int B[MAXV] = { 10,11,12,13,14,15,16,17,18,19 };
	int length = 0,i=0;
	int* C = getSort(A,B,&length);
	if (C != NULL) {
		for (i = 0; i < length; i++)
			printf("%d\t", C[i]);
	}
	return 0;
}