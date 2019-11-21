#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "line_handler_tests.h"
#include "line_handler.h"
#include "input_handler.h"
#include "params_parser.h"
#include "utils.h"

int main(int argc, char **argv)
{
	char *line = NULL;
	bool is_file = false;
	FILE *fp = NULL;
	Params params;

	//Tests:
	runLineHandlerTests();
	//runInputHandlerTest();

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
		handleLine(line, &params); //printing function.
	}
	if (line) {
		free(line);
	}
	if (is_file) {
		fclose(fp);
	}
	return 0;
}

