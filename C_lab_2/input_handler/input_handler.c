#include <stdio.h>
#include <stdbool.h>
#include "input_handler.h"
#include "utils.h"

#define MAX_LINE_LENGTH 1000

void getNextLineFromSTD(char *line) {
	gets(line);
}

void getNextLineFromFile(FILE *fp, char *line) {
	if (fp != NULL) {
		fgets(line, MAX_LINE_LENGTH, fp);
	}
}

void getNextLine(bool read_from_file, FILE *fp, char *line) {
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


//bool isStringEmpty(char *str) {
//	return (str[0] == '\0');
//}