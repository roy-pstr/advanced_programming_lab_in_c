#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "user_command.h"

Node *findLastElement(Node *head)
{
	Node *last_element = head;

	while (last_element->next != NULL)
		last_element = last_element->next;

	return last_element;
}

void addStart(Node **head, Node *new_element)
{
	Node *first_element = *head;
	*head = new_element;
	new_element->next = first_element;
}

void List_addEnd(Node **head, int value)
{
	Node *new_element = (Node*)malloc(sizeof(Node));
	new_element->value = value;

	if (NULL == *head)
	{
		addStart(head, new_element);
		return;
	}

	Node *last_element = findLastElement(*head);
	last_element->next = new_element;
	new_element->next = NULL;
}

void addMiddle(Node *head, Node *new_element, int index)
{
	Node *prev_element = head;
	for (int i = 0; i < index-1; i++)
		prev_element = prev_element->next;

	Node *next_element = prev_element->next;
	prev_element->next = new_element;
	new_element->next = next_element;
}

void List_addItemByIndex(Node **head, int value, int index)
{
	Node *new_element = (Node*)malloc(sizeof(Node));
	new_element->value = value;

	if (index == 0)
		addStart(head, new_element);

	else
		addMiddle(*head, new_element, index);
}

void deleteFirst(Node **head)
{
	Node *first_element = *head;
	*head = first_element->next;
	free(first_element);
}

int List_deleteItem(Node **head, int index)
{
	if (index == 0)
	{
		if (NULL == *head)
			return ERROR_CODE;

		deleteFirst(head);
		return SUCCESS_CODE;
	}

	Node *prev_element = *head;
	for (int i = 0; i < index - 1; i++)
	{
		if (NULL == prev_element)
			return ERROR_CODE;
		prev_element = prev_element->next;
	}

	Node *item_to_delete = prev_element->next;
	if (NULL == item_to_delete)
		return ERROR_CODE;

	Node *next_element = item_to_delete->next;
	free(item_to_delete);

	prev_element->next = next_element;
	return SUCCESS_CODE;
}

int List_findIndex(Node *head, int value)
{
	int index = 0;
	Node *iterator = head;

	while (iterator != NULL)
	{
		if (iterator->value == value)
			return index;

		iterator = iterator->next;
		index++;
	}
	
	return INDEX_NOT_EXISTS;
}

void List_destroyList(Node *head)
{
	Node *current = head;
	Node *next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void List_printList(Node *head)
{
	printf("[");
	Node *current = head;
	while (current != NULL)
	{
		printf("%d", current->value);
		if (current->next != NULL)
			printf(", ");
		current = current->next;
	}
	printf("]\n");
}