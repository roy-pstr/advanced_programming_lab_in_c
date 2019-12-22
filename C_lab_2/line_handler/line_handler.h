#ifndef LINE_HANDLER_H
#define LINE_HANDLER_H

#include "params_parser.h"
#include "regex.h"

void handleLine(Params *params, rChar *regex_string, const char *line);

/*	Decleration for tests:	*/
bool isLineMatch(Params *user_params, rChar *regex_string, const char *line);

#endif