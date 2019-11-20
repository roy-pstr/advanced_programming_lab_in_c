#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "input_handler.h"
#include "utils.h"

#define MAX_LINE_LENGTH 1000 //TBR

void getNextLineFromSTD(char **line) {
	*line = (char *)realloc(*line, MAX_LINE_LENGTH * sizeof(char));
	assert((*line != NULL));
	fgets(*line, sizeof(*line), stdin);
}

void getNextLineFromFile(FILE *fp, char **line) {
	if (fp != NULL) {
		fgets(line, MAX_LINE_LENGTH, fp);
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
	return (isStringEmpty(params->file_in));
}

void openFile(FILE* fp, const char *file_path) {
	fp = fopen(file_path, "r");
	assert((fp != NULL)); //Can not open file
}
