#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "linked_list.h"

#define MAX_COMMAND_LEN 100

typedef struct command
{
	char command_name[MAX_COMMAND_LEN];
	int arg1;
	int arg2;
}Command;

Command waitUntilUserInputCommand();

bool executeUserCommand(Command *user_command, Int **head);

#endif