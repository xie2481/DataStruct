//设A=（a1,…,am)和B=（b1,…,bn)均为顺序表，A丶和B丶分别为A和B中除去最大共同前缀后的子表（例如A=（x,y,y,z,x,z),
//B=(x,y,y,z,y,x,x,z),则两者中最大的共同前缀为（x,y,y,z)在两表中除去最大共同前缀后的子表分别为A丶=（x,z)，B丶=（y,x,x,z))。
//若A丶=B丶=空表，则A=B，若A丶=空表，而B丶≠空表，或者两者均不为空表，且A丶的首元小于B丶的首元，则A＜B，否则A>B。试写一个比较A
//B大小的算法(注意不要破坏A，B表）
#include <stdio.h>
#define MAXV 10
int compare(int* A,int lengthA, int* B,int lengthB) {
	int i = 0, j = 0;
	while (i < lengthA&&j < lengthB) {
		if (A[i] == B[j]) {
			i++;
			j++;
		}
		else
			break;
	}
	if (i == lengthA&&j == lengthB)
		return 0;
	else if ((i == lengthA&&j != lengthB) || ((i != lengthA&&j != lengthB) && (A[i] < B[j])))
		return -1;
	else
		return 1;
}
int main() {
	int A[6] = { 1,2,3,1,4, };
	int B[7] = { 1,2,3,1,4 };
	int result = compare(A, 5, B, 5);
	switch (result)
	{
	case 0:
		printf("A=B\n");
		break;
	case -1:
		printf("A<B\n");
		break;
	case 1:
		printf("A>B\n");
		break;
	}
	return 0;
}