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

int main(int argc, char **argv)
{
	//Tests:
	runLineHandlerTests();
	runInputHandlerTests();
	runUtilstests();
	runParamsParserTests();
	runRegexHandlerTests();

	//return 555;

	////Arguments handling:
	Params user_params;
	parseParams(argc, argv, &user_params);
	if (isFlagOn(&user_params.i)) {
		upperCaseString(user_params.sub_str);
	}
	rChar *regex_string = (rChar*)(malloc((1 + strlen(user_params.sub_str)) * sizeof(rChar)));
	setRegex(regex_string, user_params.sub_str);


	//Handle file:
	FILE *stream = NULL;
	bool is_file_in_use = false;
	is_file_in_use = paramsHasFile(&user_params);
	if (is_file_in_use) {
		openFile(&stream, user_params.filename);
	}
	else {
		stream = stdin;
	}

	//Handle lines:
	char *line = NULL;
	size_t len = 0;
	while (getline(&line,&len,stream)!=-1) {
		handleLine(&user_params, regex_string, line);
	}
	if (line) {
		free(line);
	}
	free(regex_string);

	//Close file:
	if (is_file_in_use) {
		fclose(stream);
	}
	if (isFlagOn(&user_params.c)) {
		printf("%d\n", user_params.c.counter);
	}
	return 0;
}

