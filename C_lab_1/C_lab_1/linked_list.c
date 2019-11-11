#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "linked_list.h"

Int *findLastElement(Int **head)
{
	Int *last_element = *head;

	while (last_element->next != NULL)
		last_element = last_element->next;

	return last_element;
}

void addStart(Int **head, Int *new_element)
{
	Int *first_element = *head;
	*head = new_element;
	new_element->next = first_element;
}

void List_addEnd(Int **head, int value)
{
	Int *new_element = (Int*)malloc(sizeof(Int));
	new_element->value = value;

	if (NULL == *head)
	{
		addStart(head, new_element);
		return;
	}

	Int *last_element = findLastElement(head);
	last_element->next = new_element;
	new_element->next = NULL;
}

void addMiddle(Int *head, Int *new_element, int index)
{
	Int *prev_element = head;
	for (int i = 0; i < index-1; i++)
		prev_element = prev_element->next;

	Int *next_element = prev_element->next;
	prev_element->next = new_element;
	new_element->next = next_element;
}

void List_addItemByIndex(Int **head, int value, int index)
{
	Int *new_element = (Int*)malloc(sizeof(Int));
	new_element->value = value;

	if (index == 0)
		addStart(head, new_element);

	else
		addMiddle(*head, new_element, index);
}

void deleteFirst(Int **head)
{
	Int *first_element = *head;
	*head = first_element->next;
	free(first_element);
}

int List_deleteItem(Int **head, int index)
{
	if (index == 0)
	{
		if (NULL == *head)
			return ERROR_CODE;

		deleteFirst(head);
		return SUCCESS_CODE;
	}

	Int *prev_element = *head;
	for (int i = 0; i < index - 1; i++)
	{
		if (NULL == prev_element)
			return ERROR_CODE;
		prev_element = prev_element->next;
	}

	Int *item_to_delete = prev_element->next;
	if (NULL == item_to_delete)
		return ERROR_CODE;

	Int *next_element = item_to_delete->next;
	free(item_to_delete);

	prev_element->next = next_element;
	return SUCCESS_CODE;
}

int List_findIndex(Int *head, int value)
{
	int index = 0;
	Int *iterator = head;

	while (iterator != NULL)
	{
		if (iterator->value == value)
			return index;

		iterator = iterator->next;
		index++;
	}
	
	return INDEX_NOT_EXISTS;
}

void List_destroyList(Int *head)
{
	Int *current = head;
	Int *next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void List_printList(Int *head)
{
	printf("[");
	Int *current = head;
	while (current != NULL)
	{
		printf("%d", current->value);
		if (current->next != NULL)
			printf(", ");
		current = current->next;
	}
	printf("]\n");
}