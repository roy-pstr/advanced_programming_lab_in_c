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

bool isSubStrAtPlace_rec(rChar *regex, const char *line)
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
		return isSubStrAtPlace_rec( regex + 1, line + 1);
	case POINT:
		return isSubStrAtPlace_rec( regex + 1, line + 1);
	case RANGE:
		if (!(regex->data.rng.start <= *line && regex->data.rng.end >= *line)){
			return false;
		}
		return isSubStrAtPlace_rec( regex + 1, line + 1);

	case OR:
		left_option_match = !strncmp(regex->data. or .left, line, regex->data. or .left_len) &&
			isSubStrAtPlace_rec( regex + 1, line + regex->data. or .left_len);
		right_option_match = !strncmp(regex->data. or .right, line, regex->data. or .right_len) &&
			isSubStrAtPlace_rec( regex + 1, line + regex->data. or .right_len);

		return left_option_match || right_option_match;

	default:
		assert(false);
		return false;
	}
}

bool isSubstrInLine(rChar *regex_string, const char *line)
{
	int line_len = strlen(line);
	for (int i = 0; i < line_len; i++)
	{
		if (isSubStrAtPlace_rec(regex_string, line + i))
			return true;
	}
	return false;
}

bool isLineMatch(Params *user_params, rChar *regex_string, const char *line)
{
	bool invert_result = isFlagOn(&user_params->v);
	bool match_exact = isFlagOn(&user_params->x);
	bool ret_val = false;
	if (match_exact){
		ret_val = (regexlen(regex_string) == strlen_without_newline(line) && 
					isSubStrAtPlace_rec(regex_string, line)		);
	}
	else {
		ret_val = isSubstrInLine(regex_string, line);
	}
	return (ret_val ^ invert_result);
}

void handleLine(Params *user_params, rChar *regex_string, const char *line)
{
	char *line_copy = (char*)malloc((1 + strlen(line)) * sizeof(char));
	strcpy(line_copy, line);

	if (isFlagOn(&user_params->i)) {
		upperCaseString(line_copy);
	}
	if (isFlagOn(&user_params->n)) {
		addCounter(&user_params->n, 1);
	}
	bool got_match = isLineMatch(user_params, regex_string, line_copy);
	free(line_copy);


	if (got_match && isFlagOn(&user_params->A)) {
		if (isFlagAEndOfBlock(&user_params->A)) { printf("--\n"); }
		setCounter(&user_params->A, user_params->A.argument);
	}

	if (got_match || isIt_A_LINE(user_params)) {
		if (isIt_A_LINE(user_params) && !got_match) {
			addCounter(&user_params->A, -1);
		}
		if (isFlagOn(&user_params->c)) {
			addCounter(&user_params->c, 1);
			return;
		}
		if (isFlagOn(&user_params->b)) {
			printf("%d:", user_params->b.counter);
		}
		if (isFlagOn(&user_params->n)) {
			printf("%d", user_params->n.counter);
			if (got_match) {
				printf(":");
			}
			else {
				printf("-");
			}
		}
		printf("%s", line);
	}

	if (isFlagOn(&user_params->b)) {
		addCounter(&user_params->b, strlen(line));
	}
}
