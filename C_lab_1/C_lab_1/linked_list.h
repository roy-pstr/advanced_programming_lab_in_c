#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define INDEX_NOT_EXISTS -1

typedef struct integer
{
	int value;
	struct integer *next;
}Int;

void List_addItemByIndex(Int **head, int value, int index);

void List_addEnd(Int **head, int value);

int List_findIndex(Int *head, int value);

int List_deleteItem(Int **head, int index);

void List_destroyList(Int *head);

void List_printList(Int *head);

#endif