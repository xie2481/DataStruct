#include <stdio.h>
#include <stdarg.h>
#define MAX_DIM 8//������������ά��Ϊ8
typedef struct {
	int* base;//����Ԫ�ػ�ַ
	int dim;//�����ά��
	int* bounds;//�����ά���ַ
	int* constants;//����ӳ������ַ
}Array;
Array* initArray(int dim, ...) {
	if (dim >= 1 && dim <= MAX_DIM) {
		Array* A = (Array*)malloc(sizeof(Array));
		va_list va;//�洢����ά�ȵ���Ϣ�Ŀɱ�����б�
		int i = 0, total = 1;//total��¼A�����Ԫ�ظ�������Ϊbase����ռ���׼��
		A->dim = dim;
		A->bounds = (int*)malloc(sizeof(int)*dim);
		va_start(va, dim);//va�ĵ�ַָ��dim
		for (i = 0; i < dim; i++) {
			A->bounds[i] = va_arg(va, int);//��ÿ��ά�ȵ�ֵ���������ά���ַ
			total *= A->bounds[i];
		}
		va_end(va);
		A->base = (int*)malloc(sizeof(int)*total);//����A���������Ԫ�ؿռ�
		A->constants = (int*)malloc(sizeof(int)*dim);
		//��ʽ���е�bi��������ӳ������ַ
		A->constants[dim - 1] = 1;
		for (i = dim - 2; i >= 0; i--) {
			A->constants[i] = A->constants[i + 1] * A->bounds[i + 1];
		}
		return A;
	}
	else
		return NULL;
}
int Locate(Array* A, int* off, va_list va) {//�õ�va�б��д洢��Ԫ��λ�ö�Ӧ�ĵ�ַ,��off���洢
	int i = 0;
	*off = 0;
	for (i = 0; i < A->dim; i++) {
		int ind = va_arg(va, int);
		if (ind < 0 || ind >= A->bounds[i])
			return 0;
		*off += A->constants[i] * ind;
	}
	return 1;
}
void Value(Array* A, int* e, ...) {////���б��е�ֵ��Ӧ��ַ��Ԫ�ص�ֵ��e
	va_list va;
	int off = 0;
	va_start(va, e);
	if (Locate(A, &off, va) == 0)
		return;
	else
		*e = *(A->base + off);
}
void Assign(Array* A, int e, ...) {//���б��е�ֵ��Ӧ��ַ��Ԫ�ص�ֵ��Ϊe
	va_list va;
	int off = 0;
	va_start(va, e);
	if (Locate(A, &off, va) == 0)
		return;
	else
		*(A->base + off) = e;
}
int main() {
	Array* A = initArray(2,4,4);
	int e = 0;
	Assign(A, 5, 0, 1);
	Assign(A, 7, 1, 3);
	Value(A, &e, 1, 3);
	printf("%d\n", e);
	return 0;
}