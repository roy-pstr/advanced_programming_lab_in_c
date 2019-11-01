#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define SUCCESS_CODE 0
#define ERROR_CODE  -1
#define LAST_INDEX  -1
#define NONE_INDEX  -2

typedef struct integer
{
	int value;
	struct integer *next;
}Int;

void addItem(Int **head, int value, int index);

int findIndex(Int *head, int value);

int deleteItem(Int **head, int index);

void destroyList(Int *head);

void printList(Int *head);

#endif