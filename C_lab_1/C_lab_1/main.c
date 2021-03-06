#include <stdio.h>
#include <stdbool.h>

#include "linked_list.h"
#include "user_command.h"

int main()
{
	Node *head = NULL;

	bool exit_program = false;
	while (!exit_program)
	{
		Command user_command;
		readNextCommand(&user_command);
		exit_program = executeOneCommand(&user_command, &head);
	}

	List_destroyList(head);
	return 0;
}