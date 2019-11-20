#ifndef PARAMS_PARSER_H
#define PARAMS_PARSER_H

#include <stdio.h>
#include "flags.h"


typedef struct Params_st
{
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

}Params;

void initializeParams(Params *flags);

#endif
