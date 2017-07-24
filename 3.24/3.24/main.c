#include <stdio.h>
int g(int m, int n) {
	printf("m=%d n=%d\n", m, n);
	if (m == 0 && n >= 0)
		return 0;
	else
		return g(m - 1, 2 * n) + n;
}
int main() {
	g(5, 2);
}