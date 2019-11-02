#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linked_list.h"
#include "input_handler.h"

#define STRINGS_ARE_EQUAL( Str1, Str2 ) ( strcmp( (Str1), (Str2) ) == 0 )

void printCommand(Command *cmd) //debugging
{
	printf("---printing command---\n");
	printf("name: %s\n", cmd->command_name);
	printf("arg1: %d\n", cmd->arg1);
	printf("arg2: %d\n", cmd->arg2);
}

bool isDigit(char c)
{
	return (c >= '0' && c <= '9');
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

int charToInt(char input)
{
	return input - '0';
}

int strToInt(char *input)
{
	int output = 0, i = 0;
	for (int i = 0; isDigit(input[i]); i++)
		output = output * 10 + charToInt(input[i]);

	return output;
}

Command transformUserInputToCommandStruct(char *input_string)
{
	Command user_command;
	int i = 0;
	while (*input_string != ' ' && *input_string != '\0')
	{
		user_command.command_name[i] = *input_string;
		input_string++;
		i++;
	}
	user_command.command_name[i] = '\0';
	upperCase(user_command.command_name);

	if (*input_string == '\0')
		return user_command;
	
	input_string++;
	user_command.arg1 = strToInt(input_string);

	while (*input_string != ' ')
	{
		if (input_string == '\0')
			return user_command;
		input_string++;
	}

	input_string++;
	user_command.arg2 = strToInt(input_string);

	return user_command;
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


Command waitUntilUserInputCommand() {
	char input_string[MAX_COMMAND_LEN];
	Command user_command;

	gets(input_string);
	user_command = transformUserInputToCommandStruct(input_string);

	return user_command;
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
		printf("Invalid command entered. Try again...\n"); //debugging

	return exit_program;
}
