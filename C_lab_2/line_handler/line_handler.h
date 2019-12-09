#ifndef LINE_HANDLER_H
#define LINE_HANDLER_H

#include <stdbool.h>
#include "params_parser.h"
#include "regex_handler.h"

typedef struct line_st
{
	char *line;
	bool is_it_A_line;  //needed.
	bool is_line_match; //optional
	/*more optional fields:
	 *all relevant counter fields from params	
	*/
}Line;

bool isLineMatch(Params *params, rChar *regex_string, const char *line);

void handleLine(Params *params, rChar *regex_string, const char *line);

#endif