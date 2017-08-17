#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	gl->tp = NULL;
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
			temp[k] = s[k + i];
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
	char* tail = getTail(s,spilt);
	if (strlen(head) == 1) {//为原子项
		GList* node = (GList*)malloc(sizeof(GList));
		node->tag = ATOM;
		node->data = head[0];
		gl->tp = node;
		if (tail != NULL)
			creatGList(node, tail);
		else
			node->tp = NULL;
	}
	else {
		GList* node = (GList*)malloc(sizeof(GList));
		node->tag = LINK;
		node->hp = (GList*)malloc(sizeof(GList));
		gl->tp = node;
		creatGList(node->hp, head);
		if (tail != NULL)
			creatGList(node, tail);
		else
			node->tp = NULL;
	}
}
void printGList(GList* gl) {
	gl = gl->hp;
	while (gl) {
		gl = gl->tp;
		if (gl&&gl->tag == LINK) {
			printGList(gl);
			printf("\n");
		}
		else if (gl) {
			printf("%c", gl->data);
		}
	}
}
void copy(GList* target,GList* gl) {//gl为待复制的表
	target = target->hp;
	gl = gl->hp;
	while (target) {
		target = target->tp;
		if (target&&target->tag == LINK) {
			GList* node = (GList*)malloc(sizeof(GList));
			node->tag = LINK;
			node->hp = (GList*)malloc(sizeof(GList));
			node->hp->tag = LINK;
			gl->tp = node;
			copy(target, node);
		}
		else if (target) {
			GList* node = (GList*)malloc(sizeof(GList));
			node->tag = ATOM;
			node->data = target->data;
			gl->tp = node;
		}
		else if (target == NULL)
			gl->tp = NULL;
		gl = gl->tp;
	}
}
int main() {
	GList* gl = init();
	GList* gl1 = init();
	creatGList(gl->hp, "((3),4)");
	printGList(gl);
	printf("\n");
	copy(gl, gl1);
	printGList(gl1);
	printf("\n");
}