#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define INDEX_NOT_EXISTS -1

typedef struct node_st
{
	int value;
	struct node_st *next;
}Node;

void List_addItemByIndex(Node **head, int value, int index);

void List_addEnd(Node **head, int value);

int List_findIndex(Node *head, int value);

int List_deleteItem(Node **head, int index);

void List_destroyList(Node *head);

void List_printList(Node *head);

#endif