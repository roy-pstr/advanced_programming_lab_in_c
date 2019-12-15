#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "line_handler_tests.h"
#include "line_handler.h"
#include "input_handler.h"
#include "input_handler_tests.h"
#include "params_parser.h"
#include "params_parser_tests.h"
#include "utils.h"
#include "utils_tests.h"
#include "flags.h"
#include "regex_handler.h"
#include "regex_handler_tests.h"

/*
To Do:
-	change params name to user_arg_params or something eq.
-	consider changing some regex names (e.g put<->set)
-	change line hander functions:
		- make line a struct with correct parameters
		- consider not to pass params as an argument
-	recursive implimentation for islinematch
-	discuss the edge case of \n in end of line (check strlen_without_newline in utils and putRegax CHAR case)
*/
int main(int argc, char **argv)
{
	////Tests:
	runLineHandlerTests();
	runInputHandlerTests();
	runUtilstests();
	runParamsParserTests();
	runRegexHandlerTests();

	//return 555;

	////Arguments handling:
	Params params;
	parseParams(argc, argv, &params);
	if (isFlagOn(&params.i)) {
		upperCaseString(params.sub_str);
	}
	rChar *regex_string = (rChar*)(malloc((1 + strlen(params.sub_str)) * sizeof(rChar)));
	putRegex(regex_string, params.sub_str);


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
		handleLine(&params, regex_string, line);
	}
	if (line) {
		free(line);
	}
	free(regex_string);

	//Close file:
	if (is_file_in_use) {
		fclose(stream);
	}
	if (isFlagOn(&params.c)) {
		printf("%d\n", params.c.counter);
	}
	return 0;
}

