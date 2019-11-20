#include <stdbool.h>
#include <stdio.h>
#include "line_handler_tests.h"
#include "line_handler.h"
#include "params_parser.h"

int main(int argc, char **argv)
{
	char *line = NULL;
	bool is_file = false;
	FILE *fp = NULL;
	Params params;

	//Tests:
	runLineHandlerTests();
	runInputHandlerTest();

	//Argument handling:
	//checkArgv();
	//parseFlags();
	
	
	getNextLine(is_file, fp, line);
	while (line != NULL) {
		handleLine(line, &params); //printing function.
	}
}

//void getLinesAndPrint() {
//
//	while (line = getNextLine()) {
//		if (isStrInLine()) {
//			print()
//		}
//	}
//}