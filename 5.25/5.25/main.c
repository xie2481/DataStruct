#include <stdio.h>
#include <stdlib.h>
int main() {
	int V1[4] = { 15,22,-6,9 };
	int B1[3][4] = { {1,0,0,1},{0,1,0,0},{1,0,0,0} };
	int V2[3] = { 33,11,25 };
	int B2[3][4] = { {1,0,0,0},{0,1,0,0},{0,1,0,0} };
	int V3[7] = { 0 };//进行加法后，非零元最大个数为2个矩阵非零元个数和
	int B3[3][4] = { 0 };
	int i = 0, j = 0,k1=0,k2=0,k3=0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++) {
			if (B1[i][j] && B2[i][j]) {
				if (V1[k1] + V2[k2]) {
					V3[k3++] = V1[k1++] + V2[k2++];
					B3[i][j] = 1;
				}
			}
			else if (B1[i][j]) {
				V3[k3++] = V1[k1++];
				B3[i][j] = 1;
			}
			else if (B2[i][j]) {
				V3[k3++] = V2[k2++];
				B3[i][j] = 1;
		   }
		}
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++) {
			printf("%d\t", B3[i][j]);
		}
		printf("\n");
	}
	i = 0;
	while (i < 7 && V3[i]) {
		printf("%d\t", V3[i++]);
	}
	printf("\n");
	return 0;
}