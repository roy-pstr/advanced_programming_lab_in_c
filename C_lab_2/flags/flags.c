#include <assert.h>
#include "flags.h"

void onFlag(Flag *flag)
{
	flag->is_on = true;
}

void offFlag(Flag *flag)
{
	flag->is_on = false;
}

bool isFlagOn(Flag *flag)
{
	return (flag->is_on);
}

void addCounter(Flag *flag, int value)
{
	flag->counter += value;
}

void setCounter(Flag *flag, int value)
{
	flag->counter = value;
}

void setArgument(Flag *flag, int value)
{
	flag->argument = value;
}

void initializeFlag(Flag *flag)
{
	setCounter(flag, 0);
	offFlag(flag);
}

bool isFlagAEndOfBlock(Flag *A_flag)
{
	return (A_flag->counter == 0);
}