#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdbool.h>
#include "utils.h"
#include "linked_list.h"

#define MAX_COMMAND_LEN 100

typedef struct command_st
{
	char command_name[MAX_COMMAND_LEN];
	int arg1;
	int arg2;
}Command;

void readNextCommand(Command *user_command);

bool executeOneCommand(Command *user_command, Node **head);

#endif