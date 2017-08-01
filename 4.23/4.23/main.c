#include <stdio.h>
#include <stdlib.h>
typedef unsigned char Elem;
typedef struct LinkedList {//方便起见头结点的数据域存储整个串的长度,因此串的长度限定最大为255
	Elem data;
	struct LinkedList* next;
}LinkedList;
LinkedList* init() {
	LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList));
	L->data = 0;
	L->next = NULL;
	return L;
}
void StrAssign(LinkedList* L, char* s) {
	int i = 0;
	LinkedList* ptail = L;
	while (s[i] != '\0') {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->data = s[i];
		node->next = NULL;
		ptail->next = node;
		ptail = node;
		L->data++;
		i++;
	}
}
//因为只要求时间复杂度，所以牺牲空间复杂度，再用栈构造出一根逆串，比较两个串是否相等,1为对称，0为不对称
int isSymmetry(LinkedList* L) {
	LinkedList* R = init(),*p=L->next,*p1=NULL;
	R->data = L->data;
	R->next = NULL;
	while (p) {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->data = p->data;
		node->next = R->next;
		R->next = node;
		p = p->next;
	}
	p = L->next;
	p1 = R->next;
	while (p) {
		if (p->data != p1->data)
			return 0;
		p = p->next;
		p1 = p1->next;
	}
	return 1;
}
int main() {
	LinkedList* L = init();
	StrAssign(L, "h");
	printf("测试单个字符，当前串为h，测试结果为:%d\n", isSymmetry(L));
	StrAssign(L, "heasd");
	printf("测试奇数长度的不对称字符,当前串为heasd，结果为：%d\n", isSymmetry(L));
	StrAssign(L, "head");
	printf("测试偶数长度的不对称字符,当前串为head,结果为：%d\n", isSymmetry(L));
	StrAssign(L, "ouuo");
	printf("测试偶数长度的对称字符，当前串为ouuo,结果为:%d\n", isSymmetry(L));
	StrAssign(L, "ouauo");
	printf("测试奇数长度的对称字符,当前串为ouauo,结果为：%d\n", isSymmetry(L));
	return 0;
}