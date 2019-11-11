#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "linked_list.h"
#include "input_handler.h"

int main()
{
	Int *head = NULL;

	bool exit_program = false;
	while (!exit_program)
	{
		Command user_command;
		readNextCommand(&user_command);
		exit_program = executeOneCommand(&user_command, &head);
	}

	List_destroyList(head);
	return SUCCESS_CODE;
}