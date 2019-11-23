#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "line_handler.h"
#include "flags.h"

bool isLineMatch(Params *params, const char *line)
{
	const char *sub_str = params->sub_str;
	const char *str_iterator = sub_str;
	bool invert_res = isFlagOn(&params->v);
	while (*line != '\0') {
		const char *line_iterator = line;
		while (*line_iterator == *str_iterator) {
			str_iterator++;
			line_iterator++;
			if (*str_iterator == '\0') {
				return (true ^ invert_res);
			}
		}
		str_iterator = sub_str;
		line++;
	}

	return (false ^ invert_res);
}

void handleLine(Params *params, const char *line) {
	if (isFlagOn(&params->n)) {
		addCounter(&params->n, 1); //check if starting from 0 or 1.
	}
	if (isFlagOn(&params->b)) {
		addCounter(&params->b, strlen(line)); //consider changing addCounter
	}

	if (isLineMatch(params, line)){
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

		printf("[%s]", line);
	}
	
}