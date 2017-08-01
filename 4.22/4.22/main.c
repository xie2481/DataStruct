//StrAssign��4.21���Ѳ��ԣ��ʱ����򲻶Ըú���������
#include <stdio.h>
#include <stdlib.h>
typedef unsigned char Elem;
typedef struct LinkedList {//�������ͷ����������洢�������ĳ���,��˴��ĳ����޶����Ϊ255
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
void StrStr(LinkedList* T, LinkedList* S,Elem e) {//Ĭ��T,S����Ϊ��
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
	if(T->data==length)//û���ҵ�ָ��Ԫ��
		pre->next = S->next;
}
int main() {
	LinkedList* L = init(),*S=init(),*p=NULL;
	StrAssign(L, "hello");
	StrAssign(S, "wqqr");
	StrStr(L, S, 'e');
	p = L->next;
	printf("��ǰT��Ϊhello��S��Ϊwqqr,�����ַ�Ϊe,���Խ������:");
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
	StrAssign(L, "hello");
	StrAssign(S, "w");
	StrStr(L, S, 'e');
	p = L->next;
	printf("��ǰT��Ϊhello��S��Ϊw,�����ַ�Ϊe,���Խ������:");
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
	StrAssign(L, "hello");
	StrAssign(S, "w");
	StrStr(L, S, 'h');
	p = L->next;
	printf("��ǰT��Ϊhello��S��Ϊw,�����ַ�Ϊh,���Խ������:");
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
	StrAssign(L, "hello");
	StrAssign(S, "w");
	StrStr(L, S, 'h');
	p = L->next;
	printf("��ǰT��Ϊhello��S��Ϊw,�����ַ�Ϊh,���Խ������:");
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
	StrAssign(L, "hello");
	StrAssign(S, "w");
	StrStr(L, S, 'o');
	p = L->next;
	printf("��ǰT��Ϊhello��S��Ϊw�������ַ�Ϊo���Խ������:");
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
	StrAssign(L, "hello");
	StrAssign(S, "w");
	StrStr(L, S, 'z');
	p = L->next;
	printf("��ǰT��Ϊhello��S��Ϊw,�����ַ�Ϊz,���Խ������:");
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
}