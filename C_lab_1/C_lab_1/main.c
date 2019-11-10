#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "input_handler.h"
#include "linked_list.h"

int main()
{
	Int *head = NULL;

	bool exit_program = false;
	while (!exit_program)
	{
		char input_string[MAX_COMMAND_LEN];
		Command user_command;

		gets(input_string);
		getCommand(input_string, &user_command);

		exit_program = executeOneCommand(&user_command, &head);
	}

	List_destroyList(head);
	return 0;
}