#include <stdio.h>
typedef struct {
	int i;
	int j;
	int data;
}TriGroup;
int main() {
	//算法默认矩阵按行序升序排列
	//很明显算法复杂度为o(len(a)+len(b))
	TriGroup A[10];
	TriGroup B[5];
	int i = 0, j = 0, k = 0;
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
	B[4].j = 0;
	B[4].data = 5;
	for (j = 0; j < 5; j++) {
		if (A[i].i == B[j].i&&A[i].j == B[j].j) {
			A[i].data += B[j].data;
			B[j].data = 0;
			++i;
		}
	}
	i = 5;
	for (j = 0; j < 5; j++) {
		if (B[j].data) {
			A[i].i = B[j].i;
			A[i].j = B[j].j;
			A[i++].data = B[j].data;
		}
	}
	for (k = 0; k < i; k++) {
		printf("%d %d %d\n", A[k].i, A[k].j, A[k].data);
	}
}