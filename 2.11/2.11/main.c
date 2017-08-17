#include <stdio.h>
int main() {
	int A[5] = { 1,3,9,45 };
	int x = 46, i = 0, k = 0;
	for (i = 0; i < 4; i++)
		if (x <= A[i])
			break;
	for (k = 4; k >= i + 1; k--)
		A[k] = A[k - 1];
	A[i]= x;
	for (i = 0; i < 5; i++)
		printf("%d\t", A[i]);
	return 0;
}