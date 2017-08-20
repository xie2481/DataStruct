#include <stdio.h>
#include <math.h>
int getDepth(int i) {
	double temp = log2(i);
	if (temp - (int)temp > 0)
		return (int)temp + 1;
	else
		return (int)temp;
}
int getNumber(int i) {
	int depth = getDepth(i);
	int total = 1<<(depth-1);
	while (i!=1) {
		if (i != i / 2 * 2) {//ÎªÓÒ·ÖÖ§
			total += 1 << (depth-getDepth(i));
		}
		i /= 2;
	}
	return total;
}
int main() {
	printf("%d\n", getNumber(5)); 
}
