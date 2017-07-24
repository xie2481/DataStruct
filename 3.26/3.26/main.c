#include <stdio.h>
#include <math.h>
double sqrtWithRecursion(double A, double p, double e) {
	if (fabs(p*p - A) < e)
		return p;
	else
		return sqrtWithRecursion(A, (p + A / p) / 2.0, e);
}
double sqrtWithNoRecursion(double A,double p, double e) {
	while (fabs(p*p - A) >= e) {
		p = (p + A / p) / 2.0;
	}
	return p;
}
int main() {
	double A = 0.0,e=0.0;
	printf("请输入一个浮点数和要求的精度\n");
	scanf("%lf%lf", &A,&e);
	printf("递归版本sqrt(%lf)=%.3lf\n",A, sqrtWithRecursion(A, A, e));
	printf("非递归版本sqrt(%lf)=%.3lf\n",A, sqrtWithNoRecursion(A, A,e));
}