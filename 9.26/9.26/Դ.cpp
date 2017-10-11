#include <stdio.h>
void search(int* A, int low, int high,int* index,int target) {
	if (low > high)
		return;
	int mid = low + (high - low) / 2;
	if (A[mid] == target)
		*index = mid;
	else if (A[mid] < target)
		search(A, low, mid - 1, index, target);
	else
		search(A, mid + 1, high, index, target);
}
int main() {
	int A[] = { 1,5,8,10,12 };
	int index = -1;
	search(A, 0, 4, &index, 8);
	printf("%d", index);
}