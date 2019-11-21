#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "input_handler.h"
#include "utils.h"

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*Comments for Paster:
 * Look at this shit: https://moodle.tau.ac.il/mod/forum/discuss.php?d=15198
 * We have new function called paramsHasFile(Params *params)
 */
 /*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#define MAX_LINE_LENGTH 1000 //TBR

void getNextLineFromSTD(char **line) {
	*line = (char *)realloc(*line, MAX_LINE_LENGTH * sizeof(char));
	assert((*line != NULL));
	fgets(*line, sizeof(*line), stdin);
}

void getNextLineFromFile(FILE *fp, char **line) {
	if (fp != NULL) {
		fgets(*line, MAX_LINE_LENGTH, fp);
	}
}

void getNextLine(bool read_from_file, FILE *fp, char **line) {
	if (read_from_file) {
		getNextLineFromFile(fp, line);
	}
	else {
		getNextLineFromSTD(line);
	}
}

bool isFileInUse(Params *params) {
	return (params->filename!=NULL);
}

void openFile(FILE* fp, const char *file_path) {
	fp = fopen(file_path, "r");
	assert((fp != NULL)); //Can not open file
}
