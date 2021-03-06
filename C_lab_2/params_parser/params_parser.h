#ifndef PARAMS_PARSER_H
#define PARAMS_PARSER_H

#include "flags.h"
#include <stdbool.h>

#define A_FLAG_COUNTER_INIT -1

typedef struct Params_st {
  char *sub_str;
  char *filename;
  Flag A;
  Flag b;
  Flag c;
  Flag i;
  Flag n;
  Flag v;
  Flag x;
  Flag E;
} Params;

bool paramsHasFile(Params *params);

void parseParams(int argc, char **argv, Params *params);

/*	Decleration for tests:	*/
void initializeParams(Params *params);

#endif
