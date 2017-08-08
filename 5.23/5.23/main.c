#include <stdio.h>
typedef struct {
	int j;
	int data;
}TwoGroup;
int main() {
	TwoGroup A[3];
	int LineStart[3];
	int i = 0,k=0;
	A[0].j = 1;
	A[0].data = 5;
	A[1].j = 3;
	A[1].data = 7;
	A[2].j = 2;
	A[2].data = 9;
	LineStart[0] = -1;//第0行没有非零元
	LineStart[1] = 0;
	LineStart[2] = 2;
	while (i < 3) {
		if (LineStart[i] != -1) {//该行有非零元
			printf("%d %d %d\n", i, A[LineStart[i]].j, A[LineStart[i]].data);
			LineStart[i]++;
			if (i < 2 && LineStart[i] == LineStart[i + 1])
				i++;
			if (i == 2 && LineStart[i] == 3)
				i++;
		} else
			i++;
	}
}