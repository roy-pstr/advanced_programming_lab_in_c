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

void List_addItem(Int **head, int value, int index);

int List_findIndex(Int *head, int value);

int List_deleteItem(Int **head, int index);

void List_destroyList(Int *head);

void List_printList(Int *head);

#endif