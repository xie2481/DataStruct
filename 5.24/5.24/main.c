#include <stdio.h>
#include <stdarg.h>
#define MAX_DIM 8//定义数组的最大维度为8
typedef struct {
	int* base;//数组元素基址
	int dim;//数组的维度
	int* bounds;//数组的维界基址
	int* constants;//数组映像函数基址
}Array;
Array* initArray(int dim, ...) {
	if (dim >= 1 && dim <= MAX_DIM) {
		Array* A = (Array*)malloc(sizeof(Array));
		va_list va;//存储各个维度的信息的可变参数列表
		int i = 0, total = 1;//total记录A数组的元素个数，以为base分配空间做准备
		A->dim = dim;
		A->bounds = (int*)malloc(sizeof(int)*dim);
		va_start(va, dim);//va的地址指向dim
		for (i = 0; i < dim; i++) {
			A->bounds[i] = va_arg(va, int);//将每个维度的值传给数组的维界基址
			total *= A->bounds[i];
		}
		va_end(va);
		A->base = (int*)malloc(sizeof(int)*total);//分配A所需的所有元素空间
		A->constants = (int*)malloc(sizeof(int)*dim);
		//求公式当中的bi，即数组映像函数基址
		A->constants[dim - 1] = 1;
		for (i = dim - 2; i >= 0; i--) {
			A->constants[i] = A->constants[i + 1] * A->bounds[i + 1];
		}
		return A;
	}
	else
		return NULL;
}
int Locate(Array* A, int* off, va_list va) {//得到va列表中存储的元素位置对应的地址,用off来存储
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
void Value(Array* A, int* e, ...) {////将列表中的值对应地址的元素的值给e
	va_list va;
	int off = 0;
	va_start(va, e);
	if (Locate(A, &off, va) == 0)
		return;
	else
		*e = *(A->base + off);
}
void Assign(Array* A, int e, ...) {//将列表中的值对应地址的元素的值赋为e
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