#include <stdio.h>
void traverse(int* A,int length) {
	int low = 0, high = length - 1;
	while (low < high) {
		int temp = A[low];
		A[low] = A[high];
		A[high] = temp;
		low++;
		high--;
	}
}
int main() {
	int A[10] = { 1,2,3,4,5,6,7,8,9,10 },i=0;
	traverse(A, 10);
	for (i = 0; i < 10; i++) {
		printf("%d\t", A[i]);
	}
	printf("\n");
	return 0;
}