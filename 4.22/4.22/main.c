//StrAssign在4.21中已测试，故本程序不对该函数做测试
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
void StrStr(LinkedList* T, LinkedList* S,Elem e) {//默认T,S均不为空
	LinkedList* p1 = T->next,*pre=T, *ptail = S->next;
	int length = T->data;
	while (p1) {
		if (p1->data == e) {
			LinkedList* p = p1->next;
			p1->next = S->next;
			while (ptail->next)
				ptail = ptail->next;
			ptail->next = p;
			T->data += S->data;
		}
		p1 = p1->next;
		pre = pre->next;
	}
	if(T->data==length)//没有找到指定元素
		pre->next = S->next;
}
int main() {
	LinkedList* L = init(),*S=init(),*p=NULL;
	StrAssign(L, "hello");
	StrAssign(S, "wqqr");
	StrStr(L, S, 'e');
	p = L->next;
	printf("当前T串为hello，S串为wqqr,测试字符为e,测试结果如下:");
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
	StrAssign(L, "hello");
	StrAssign(S, "w");
	StrStr(L, S, 'e');
	p = L->next;
	printf("当前T串为hello，S串为w,测试字符为e,测试结果如下:");
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
	StrAssign(L, "hello");
	StrAssign(S, "w");
	StrStr(L, S, 'h');
	p = L->next;
	printf("当前T串为hello，S串为w,测试字符为h,测试结果如下:");
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
	StrAssign(L, "hello");
	StrAssign(S, "w");
	StrStr(L, S, 'h');
	p = L->next;
	printf("当前T串为hello，S串为w,测试字符为h,测试结果如下:");
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
	StrAssign(L, "hello");
	StrAssign(S, "w");
	StrStr(L, S, 'o');
	p = L->next;
	printf("当前T串为hello，S串为w，测试字符为o测试结果如下:");
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
	StrAssign(L, "hello");
	StrAssign(S, "w");
	StrStr(L, S, 'z');
	p = L->next;
	printf("当前T串为hello，S串为w,测试字符为z,测试结果如下:");
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
}