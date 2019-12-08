#include <stdbool.h>
#include <stdio.h>
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
#include "regex_handler_tests.h"

int main(int argc, char **argv)
{
	//Tests:
	runLineHandlerTests();
	runInputHandlerTests();
	runUtilstests();
	runParamsParserTests();
	runRegexHandlerTests();

	return 555;

	//Arguments handling:
	Params params;
	parseParams(argc, argv, &params);
	
	//Handle file:
	FILE *stream = NULL;
	bool is_file_in_use = false;
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
	while (getline(&line,&len,stream)!=-1) {
		handleLine(&params, line);
	}
	if (line) {
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

