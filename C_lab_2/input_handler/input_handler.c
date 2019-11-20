#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "input_handler.h"
#include "utils.h"

#define MAX_LINE_LENGTH 1000 //TBR

bool getNextLineFromSTD(char **line) {
	*line = (char *)realloc(*line, MAX_LINE_LENGTH * sizeof(char));
	assert((*line != NULL));
	fgets(*line, MAX_LINE_LENGTH, stdin);
	return (*line!='\n');
}

bool getNextLineFromFile(FILE *fp, char **line) {
	assert(fp != NULL);
	*line = (char *)realloc(*line, MAX_LINE_LENGTH * sizeof(char));
	assert(*line != NULL);
	*line = fgets(*line, MAX_LINE_LENGTH, fp);
	return (*line != NULL);
}

bool getNextLine(bool read_from_file, FILE *fp, char **line) {
	if (read_from_file) {
		return getNextLineFromFile(fp, line);
	}
	else {
		return getNextLineFromSTD(line);
	}
}

bool isFileInUse(Params *params) {
	return (params->filename!=NULL);
}

void openFile(FILE** fp, const char *file_path) {
	*fp = fopen(file_path, "r");
	assert((*fp != NULL)); 
}
