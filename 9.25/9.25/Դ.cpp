#include <stdio.h>
#include <stdlib.h>
int Search_Seq(int* A, int Size) {
	int key = A[Size - 1];
	int i = 0;
	for (i = 0; A[i] != key; i++);
	return i;
}
int main() {
	int A[] = { 1,5,4,3,4 };
	printf("%d", Search_Seq(A, 5));
}