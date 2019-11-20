#include <stdio.h>
#include "params_parser.h"
#include "flags.h"
#include "utils.h"


void initializeParams(Params *params) 
{
	params->sub_str  = NULL;
	params->filename = NULL;
	initializeFlag(&params->A);
	initializeFlag(&params->b);
	initializeFlag(&params->c);
	initializeFlag(&params->i);
	initializeFlag(&params->n);
	initializeFlag(&params->v);
	initializeFlag(&params->x);
	initializeFlag(&params->E);
}

void parseParams(int argc, char **argv, Params *params)
{
	initializeParams(params);
	bool has_filename = false;
	for (int i = 1; i < argc - 2; i++) {
		{
			if (STRINGS_ARE_EQUAL(argv[i], "-A")) {
				onFlag(&params->A);
				i++;
				assert(isDigits(argv[i]));
				addCounter(&params->A, atoi(argv[i]));
			}
			else if (STRINGS_ARE_EQUAL(argv[i], "-b")) {
				onFlag(&params->b);
			}
			else if (STRINGS_ARE_EQUAL(argv[i], "-c")) {
				onFlag(&params->c);
			}
			else if (STRINGS_ARE_EQUAL(argv[i], "-i")) {
				onFlag(&params->i);
			}
			else if (STRINGS_ARE_EQUAL(argv[i], "-n")) {
				onFlag(&params->n);
			}
			else if (STRINGS_ARE_EQUAL(argv[i], "-v")) {
				onFlag(&params->n);
			}
			else if (STRINGS_ARE_EQUAL(argv[i], "-x")) {
				onFlag(&params->n);
			}
			else if (STRINGS_ARE_EQUAL(argv[i], "-E")) {
				onFlag(&params->n);
			}
			else if (i == argc - 2) {
				has_filename = true;
			}
		}
		if (has_filename){
			params->filename = argv[argc - 1];
			params->sub_str = argv[argc - 2];
		}
		else{
			params->sub_str = argv[argc - 1];
		}
	}
}
