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
LinkedList* Concat(LinkedList* T, LinkedList* S) {//要求T，S串的长度和不能超过255,否则R串会溢出
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
	printf("------------------开始测试StrASSign-------------\n");
	StrAssign(L1, "hello");
	p1 = L1->next;
	printf("L1串为：");
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("------------------开始测试StrCopy----------------\n");
	StrAssign(L2, "hello");
	printf("L2串等于hello,进行相等测试:%d\n", StrCompare(L1, L2));
	StrAssign(L2, "a");
	printf("L2串等于a,进行大于测试:%d\n", StrCompare(L1, L2));
	StrAssign(L2, "m");
	printf("L2串等于m,进行小于测试:%d\n", StrCompare(L1, L2));
	StrAssign(L2, "hell");
	printf("L2串等于hell,进行L1串长度长于L2时的比较测试:%d\n", StrCompare(L1, L2));
	StrAssign(L2, "helloa");
	printf("L2串等于helloa,进行L2串长度长于L1串时的比较测试:%d\n", StrCompare(L1, L2));
	printf("------------------开始测试StrLength---------------\n");
	printf("L1串的长度=%d\n", StrLength(L1));
	printf("------------------开始测试Concat------------------\n");
	printf("L1串等于hello,L2串等于helloa,进行Concat测试:");
	L3 = Concat(L1, L2);
	p1 = L3->next;
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("-----------------开始测试SubString-----------------\n");
	printf("首先测试不合法的情况，以hello串进行测试\n");
	printf("首先测试Sub串为空的情况:%s\n", SubString(init(), 1, 0));
	printf("接着测试pos不合法的情况,pos为0的情况和pos为6的情况:%s %s\n", SubString(L1, 0, 1), SubString(L1, 6, 1));
	printf("测试len不合法的情况,在pos=1的情况下测试,len为-1和6的情况 %s %s\n", SubString(L1, 1, -1), 
		SubString(L1, 1, 6));
	printf("开始测试正常运行的情况\n");
	printf("Sub串为hello\n");
	printf("开始测试len为3,pos为1的情况:");
	L3 = SubString(L1, 1, 3);
	p1 = L3->next;
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("开始测试len为5,pos为1的情况:");
	L3 = SubString(L1, 1, 5);
	p1 = L3->next;
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("开始测试len为3,pos为2的情况:");
	L3 = SubString(L1, 2, 3);
	p1 = L3->next;
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("开始测试len为4,pos为2的情况:");
	L3 = SubString(L1, 2, 4);
	p1 = L3->next;
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("开始测试len为1,pos为5的情况:");
	L3 = SubString(L1, 5, 1);
	p1 = L3->next;
	while (p1) {
		printf("%c", p1->data);
		p1 = p1->next;
	}
	printf("\n");
	printf("------------------------测试完毕------------------------\n");
}
