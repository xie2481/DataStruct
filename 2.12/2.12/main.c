//��A=��a1,��,am)��B=��b1,��,bn)��Ϊ˳���Aؼ��Bؼ�ֱ�ΪA��B�г�ȥ���ͬǰ׺����ӱ�����A=��x,y,y,z,x,z),
//B=(x,y,y,z,y,x,x,z),�����������Ĺ�ͬǰ׺Ϊ��x,y,y,z)�������г�ȥ���ͬǰ׺����ӱ�ֱ�ΪAؼ=��x,z)��Bؼ=��y,x,x,z))��
//��Aؼ=Bؼ=�ձ���A=B����Aؼ=�ձ���Bؼ�ٿձ��������߾���Ϊ�ձ���Aؼ����ԪС��Bؼ����Ԫ����A��B������A>B����дһ���Ƚ�A
//B��С���㷨(ע�ⲻҪ�ƻ�A��B��
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