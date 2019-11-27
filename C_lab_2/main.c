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
	bool is_file_in_use = false;
	FILE *fp = NULL;
	Params params;

	//Tests:
	runLineHandlerTests();
	runInputHandlerTests();
	runUtilstests();
	runParamsParserTests();

	//return DEBUGGING_EXIT;

	//Argument handling:
	parseParams(argc, argv, &params);
	
	//Handle file:
	is_file_in_use = paramsHasFile(&params);
	if (is_file_in_use) {
		openFile(&fp, params.filename);
	}

	//Handle lines:
	while (getNextLine(is_file_in_use, fp, &line)) {
		handleLine(&params, line);
		//printf("[debuggin getline: %s]\n", line); //debugging
		
	}
	if (NULL != line) {
		//printf("[free line]\n");
		free(line);
		//printf("[debuggin line after free: %s]\n", line); //debugging
	}
	//Close file:
	if (is_file_in_use) {
		fclose(fp);
	}
	if (isFlagOn(&params.c)) {
		printf("%d", params.c.counter);
	}
	return 0;
}

