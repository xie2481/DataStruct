#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char* ch;//���Ƿǿմ����򰴴�������洢��������chΪNULL
	int length;//���ĳ���
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
		if (flag) {//�����滻����
			if (V->length > T->length) {//S�ĵ�ǰ�ռ䲻��
				S->ch = (char*)realloc(S->ch, sizeof(char)*(S->length-T->length+V->length));
				for (j = S->length-1; j >= i + T->length;j--) {//��T������Ĳ�������ƶ�V->length-T->length����λ
					S->ch[j + V->length - T->length] = S->ch[j];
				}
			}
			if (V->length < T->length) {
				for (j = i + T->length; j <S->length; j++) {//��T������Ĳ�����ǰ�ƶ�V->length-T->length����λ
					S->ch[j + V->length - T->length] = S->ch[j];
				}
			}
			S->length += V->length - T->length;
			//���д����滻
			for (j = 0; j <V->length; j++) {
				S->ch[j+i] = V->ch[j];
			}
			i = i + V->length - 1;//iָ��ָ����ȷ�ĵ�ǰλ��
		}
	}
	S->ch[S->length] = '\0';
}
void StrInsert(HString* S, int pos, HString* T) {//Ĭ��S��T��Ϊ�մ�
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
	printf("--------------��ʼ����Concat------------\n");
	StrAssign(s, "hello");
	StrAssign(t, "he");
	printf("��ǰ��Ϊhello��head,����������Ӳ���:");
	h = Concat(s, t);
	printf("%s\n", h->ch);
	printf("-------------��ʼ����Replace------------\n");
	//������ȵ����Ϊ�˷���Ͳ�������
	printf("���Ȳ����滻������С�ڴ��滻�����滻��Ϊi,���滻��Ϊhe,ĸ��Ϊhello:\n");
	StrAssign(s, "hello");
	StrAssign(t, "he");
	StrAssign(h, "i");
	Replace(s, t, h);
	printf("��Ϊ%s ����Ϊ%d\n", s->ch, s->length);
	printf("���ڲ����滻�����ȴ��ڴ��滻�����滻��Ϊia,���滻��Ϊh,ĸ��Ϊhello:\n");
	StrAssign(s, "hello");
	StrAssign(t, "h");
	StrAssign(h, "ia");
	Replace(s, t, h);
	printf("��Ϊ%s ����Ϊ%d\n", s->ch, s->length);
	printf("���ڲ����滻�����ȴ��ڴ��滻��,�Ҵ��ڶ�����滻�����滻��Ϊia,���滻��Ϊh,ĸ��Ϊhello:\n");
	StrAssign(s, "hehlh");
	StrAssign(t, "h");
	StrAssign(h, "ia");
	Replace(s, t, h);
	printf("��Ϊ%s ����Ϊ%d\n", s->ch, s->length);
	printf("���ڲ����滻������С�ڴ��滻��,�Ҵ��ڶ�����滻�����滻��Ϊi,���滻��Ϊhe,ĸ��Ϊhello:\n");
	StrAssign(s, "hehelhe");
	StrAssign(t, "he");
	StrAssign(h, "i");
	Replace(s, t, h);
	printf("��Ϊ%s ����Ϊ%d\n", s->ch, s->length);
	printf("--------------------��ʼ����StrInsert-------------------\n");
	StrAssign(s, "hello");
	StrAssign(t, "fv");
	printf("�Ȳ�����1λ�ò���,ĸ��Ϊhello,�Ӵ�Ϊfv:");
	StrInsert(s, 1, t);
	printf("%s\n", s->ch);
	printf("���ڲ������м�λ�ò���,λ��Ϊ3:");
	StrAssign(s, "hello");
	StrAssign(t, "fv");
	StrInsert(s, 3, t);
	printf("%s\n", s->ch);
	printf("���ڲ�����ĩβλ�ò���,λ��Ϊ5:");
	StrAssign(s, "hello");
	StrAssign(t, "fv");
	StrInsert(s, 5, t);
	printf("%s\n", s->ch);
	return 0;
}