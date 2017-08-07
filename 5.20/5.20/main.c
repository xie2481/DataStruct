#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
	int m = 2,i=0,j=0,k=0;
	int A[3][3] = { {2,0,4},
	{-1,3,0},{1,0,0} };
	int total = 0;
	for (i = m; i >= 0; i--) {
		for (j = m; j >= 0; j--) {
			if (A[i][j]) {
				total++;
				if (A[i][j] != 1) {
					if (total != 1 && A[i][j] > 0)
						printf("+%d", A[i][j]);
					else if (A[i][j] == -1)
						printf("-");
					else 
						printf("%d", A[i][j]);
				}
				else if (total != 1)
					printf("+");
				if (i != 0) {
					printf("x1");
					if (i != 1)
						printf("Ee%d", i);
				}
				if (j != 0) {
					printf("x2");
					if (j != 1)
						printf("Ee%d", j);
				}
			}
		}
	}
	printf("\n");
};