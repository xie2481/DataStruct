#include <stdlib.h>
#include <stdio.h>
#define LEFT 0
#define RIGHT 1
#define ERROR 0
#define OK 1
#define Status int 

// 定义节点
typedef struct XorNode
{
	// 数据域
	char data;
	// 指针域
	struct XorNode *LPPtr;
} XorNode, *XorPointer;


// 无头节点的异或指针双向链表
typedef struct {
	// 分别指向链表的左端和右端
	XorPointer Left, Right;
} XorLinkedList;

XorPointer XorP(XorPointer p, XorPointer q);

// 打印异或链表
void PrintXorList(XorLinkedList A, int direction);

// 插入
Status InstertXorList(XorLinkedList &A, int i, XorNode *a);

// 删除
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

	printf("删除第一个节点\n");
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
A 遍历输出的异或链表
direction 遍历的方向，LEFT左到右，RIGHT从右到左
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
/* 向链表的第i个节点之前插入一个节点，从1开始，左边算起！                                                                     */
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
		q = XorP(pre, p->LPPtr);// 找到下一个节点，以便修改
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

	// 最后一个位置插入特殊处理
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
/* 删除链表中第i个节点，从1开始左边开始                                                                     */
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
		printf("链表为空！！！");
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
		printf("无此节点可删除\n");
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
