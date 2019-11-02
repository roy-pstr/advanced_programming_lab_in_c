#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "input_handler.h"
#include "linked_list.h"

#define EXIT_PROGRAM true

int main()
{
	Int *head = NULL;
	bool read_commands_from_user = true;

	while (read_commands_from_user)
	{
		
		Command user_command = waitUntilUserInputCommand();

		bool return_status = executeUserCommand(&user_command, &head);

		if (return_status == EXIT_PROGRAM) {
			destroyList(head);
			read_commands_from_user = false;
		}
	}

	return SUCCESS_CODE;
}
