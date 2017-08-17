#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum{ATOM,LINK}DataType;
typedef struct GLNode {
	DataType tag;
	union {
		char data;
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
	char* tail = subString(s, i + 2, strlen(s) - 1);
	if (tail != NULL) {
		int len = strlen(tail);
		char* temp = (char*)malloc(sizeof(char)*(len + 2));
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
	char* head = getHead(s, spilt);
	char* tail = getTail(s, spilt);
	if (strlen(head) == 1) {//原子类型
		GList* node = (GList*)malloc(sizeof(GList));
		node->data = head[0];
		node->tag = ATOM;
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
		node->hp->tag = LINK;
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
int isEqual(GList* gl1, GList* gl2) {
	gl1 = gl1->hp;
	gl2 = gl2->hp;
	int equal = 1;
	while (gl1&&gl2) {
		gl1 = gl1->tp;
		gl2 = gl2->tp;
		if (equal == 0)
			break;
		else {
			if (gl1&&gl1->tag == LINK) {
				if (gl2&&gl2->tag == LINK)
					equal = isEqual(gl1, gl2);
				else
					equal = 0;
			}
			else if (gl1) {
				if (gl2) {
					equal = 1;
				}
				else
					equal = 0;
			}
		}
	}
	return equal;
}
int main() {
	GList* gl1 = init();
	GList* gl2 = init();
	creatGList(gl1->hp, "((3),4)");
	creatGList(gl2->hp, "(3,4)");
	printf("%d", isEqual(gl1, gl2));
	printf("\n");
}