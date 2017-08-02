#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char* ch;//若是非空串，则按串长分配存储区，否则ch为NULL
	int length;//串的长度
}HString;
HString* init() {
	HString* h = (HString*)malloc(sizeof(HString));
	h->ch = NULL;
	h->length = 0;
	return h;
}
void StrAssign(HString* h, char* ch) {
	h->length = strlen(ch);
	h->ch = (char*)malloc(sizeof(char)*h->length);
	strcpy(h->ch, ch);
}
HString* Concat(HString* s1, HString* s2) {
	HString* T = (HString*)malloc(sizeof(HString));
	T->length = s1->length + s2->length;
	T->ch = (char*)malloc(sizeof(char)*T->length);
	strcpy(T->ch, s1->ch);
	strcat(T->ch, s2->ch);
	return T;
}
void Replace(HString* S, HString* T, HString* V) {
	int i = 0, j = 0, flag = 0;
	for (i = 0; i < S->length-T->length+1; i++) {
		flag = 1;
		for (j = 0; j < T->length; j++) {
			if (S->ch[i + j] != T->ch[j])
				flag = 0;
		}
		if (flag) {//符合替换条件
			if (V->length > T->length) {//S的当前空间不足
				S->ch = (char*)realloc(S->ch, sizeof(char)*(S->length-T->length+V->length));
				for (j = S->length-1; j >= i + T->length;j--) {//将T串后面的部分向后移动V->length-T->length个单位
					S->ch[j + V->length - T->length] = S->ch[j];
				}
			}
			if (V->length < T->length) {
				for (j = i + T->length; j <S->length; j++) {//将T串后面的部分向前移动V->length-T->length个单位
					S->ch[j + V->length - T->length] = S->ch[j];
				}
			}
			S->length += V->length - T->length;
			//进行串的替换
			for (j = 0; j <V->length; j++) {
				S->ch[j+i] = V->ch[j];
			}
			i = i + V->length - 1;//i指针指向正确的当前位置
		}
	}
	S->ch[S->length] = '\0';
}
void StrInsert(HString* S, int pos, HString* T) {//默认S，T不为空串
	int i = 0;
	if (pos<1 || pos>S->length)
		return;
	S->ch = (char*)realloc(S->ch, sizeof(char)*(S->length+T->length));
	for (i = S->length-1; i >= pos; i--) {
		S->ch[i + T->length] = S->ch[i];
	}
	for (i = 0; i < T->length; i++) {
		S->ch[i + pos] = T->ch[i];
	}
	S->length += T->length;
	S->ch[S->length] = '\0';
}
int main() {
	HString* s = init(), *t = init(), *h = init();
	printf("--------------开始测试Concat------------\n");
	StrAssign(s, "hello");
	StrAssign(t, "he");
	printf("当前串为hello和head,下面进行连接操作:");
	h = Concat(s, t);
	printf("%s\n", h->ch);
	printf("-------------开始测试Replace------------\n");
	//长度相等的情况为了方便就不测试了
	printf("首先测试替换串长度小于待替换串，替换串为i,待替换串为he,母串为hello:\n");
	StrAssign(s, "hello");
	StrAssign(t, "he");
	StrAssign(h, "i");
	Replace(s, t, h);
	printf("串为%s 长度为%d\n", s->ch, s->length);
	printf("现在测试替换串长度大于待替换串，替换串为ia,待替换串为h,母串为hello:\n");
	StrAssign(s, "hello");
	StrAssign(t, "h");
	StrAssign(h, "ia");
	Replace(s, t, h);
	printf("串为%s 长度为%d\n", s->ch, s->length);
	printf("现在测试替换串长度大于待替换串,且存在多个带替换串，替换串为ia,待替换串为h,母串为hello:\n");
	StrAssign(s, "hehlh");
	StrAssign(t, "h");
	StrAssign(h, "ia");
	Replace(s, t, h);
	printf("串为%s 长度为%d\n", s->ch, s->length);
	printf("现在测试替换串长度小于待替换串,且存在多个带替换串，替换串为i,待替换串为he,母串为hello:\n");
	StrAssign(s, "hehelhe");
	StrAssign(t, "he");
	StrAssign(h, "i");
	Replace(s, t, h);
	printf("串为%s 长度为%d\n", s->ch, s->length);
	printf("--------------------开始测试StrInsert-------------------\n");
	StrAssign(s, "hello");
	StrAssign(t, "fv");
	printf("先测试在1位置插入,母串为hello,子串为fv:");
	StrInsert(s, 1, t);
	printf("%s\n", s->ch);
	printf("现在测试在中间位置插入,位置为3:");
	StrAssign(s, "hello");
	StrAssign(t, "fv");
	StrInsert(s, 3, t);
	printf("%s\n", s->ch);
	printf("现在测试在末尾位置插入,位置为5:");
	StrAssign(s, "hello");
	StrAssign(t, "fv");
	StrInsert(s, 5, t);
	printf("%s\n", s->ch);
	return 0;
}