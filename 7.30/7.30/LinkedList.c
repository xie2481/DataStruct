#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
LinkedList* init() {
	LinkedList* p = (LinkedList*)malloc(sizeof(LinkedList));
	p->head = NULL;
	p->elemcount = 0;
	return p;
}
void insert(LinkedList* L, char* s) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->s = (char*)malloc(sizeof(char)*strlen(s));
	strcpy(p->s, s);
	p->next = L->head;
	L->head = p;
}
void printList(LinkedList* L) {
	Node* p = L->head;
	while (p) {
		printf("%s\n", p->s);
		p = p->next;
	}
}