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
	printf("������һ����������Ҫ��ľ���\n");
	scanf("%lf%lf", &A,&e);
	printf("�ݹ�汾sqrt(%lf)=%.3lf\n",A, sqrtWithRecursion(A, A, e));
	printf("�ǵݹ�汾sqrt(%lf)=%.3lf\n",A, sqrtWithNoRecursion(A, A,e));
}