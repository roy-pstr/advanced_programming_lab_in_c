#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "user_command.h"

#define STRINGS_ARE_EQUAL( Str1, Str2 ) ( strcmp( (Str1), (Str2) ) == 0 )

void printCommand(Command *cmd)
{	/*debug function*/
	printf("---printing command---\n");
	printf("name: %s\n", cmd->command_name);
	printf("arg1: %d\n", cmd->arg1);
	printf("arg2: %d\n", cmd->arg2);
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

void strToCommand(char *input_string, Command *user_command)
{
	char *token = strtok(input_string, " ");
	strcpy(user_command->command_name, token);
	upperCase(user_command->command_name);

	for (int i = 0; i < 2; i++)
	{
		token = strtok(NULL, " ");
		if (NULL == token)	return;

		if (i==0)
			user_command->arg1 = atoi(token);
		else
			user_command->arg2 = atoi(token);
	}
}

void executeAddEnd(Command *user_command, Node **head)
{
	List_addEnd(head, user_command->arg1);
}

void executeAddStart(Command *user_command, Node **head)
{
	List_addItemByIndex(head, user_command->arg1, 0);
}

bool executeAddAfter(Command *user_command, Node **head)
{
	bool exit_program = false;
	int previous_item_index = List_findIndex(*head, user_command->arg2);
	if (previous_item_index == INDEX_NOT_EXISTS)
	{
		printf("Sorry, can't find %d in the list. Exiting...\n", user_command->arg2);
		exit_program = true;
	}
	else
		List_addItemByIndex(head, user_command->arg1, previous_item_index+1);

	return exit_program;
}

void executeIndex(Command *user_command, Node **head)
{
	int index = List_findIndex(*head, user_command->arg1);
	if (index == INDEX_NOT_EXISTS)
		printf("-1\n");
	else
		printf("%d\n", index);
}

bool executeDel(Command *user_command, Node **head)
{
	bool exit_program = false;
	int retval = List_deleteItem(head, user_command->arg1);
	if (retval == ERROR_CODE)
	{
		printf("Index is too large. Exiting...\n");
		exit_program = true;
	}

	return exit_program;
}

void executePrint(Node **head)
{
	List_printList(*head);
}

bool executeOneCommand(Command *user_command, Node **head)
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
		printf("Invalid command entered. Try again...\n");

	return exit_program;
}

void readNextCommand(Command *user_command)
{
	char input_string[MAX_COMMAND_LEN];
	gets(input_string);

	strToCommand(input_string, user_command);
}