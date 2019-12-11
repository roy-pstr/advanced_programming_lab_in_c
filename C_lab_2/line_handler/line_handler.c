#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regex_handler.h"
#include "line_handler.h"
#include "flags.h"
#include "utils.h"
#include "char_comprasion.h"

bool isSubStrAtPlace(Params *params, rChar *regex_string, const char *mid_line_ptr)
{
	int chars_proceed_in_line=0;

	while (true) {
		if (endOfRegexStr(regex_string)) {
			return true;
		}
		if (isRegexMatch(regex_string, mid_line_ptr, &chars_proceed_in_line)){
			regex_string++;
			mid_line_ptr += chars_proceed_in_line;
		}
		else
			return false;
	}
}
//bool isSubStrAtPlace_rec(Params *params, rChar *regex_string, const char *mid_line_ptr)
//{
//	int line_step = 0;
//
//	/* stop condition */
//	if (NULL==regex_string) {
//		return false;
//	}
//	if (endOfRegexStr(regex_string)) {
//		return true;
//	}
//
//	/* recursive call */
//	bool ret_val = isSubStrAtPlace_rec(params, regex_string++, mid_line_ptr++);
//	return ret_val && isRegexMatch(regex_string, mid_line_ptr, &line_step);
//}
bool isSubstrInLine(Params *params, rChar *regex_string, const char *line)
{
	int line_len = strlen(line);
	for (int i = 0; i < line_len; i++)
	{
		if (isSubStrAtPlace(params, regex_string, line + i))
			return true;
	}
	return false;
}

bool isLineMatch(Params *params, rChar *regex_string, const char *line)
{
	bool invert_result = isFlagOn(&params->v);
	return (isSubstrInLine(params, regex_string,line) ^ invert_result);
}

void handleLine(Params *params, rChar *regex_string, const char *line)
{
	char *line_copy = (char*)malloc((1 + strlen(line)) * sizeof(char));
	strcpy(line_copy, line);

	if (isFlagOn(&params->i)) {
		upperCaseString(line_copy);
	}

	if (isFlagOn(&params->n)) {
		addCounter(&params->n, 1);
	}

	bool got_match = isLineMatch(params, regex_string, line_copy);
	free(line_copy);

	if (got_match) {
		if (isFlagOn(&params->c)) {
			addCounter(&params->c, 1);
			return;
		}
		if (isFlagOn(&params->b)) {
			printf("%d:", params->b.counter);
		}
		if (isFlagOn(&params->n)) {
			printf("%d", params->n.counter);
			if (0) {				//TBR: if it is a -A line
				printf("-");
			}
			else {
				printf(":");
			}
		}
		printf("%s", line);
	}

	if (isFlagOn(&params->b)) { //no need for this if
		addCounter(&params->b, strlen(line));
	}
}