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
//��ΪֻҪ��ʱ�临�Ӷȣ����������ռ临�Ӷȣ�����ջ�����һ���洮���Ƚ��������Ƿ����,1Ϊ�Գƣ�0Ϊ���Գ�
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
	printf("���Ե����ַ�����ǰ��Ϊh�����Խ��Ϊ:%d\n", isSymmetry(L));
	StrAssign(L, "heasd");
	printf("�����������ȵĲ��Գ��ַ�,��ǰ��Ϊheasd�����Ϊ��%d\n", isSymmetry(L));
	StrAssign(L, "head");
	printf("����ż�����ȵĲ��Գ��ַ�,��ǰ��Ϊhead,���Ϊ��%d\n", isSymmetry(L));
	StrAssign(L, "ouuo");
	printf("����ż�����ȵĶԳ��ַ�����ǰ��Ϊouuo,���Ϊ:%d\n", isSymmetry(L));
	StrAssign(L, "ouauo");
	printf("�����������ȵĶԳ��ַ�,��ǰ��Ϊouauo,���Ϊ��%d\n", isSymmetry(L));
	return 0;
}