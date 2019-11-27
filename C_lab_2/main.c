#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include "line_handler_tests.h"
#include "line_handler.h"
#include "input_handler.h"
#include "input_handler_tests.h"
#include "params_parser.h"
#include "params_parser_tests.h"
#include "utils.h"
#include "utils_tests.h"
#include "flags.h"

#define DEBUGGING_EXIT 0

int main(int argc, char **argv)
{
	//Tests:
	runLineHandlerTests();
	runInputHandlerTests();
	runUtilstests();
	runParamsParserTests();

	//return DEBUGGING_EXIT;

	//Argument handling:
	Params params;
	parseParams(argc, argv, &params);
	
	//Handle file:
	bool is_file_in_use = false;
	FILE *stream = NULL;
	is_file_in_use = paramsHasFile(&params);
	if (is_file_in_use) {
		openFile(&stream, params.filename);
	}
	else {
		stream = stdin;
	}

	//Handle lines:
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	while ((nread = getline(&line, &len, stream))!=-1) {
		handleLine(&params, line);
	}
	if (NULL != line) {
		free(line);
	}
	//Close file:
	if (is_file_in_use) {
		fclose(stream);
	}
	if (isFlagOn(&params.c)) {
		printf("%d", params.c.counter);
	}
	return 0;
}

