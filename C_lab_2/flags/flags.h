#ifndef FLAG_H
#define FLAG_H

#include <stdbool.h>

typedef struct Flag_st {
	bool is_on;
	int counter;
}Flag;

bool isFlagOn(Flag *flag);

void onFlag(Flag *flag);

void offFlag(Flag *flag);

void initializeFlag(Flag *flag);

void addCounter(Flag *flag, int value);

#endif
