#ifndef FLAG_H
#define FLAG_H

#include <stdbool.h>

#define A_FLAG_COUNTER_INIT -1 

typedef struct Flag_st {
	bool is_on;
	int argument;
	int counter;
}Flag;

bool isFlagOn(Flag *flag);

void onFlag(Flag *flag);

void offFlag(Flag *flag);

void initializeFlag(Flag *flag);

void addCounter(Flag *flag, int value);

void setCounter(Flag * flag, int value);

void setArgument(Flag *flag, int value);

bool isFlagAEndOfBlock(Flag *A_flag);

#endif
