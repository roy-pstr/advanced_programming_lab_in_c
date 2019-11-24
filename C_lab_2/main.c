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

#define DEBUGGING_EXIT 0

int main(int argc, char **argv)
{
	char *line = NULL;
	bool is_file = false;
	FILE *fp = NULL;
	Params params;

	//Tests:
	runLineHandlerTests();
	runInputHandlerTests();
	runUtilstests();
	runParamsParserTests();

	return DEBUGGING_EXIT;

	//Argument handling:
	//checkArgv();
	parseParams(argc, argv, &params);
	
	//Handle file
	is_file = isFileInUse(&params);
	if (is_file) {
		openFile(&fp, params.filename);
	}

	//Handle lines
	while (getNextLine(is_file, fp, &line)) {
		handleLine(&params, line); //printing/counting function.
	}
	if (line) {
		free(line);
	}
	if (is_file) {
		fclose(fp);
	}
	if (isFlagOn(&params.c)) {
		printf("%d",&params.c, 1);
	}

	return 0;
}

