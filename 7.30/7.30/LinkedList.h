#pragma once
typedef struct Node {
	char* s;
	struct Node* next;
}Node;
typedef struct LinkedList {
	Node* head;
	int elemcount;
}LinkedList;
LinkedList* init();
void insert(LinkedList* L, char* s);
void printList(LinkedList* L);