#include <stdlib.h>
#include <stdio.h>
#define LEFT 0
#define RIGHT 1
#define ERROR 0
#define OK 1
#define Status int 

// ����ڵ�
typedef struct XorNode
{
	// ������
	char data;
	// ָ����
	struct XorNode *LPPtr;
} XorNode, *XorPointer;


// ��ͷ�ڵ�����ָ��˫������
typedef struct {
	// �ֱ�ָ���������˺��Ҷ�
	XorPointer Left, Right;
} XorLinkedList;

XorPointer XorP(XorPointer p, XorPointer q);

// ��ӡ�������
void PrintXorList(XorLinkedList A, int direction);

// ����
Status InstertXorList(XorLinkedList &A, int i, XorNode *a);

// ɾ��
Status DeleteXorList(XorLinkedList &A, int i);

int main()
{
	XorLinkedList A;
	A.Right = A.Left = NULL;
	XorNode *a = (XorNode *)malloc(sizeof(XorNode));
	a->data = 'A';
	InstertXorList(A, 1, a);


	XorNode *b = (XorNode *)malloc(sizeof(XorNode));
	b->data = 'B';
	InstertXorList(A, 2, b);

	XorNode *c = (XorNode *)malloc(sizeof(XorNode));
	c->data = 'C';
	InstertXorList(A, 3, c);

	XorNode *d = (XorNode *)malloc(sizeof(XorNode));
	d->data = 'D';
	InstertXorList(A, 4, d);

	PrintXorList(A, LEFT);
	printf("\n");
	PrintXorList(A, RIGHT);

	printf("ɾ����һ���ڵ�\n");
	DeleteXorList(A, 1);
	PrintXorList(A, LEFT);
	printf("\n");

	getchar();
	return 0;
}

XorPointer XorP(XorPointer p, XorPointer q) {
	unsigned long x, y, z;
	x = (unsigned long)p;
	y = (unsigned long)q;
	z = x^y;
	return (XorPointer)z;
}

/************************************************************************/
/*
A ����������������
direction �����ķ���LEFT���ң�RIGHT���ҵ���
*/
/************************************************************************/
void PrintXorList(XorLinkedList A, int direction) {
	XorNode *p, *pre = NULL, *q = NULL;
	if (direction == LEFT)
	{
		p = A.Left;
	}
	else {
		p = A.Right;
	}

	while (p != NULL)
	{
		printf("%c", p->data);
		q = XorP(pre, p->LPPtr);
		pre = p;
		p = q;
	}
}

/************************************************************************/
/* ������ĵ�i���ڵ�֮ǰ����һ���ڵ㣬��1��ʼ���������                                                                     */
/************************************************************************/
Status InstertXorList(XorLinkedList &A, int i, XorNode *a) {
	if (i <= 0)
	{
		return ERROR;
	}
	XorNode *p = A.Left, *pre = NULL, *q;
	if (p == NULL)
	{
		A.Left = a;
		A.Right = a;
		a->LPPtr = NULL;
		return OK;
	}

	/*if (i == 1)
	{
		q = XorP(pre, p->LPPtr);// �ҵ���һ���ڵ㣬�Ա��޸�
		p->LPPtr = XorP(a, q);
		a->LPPtr = XorP(NULL, p);
		A.Left = a;
		return OK;
	}*/

	int count = 1;
	while (count < i && p != NULL)
	{
		q = XorP(pre, p->LPPtr);
		pre = p;
		p = q;
		count++;
	}

	// ���һ��λ�ò������⴦��
	if (p == NULL)
	{
		q = XorP(pre->LPPtr, NULL);
		pre->LPPtr = XorP(q, a);
		a->LPPtr = XorP(pre, NULL);
		A.Right = a;
	}
	else {
		q = XorP(pre->LPPtr, p);
		pre->LPPtr = XorP(q, a);
		q = XorP(pre, p->LPPtr);
		p->LPPtr = XorP(a, q);
		a->LPPtr = XorP(pre, p);
	}
	return OK;
}

/************************************************************************/
/* ɾ�������е�i���ڵ㣬��1��ʼ��߿�ʼ                                                                     */
/************************************************************************/
Status DeleteXorList(XorLinkedList &A, int i) {
	if (i <= 0)
	{
		return ERROR;
	}
	XorNode *p = A.Left, *pre = NULL, *q;
	int count = 1;
	if (p->LPPtr == NULL)
	{
		free(p);
		A.Left = NULL;
		A.Right = NULL;
		printf("����Ϊ�գ�����");
		return OK;
	}
	if (i == 1)
	{
		pre = XorP(p->LPPtr, NULL);
		q = XorP(pre->LPPtr, p);
		free(p);
		pre->LPPtr = XorP(NULL, q);
		A.Left = pre;
		return OK;
	}

	while (count<i && p != NULL)
	{
		q = XorP(pre, p->LPPtr);
		pre = p;
		p = q;
		count++;
	}

	if (p == NULL)
	{
		printf("�޴˽ڵ��ɾ��\n");
		return ERROR;
	}
	else {
		if (XorP(p->LPPtr, pre) == NULL)
		{
			q = XorP(pre->LPPtr, p);
			pre->LPPtr = XorP(q, NULL);
			free(p);
			A.Right = pre;
			return OK;
		}
		else {
			XorNode *temp1, *temp2;
			q = XorP(p->LPPtr, pre);
			temp1 = XorP(pre->LPPtr, p);
			temp2 = XorP(q->LPPtr, p);
			free(p);
			pre->LPPtr = XorP(temp1, q);
			q->LPPtr = XorP(temp2, pre);
			return OK;
		}
	}
}
