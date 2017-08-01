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
void StrCopy(LinkedList* T, LinkedList* S) {
	LinkedList* p = S->next, *ptail = T;
	while (p) {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->data = p->data;
		node->next = NULL;
		ptail->next = node;
		ptail = node;
		p = p->next;
	}
}
int StrCompare(LinkedList* T, LinkedList* S) {
	LinkedList* p1 = T->next, *p2 = S->next;
	while (p1&&p2) {
		if (p1->data < p2->data)
			return -1;
		else if (p1->data > p2->data)
			return 1;
		else {
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	if (!p1 && !p2)
		return 0;
	else if (p1)
		return 1;
	else
		return -1;
}
int StrLength(LinkedList* L) {
	return L->data;
}
LinkedList* Concat(LinkedList* T, LinkedList* S) {//Ҫ��T��S���ĳ��ȺͲ��ܳ���255,����R�������
	LinkedList* R = (LinkedList*)malloc(sizeof(LinkedList));
	LinkedList* ptail = R, *p1 = T->next, *p2 = S->next;
	R->data = StrLength(T)+StrLength(S);
	R->next = NULL;
	while (p1) {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->data = p1->data;
		node->next = NULL;
		ptail->next = node;
		ptail = node;
		p1 = p1->next;
	}
	while (p2) {
		LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
		node->data = p2->data;
		node->next = NULL;
		ptail->next = node;
		ptail = node;
		p2 = p2->next;
	}
	return R;
}
LinkedList* SubString(LinkedList* Sub, int pos, int len) {
	if (Sub->next
		&&pos >= 1&& pos <= StrLength(Sub)
		&& len >= 0 && len <= StrLength(Sub) - pos + 1) {
		LinkedList* R = (LinkedList*)malloc(sizeof(LinkedList)),*p=Sub,*ptail=R;
		int i = 0;
		R->data = len;
		R->next = NULL;
		for (i = 0; i < pos;i++) {
			p = p->next;
		}
		for (i = pos; i <= len + pos - 1; i++) {
			LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
			node->data = p->data;
			node->next = NULL;
			ptail->next = node;
			ptail = node;
			p = p->next;
		}
		return R;
	}
	else
		return NULL;
}
int main() {
	LinkedList* L1 =init(),*L2=init(),*p1=NULL,*L3=init();
	printf("------------------��ʼ����StrASSign-------------\n");
	StrAssign(L1, "hello");
	p1 = L1->next;
	printf("L1��Ϊ��");
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("------------------��ʼ����StrCopy----------------\n");
	StrAssign(L2, "hello");
	printf("L2������hello,������Ȳ���:%d\n", StrCompare(L1, L2));
	StrAssign(L2, "a");
	printf("L2������a,���д��ڲ���:%d\n", StrCompare(L1, L2));
	StrAssign(L2, "m");
	printf("L2������m,����С�ڲ���:%d\n", StrCompare(L1, L2));
	StrAssign(L2, "hell");
	printf("L2������hell,����L1�����ȳ���L2ʱ�ıȽϲ���:%d\n", StrCompare(L1, L2));
	StrAssign(L2, "helloa");
	printf("L2������helloa,����L2�����ȳ���L1��ʱ�ıȽϲ���:%d\n", StrCompare(L1, L2));
	printf("------------------��ʼ����StrLength---------------\n");
	printf("L1���ĳ���=%d\n", StrLength(L1));
	printf("------------------��ʼ����Concat------------------\n");
	printf("L1������hello,L2������helloa,����Concat����:");
	L3 = Concat(L1, L2);
	p1 = L3->next;
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("-----------------��ʼ����SubString-----------------\n");
	printf("���Ȳ��Բ��Ϸ����������hello�����в���\n");
	printf("���Ȳ���Sub��Ϊ�յ����:%s\n", SubString(init(), 1, 0));
	printf("���Ų���pos���Ϸ������,posΪ0�������posΪ6�����:%s %s\n", SubString(L1, 0, 1), SubString(L1, 6, 1));
	printf("����len���Ϸ������,��pos=1������²���,lenΪ-1��6����� %s %s\n", SubString(L1, 1, -1), 
		SubString(L1, 1, 6));
	printf("��ʼ�����������е����\n");
	printf("Sub��Ϊhello\n");
	printf("��ʼ����lenΪ3,posΪ1�����:");
	L3 = SubString(L1, 1, 3);
	p1 = L3->next;
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("��ʼ����lenΪ5,posΪ1�����:");
	L3 = SubString(L1, 1, 5);
	p1 = L3->next;
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("��ʼ����lenΪ3,posΪ2�����:");
	L3 = SubString(L1, 2, 3);
	p1 = L3->next;
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("��ʼ����lenΪ4,posΪ2�����:");
	L3 = SubString(L1, 2, 4);
	p1 = L3->next;
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("��ʼ����lenΪ1,posΪ5�����:");
	L3 = SubString(L1, 5, 1);
	p1 = L3->next;
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("------------------------�������------------------------\n");
}
