#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
typedef enum{ATOM,LINK}DataType;
typedef struct GLNode {
	DataType tag;
	union {
		int data;
		struct GLNode* hp;
	};
	struct GLNode* tp;
}GList;
GList* init() {
	GList* gl = (GList*)malloc(sizeof(GList));
	gl->tag = LINK;
	gl->hp = (GList*)malloc(sizeof(GList));
	gl->hp->tag = LINK;
	return gl;
}
char* subString(char* s, int i, int j) {
	int len = strlen(s);
	if (i < j&&i >= 0 && j < len) {
		char* temp = (char*)malloc(sizeof(char)*(j - i));
		int k = 0;
		for (k = 0; k < j - i; k++) {
			temp[k] = s[k + i];
		}
		temp[k] = '\0';
		return temp;
	}
	else
		return NULL;
}
int serve(char* s) {
	int k = 0, i = 1, len = strlen(s);
	for (i = 1; i < len; i++) {
		if (s[i] == '(')
			k++;
		else if (s[i] == ')')
			k--;
		if (k == 0)
			break;
	}
	return i;
}
char* getHead(char* s, int i) {
	return subString(s, 1, i + 1);
}
char* getTail(char* s, int i) {
	char* ptail = subString(s, i + 2, strlen(s) - 1);
	if (ptail != NULL) {
		int len = strlen(ptail);
		char* temp = (char*)malloc(sizeof(char)*(len + 2));
		temp[0] = '(';
		temp[1] = '\0';
		strcat(temp, ptail);
		strcat(temp, ")");
		return temp;
	}
	else
		return NULL;
}
void creatGList(GList* gl, char* s) {
	int spilt = serve(s);
	char* head = getHead(s,spilt);
	char* tail = getTail(s, spilt);
	if (strlen(head) == 1) {//为原子项
		GList* node = (GList*)malloc(sizeof(GList));
		node->tag = ATOM;
		node->data = head[0];
		gl->tp = node;
		if (tail != NULL) {//还有后续列表
			creatGList(node, tail);
		}
		else
			node->tp = NULL;
	}
	else {//为列表项
		GList* node = (GList*)malloc(sizeof(GList));
		node->tag = LINK;
		gl->tp = node;
		node->hp = (GList*)malloc(sizeof(GList));
		node->hp->tag = LINK;
		creatGList(node->hp, head);
		if (tail != NULL) {//有后续元素存在
			creatGList(node, tail);
		}
		else
			node->tp = NULL;
	}
}
void printGList(GList* gl) {//最后输出层次颠倒
	gl = gl->hp;
	while (gl) {
		gl = gl->tp;
		if (gl&&gl->tag == ATOM) {
			printf("%c", gl->data);
		}
		else if(gl){
			printGList(gl);
			printf("\n");
		}
	}
}
int getDepth(GList* gl) {
	gl = gl->hp;
	int max = 0;
	while (gl) {
		gl = gl->tp;
		if (gl&&gl->tag == LINK) {
			int temp = getDepth(gl)+1;
			if (max < temp)
				max = temp;
		}
		else if (gl) {
			if (max < 1)
				max = 1;
		}
	}
	return max;
}
int main() {
	GList* gl = init();
	creatGList(gl->hp, "(((3)),4,5)");
	printGList(gl);
	printf("\n");
	printf("%d\n", getDepth(gl));
}

