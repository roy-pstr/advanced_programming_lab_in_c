#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "line_handler.h"
#include "params_parser.h"
#include "utils.h"
#include "flags.h"
#include "regex.h"

int main(int argc, char **argv)
{
	Params user_params;
	parseParams(argc, argv, &user_params);
	if (isFlagOn(&user_params.i)) {
		upperCaseString(user_params.sub_str);
	}
	rChar *regex_string = (rChar*)(malloc((1 + strlen(user_params.sub_str)) * sizeof(rChar)));
	setRegex(regex_string, user_params.sub_str);

	FILE *stream = NULL;
	bool is_file_in_use = false;
	is_file_in_use = paramsHasFile(&user_params);
	if (is_file_in_use) {
		openFile(&stream, user_params.filename, "r");
	}
	else {
		stream = stdin;
	}

	char *line = NULL;
	size_t len = 0;
	while (getline(&line,&len,stream)!=-1) {
		handleLine(&user_params, regex_string, line);
	}
	if (line) {
		free(line);
	}
	free(regex_string);

	if (is_file_in_use) {
		fclose(stream);
	}
	if (isFlagOn(&user_params.c)) {
		printf("%d\n", user_params.c.counter);
	}
	return 0;
}

