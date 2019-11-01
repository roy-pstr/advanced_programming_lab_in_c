#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "input_handler.h"
#include "linked_list.h"

#define EXIT_WHILE_LOOP break

int main()
{
	Int *head = NULL;
	bool exit_program = false;

	while (true)
	{
		
		Command user_command;

		readUserCommandFromInput(&user_command);

		exit_program = executeUserCommand(&user_command, &head);

		if (exit_program) {
			destroyList(head);
			EXIT_WHILE_LOOP;
		}
	}

	return SUCCESS_CODE;
}
