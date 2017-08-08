#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int i;
	int j;
	int data;
}TriGroup;
int main() {
	TriGroup A[5];
	TriGroup B[5];
	TriGroup C[10];
	int i = 0, j = 0,k=0;
	A[0].i = 0;
	A[0].j = 0;
	A[0].data = 1;
	A[1].i = 1;
	A[1].j = 1;
	A[1].data = 2;
	A[2].i = 1;
	A[2].j = 2;
	A[2].data = 3;
	A[3].i = 2;
	A[3].j = 1;
	A[3].data = 4;
	A[4].i = 2;
	A[4].j = 2;
	A[4].data = 5;

	B[0].i = 0;
	B[0].j = 0;
	B[0].data = 1;
	B[1].i = 1;
	B[1].j = 1;
	B[1].data = 2;
	B[2].i = 1;
	B[2].j = 2;
	B[2].data = 3;
	B[3].i = 2;
	B[3].j = 1;
	B[3].data = 4;
	B[4].i = 2;
	B[4].j = 2;
	B[4].data = 5;
	
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (A[i].i == B[j].i&&A[i].j == B[j].j) {
				A[i].data += B[j].data;
				B[j].data = 0;
				break;
			}
		}
		if (A[i].data) {
			C[k].i = A[i].i;
			C[k].j = A[i].j;
			C[k++].data = A[i].data;
		}
	}
	for (j = 0; j < 5; j++) {
		if (B[j].data) {
			C[k].i = B[i].i;
			C[k].j = B[i].j;
			C[k++].data = B[i].data;
		}
	}
	for (i = 0; i < k; i++) {
		printf("%d %d %d\n", C[i].i, C[i].j, C[i].data);
	}
	return 0;
}