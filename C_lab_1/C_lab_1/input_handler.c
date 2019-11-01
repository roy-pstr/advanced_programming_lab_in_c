#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linked_list.h"
#include "input_handler.h"

#define STRINGS_ARE_EQUAL( Str1, Str2 ) ( strcmp( (Str1), (Str2) ) == 0 )

int charToInt(char input)
{
	return input - '0';
}

void printCommand(Command *cmd) //debugging
{
	printf("---printing command---\n");
	printf("name: %s\n", cmd->command_name);
	printf("arg1: %d\n", cmd->arg1);
	printf("arg2: %d\n", cmd->arg2);
}

bool endOfString(char *str, int i)
{
	return str[i] == '\0';
}

void upperCase(char *str)
{
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= ' ';
		str++;
	}
}

void getCommand(char *input_string, Command *user_command)
{
	int i = 0;
	while(input_string[i] != ' ' && !endOfString(input_string, i))
	{
		user_command->command_name[i] = input_string[i];
		i++;
	}
	user_command->command_name[i] = '\0';
	upperCase(user_command->command_name);
		
	if (endOfString(input_string, i))
		return;

	i++;
	user_command->arg1 = charToInt(input_string[i]);
	
	i++;
	if (endOfString(input_string, i))
		return;

	i++;
	user_command->arg2 = charToInt(input_string[i]);
}

void readUserCommandFromInput( Command *user_command) {
	char input_string[MAX_COMMAND_LEN];
	gets(input_string);
	getCommand(input_string, user_command);
}

void executeAddEnd(Command *user_command, Int **head)
{
	addItem(head, user_command->arg1, LAST_INDEX);
}

void executeAddStart(Command *user_command, Int **head)
{
	addItem(head, user_command->arg1, 0);
}

bool executeAddAfter(Command *user_command, Int **head)
{
	bool exit_program = false;
	int previous_item_index = findIndex(*head, user_command->arg2);
	if (previous_item_index == NONE_INDEX)
	{
		printf("Sorry, can't find %d in the list. Exiting...\n", user_command->arg2);
		exit_program = true;
	}
	else
		addItem(head, user_command->arg1, previous_item_index+1);

	return exit_program;
}

void executeIndex(Command *user_command, Int **head)
{
	int index = findIndex(*head, user_command->arg1);
	if (index == NONE_INDEX)
		printf("-1\n");
	else
		printf("%d\n", index);
}

bool executeDel(Command *user_command, Int **head)
{
	bool exit_program = false;
	int retval = deleteItem(head, user_command->arg1);
	if (retval == ERROR_CODE)
	{
		printf("Index is too large. Exiting...\n");
		exit_program = true;
	}

	return exit_program;
}

void executePrint(Int **head)
{
	printList(*head);
}

bool executeUserCommand(Command *user_command, Int **head)
{
	bool exit_program = false;
	if (STRINGS_ARE_EQUAL(user_command->command_name, "ADD_END"))
		executeAddEnd(user_command, head);

	else if (STRINGS_ARE_EQUAL(user_command->command_name, "ADD_START"))
		executeAddStart(user_command, head);

	else if (STRINGS_ARE_EQUAL(user_command->command_name, "ADD_AFTER"))
		exit_program = executeAddAfter(user_command, head);

	else if (STRINGS_ARE_EQUAL(user_command->command_name, "INDEX"))
		executeIndex(user_command, head);

	else if (STRINGS_ARE_EQUAL(user_command->command_name, "DEL"))
		exit_program = executeDel(user_command, head);

	else if (STRINGS_ARE_EQUAL(user_command->command_name, "PRINT"))
		executePrint(head);

	else if (STRINGS_ARE_EQUAL(user_command->command_name, "EXIT"))
		exit_program = true;

	else
		printf("FUCK!! Default! shouldn't be here!!!\nTry again...\n"); //debugging

	return exit_program;
}
