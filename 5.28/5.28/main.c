#include <stdio.h>
#include <stdlib.h>
typedef enum { ATOM, LINK }DataType;
typedef struct GLNode {
	DataType tag;
	int exp;
	union {
		int coef;
		struct GLNode* hp;
	};
	struct GLNode* tp;
}GList;
GList* init(int m) {
	GList* gl = (GList*)malloc(sizeof(GList));
	GList* gt = (GList*)malloc(sizeof(GList));
	gt->tag = LINK;
	gt->exp = 'a' + m-1;
	gl->exp = m;
	gl->tag = LINK;
	gl->tp = NULL;
	gl->hp = gt;
	return gl;
}
char* subString(char* s, int i, int j) {
	int len = strlen(s);
	if (i < j&&i >= 0 && j < len) {
		char* t = (char*)malloc(sizeof(char)*(j - i));
		int k = 0;
		for (k = 0; k < j - i; k++)
			t[k] = s[k + i];
		t[k] = '\0';
		return t;
	}
	else
		return NULL;
}
int serve(char* s) {
	int k = 1, i = 1,len=strlen(s);
	for (i = 2; i < len; i++) {
		if (s[i] == '(')
			k++;
		else if (s[i] == ')')
			k--;
		if (k == 0)
			break;
	}
	return i;
}
char* getHead(char* s,int i) {
	return subString(s, 1, i + 1);
}
char* getTail(char* s, int i) {
	int len = strlen(s);
	char* t = subString(s, i + 2, len-1);
	if (t != NULL) {//取尾时要补一对括号
		int lent = strlen(t);
		char* temp = (char*)malloc(sizeof(char)*(lent + 2));
		temp[0] = '(';
		temp[1] = '\0';
		strcat(temp, t);
		temp[lent+1] = ')';
		temp[lent + 2] = '\0';
		return temp;
	}
	else
		return NULL;
}
char* dealListHead(char* s) {
	int len = strlen(s);
	char* sub = subString(s, 1, len - 3);
	char* t = (char*)malloc(sizeof(char)*(strlen(sub)+2));
	t[0] = '(';
	t[1] = '\0';
	strcat(t, sub);
	strcat(t, ")");
	return t;
}
void creatGList(GList* gl, char* s,int m) {
	int spilt = serve(s);
	char* head = getHead(s,spilt);
	char* tail = getTail(s,spilt);
	//先考虑表头的处理
	int lenH = strlen(head);
	if (lenH == 5) {//当前表项为原子项
		GList* p = (GList*)malloc(sizeof(GList));
		p->exp = head[3] - '0';
		p->coef = head[1] - '0';
		p->tag = ATOM;
		gl->tp = p;
		if (tail != NULL) {
			creatGList(p, tail,m);
		}
	   else {
			p->tp = NULL;
		}
	}
	else {//为列表项
		GList* p = (GList*)malloc(sizeof(GList));
		GList* pt = (GList*)malloc(sizeof(GList));
		gl->tp = p;
		p->tag = LINK;
		p->exp =head[strlen(head)-2]-'0';
		if (tail != NULL)
			creatGList(p, tail, m);
		else
			p->tp = NULL;
			pt->tag = LINK;
			pt->exp = 'a'+m - 1;
			p->hp = pt;
			creatGList(pt, dealListHead(head), m - 1);
	}
}
void getDerived(GList* gl) {
	GList* p = gl->hp;
	while (p) {
		GList* ptemp = p;
		while (ptemp->exp != 'a'&&ptemp == LINK&&ptemp&&ptemp->hp)
			ptemp = ptemp->hp;
		if (ptemp->exp == 'a') {//当前求偏导的目标变量
			ptemp = ptemp->tp;
			while (ptemp) {
				ptemp->coef *= ptemp->exp;
				ptemp->exp--;
				ptemp = ptemp->tp;
			}
		}
		p = p->tp;
	}
}
void printGList(GList* gl) {
	char val = 0;
	while (gl) {
	if ((gl->exp<'a'||gl->exp>'z')&&gl->tag == LINK) {//表头
			gl = gl->hp;
		}
		else {
			if (gl->tag == LINK&&gl->exp >= 'a'&&gl->exp <= 'z') {//每项开头
				val = gl->exp;
				gl = gl->tp;
				if (gl->tag == LINK) {
					printGList(gl->hp);
				}
				else {
					printf("%d", gl->coef);
				}
				printf("%c^%d", val, gl->exp);
				gl = gl->tp;
			}
			else {
				printf("%d", gl->coef);
				printf("%c^%d",val, gl->exp);
				gl = gl->tp;
			}
			if(gl!=NULL)
				printf("+");
		}
	}
}
int main() { 
	GList* gl = init(1);
	creatGList(gl->hp, "((5,3),(5,6),(7,8))",0);
	getDerived(gl);
	printGList(gl);
}