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

void initializeFlag(Flag *flag)
{
	flag->counter = 0;
	offFlag(flag);
}

void addCounter(Flag *flag, int value)
{
	assert(isFlagOn(flag));
	flag->counter += value;
}
