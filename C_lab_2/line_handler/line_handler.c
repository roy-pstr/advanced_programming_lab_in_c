#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "regex_handler.h"
#include "line_handler.h"
#include "flags.h"
#include "utils.h"

bool isIt_A_LINE(Params *params)
{
	return  (isFlagOn(&params->A)) && (params->A.counter > 0);
}

////[Doron]: delete_me!!
//bool isSubStrAtPlace(Params *params, rChar *regex_string, const char *mid_line_ptr)
//{
//	int chars_proceed_in_line=0;
//
//	while (true) {
//		if (endOfRegexStr(regex_string)) {
//			return true;
//		}
//		if (isRegexMatch(regex_string, mid_line_ptr, &chars_proceed_in_line)){
//			regex_string++;
//			mid_line_ptr += chars_proceed_in_line;
//		}
//		else
//			return false;
//	}
//}

bool isSubStrAtPlace_rec(Params *params, rChar *regex, const char *line)
{
	/* stop conditions */
	if (endOfRegexStr(regex))
		return true;

	if (*line == '\0'){
		return false;
	}

	bool left_option_match, right_option_match;

	switch (regex->dataType) {
	case CHAR:
		if (regex->data.c != *line) {
			return false;
		}
		return isSubStrAtPlace_rec(params, regex + 1, line + 1);
	case POINT:
		return isSubStrAtPlace_rec(params, regex + 1, line + 1);
	case RANGE:
		if (!(regex->data.rng.start <= *line && regex->data.rng.end >= *line)){
			return false;
		}
		return isSubStrAtPlace_rec(params, regex + 1, line + 1);

	case OR:
		left_option_match = !strncmp(regex->data. or .left, line, regex->data. or .left_len) &&
			isSubStrAtPlace_rec(params, regex + 1, line + regex->data. or .left_len);
		right_option_match = !strncmp(regex->data. or .right, line, regex->data. or .right_len) &&
			isSubStrAtPlace_rec(params, regex + 1, line + regex->data. or .right_len);

		return left_option_match || right_option_match;

	default:
		assert(false);
		return false;
	}
}

bool isSubstrInLine(Params *params, rChar *regex_string, const char *line)
{
	int line_len = strlen(line);
	for (int i = 0; i < line_len; i++)
	{
		if (isSubStrAtPlace_rec(params, regex_string, line + i))
			return true;
	}
	return false;
}

bool isLineMatch(Params *params, rChar *regex_string, const char *line)
{
	bool invert_result = isFlagOn(&params->v);
	bool match_exact = isFlagOn(&params->x);
	bool ret_val = false;
	if (match_exact){
		ret_val = (regexlen(regex_string) == strlen_without_newline(line) && 
					isSubStrAtPlace_rec(params, regex_string, line)		);
	}
	else {
		ret_val = isSubstrInLine(params, regex_string, line);
	}
	return (ret_val ^ invert_result);
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


	if (got_match && isFlagOn(&params->A)) {
		if (isFlagAEndOfBlock(&params->A)) { printf("--\n"); }
		setCounter(&params->A, params->A.argument);
	}

	if (got_match || isIt_A_LINE(params)) {
		if (isIt_A_LINE && !got_match) {
			addCounter(&params->A, -1);
		}
		if (isFlagOn(&params->c)) {
			addCounter(&params->c, 1);
			return;
		}
		if (isFlagOn(&params->b)) {
			printf("%d:", params->b.counter);
		}
		if (isFlagOn(&params->n)) {
			printf("%d", params->n.counter);
			if (got_match) {
				printf(":");
			}
			else {
				printf("-");
			}
		}
		printf("%s", line);
	}

	if (isFlagOn(&params->b)) {
		addCounter(&params->b, strlen(line));
	}
}
