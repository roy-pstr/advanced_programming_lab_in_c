#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "input_handler.h"
#include "linked_list.h"

#define READ_NEXT_COMMAND 

int main()
{
	Int *head = NULL;
	bool exit_program = false;

	while (!exit_program)
	{
		Command user_command = readNextCommand();
		exit_program = executeUserCommand(&user_command, &head);
	}
	destroyList(head);
	return SUCCESS_CODE;
}
