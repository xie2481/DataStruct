#include <stdio.h>
#define M 5
#define N 3
int visited[M][N] = { 0 };
void changeColor(int g[][N], int i0, int j0,int color) {
	if (visited[i0][j0] == 0) {
		visited[i0][j0] = 1;
		if (i0 - 1 >= 0 && g[i0 - 1][j0] == g[i0][j0])
			changeColor(g, i0 - 1, j0, color);
		if (i0 + 1 < M&&g[i0 + 1][j0] == g[i0][j0])
			changeColor(g, i0 + 1, j0, color);
		if (j0 - 1 >= 0 && g[i0][j0 - 1] == g[i0][j0])
			changeColor(g, i0, j0 - 1, color);
		if (j0 + 1 < N&&g[i0][j0 + 1] == g[i0][j0])
			changeColor(g, i0, j0 + 1, color);
		g[i0][j0] = color;
	}
	else
		return;
}
int main() {
	int g[M][N] = { {1,2,3},{3,1,2},{1,3,2},{1,1,2},{3,3,3} },i=0,j=0;
	changeColor(g, 3, 1,5);
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			printf("%d\t", g[i][j]);
		}
		printf("\n");
	}
	return 0;
}