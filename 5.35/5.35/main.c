#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum{ATOM,LINK}DataType;
typedef struct GLNode {
	DataType tag;
	union {
		int data;
		struct {
			struct GLNode* hp;
			struct GLNode* tp;
		}ptr;
	};
}GList;
GList* init() {
	GList* gl = (GList*)malloc(sizeof(GList));
	gl->tag = LINK;
	gl->ptr.hp = NULL;
	return gl;
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
char* subString(char* s, int i, int j) {
	int len = strlen(s);
	if (i < j&&i >= 0 && j < len) {
		char* temp = (char*)malloc(sizeof(char)*(j - i));
		int k = 0;
		for (k = 0; k < j - i; k++)
			temp[k] = s[i + k];
		temp[k] = '\0';
		return temp;
	}
	else
		return NULL;
}
char* getHead(char* s, int i) {
	return subString(s, 1, i + 1);
}
char* getTail(char* s, int i) {
	char* tail = subString(s, i + 2, strlen(s) - 1);
	if (tail) {
		char* temp = (char*)malloc(sizeof(char)*(strlen(tail) + 2));
		temp[0] = '(';
		temp[1] = '\0';
		strcat(temp, tail);
		strcat(temp, ")");
		return temp;
	}
	else
		return NULL;
}
void creatGList(GList* gl, char* s) {
	int spilt = serve(s);
	char* head = getHead(s,spilt);
	char* tail = getTail(s,spilt);
	if (strlen(head) == 1) {//为原子项
		GList* node = (GList*)malloc(sizeof(GList));
		node->tag = ATOM;
		node->data = head[0];
		node->ptr.tp = NULL;
		gl->ptr.hp = node;
		if (tail != NULL) {
			gl->ptr.tp = (GList*)malloc(sizeof(GList));
			gl->ptr.tp->tag = LINK;
			creatGList(gl->ptr.tp, tail);
		}
		else
			gl->ptr.tp = NULL;
	}
	else {
		GList* node = (GList*)malloc(sizeof(GList));
		node->tag = LINK;
		gl->ptr.tp = node;
		creatGList(node, head);
		if (tail) {
			node->ptr.tp = (GList*)malloc(sizeof(GList));
			node->ptr.tp->tag = LINK;
			creatGList(node->ptr.tp, tail);
		}
		else
			node->ptr.tp = NULL;
	}

}
void printGList(GList* gl) {
	while (gl) {
		if (gl->tag == ATOM)
			printf("%c", gl->data);
		else {
			printGList(gl->ptr.hp);
			printf("\n");
		}
		gl = gl->ptr.tp;
	}
}
int main() {
	GList* gl = init();
	creatGList(gl, "((3),4)");
	printGList(gl);
	return 0;
}