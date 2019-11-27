#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "input_handler.h"
#include "utils.h"
//#define _GNU_SOURCE
#define LINUX_FLAG //debug
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*Comments for Paster:
 * Look at this shit: https://moodle.tau.ac.il/mod/forum/discuss.php?d=15198
 */
 /*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#define MAX_LINE_LENGTH 1000 //TBR

bool getNextLineFromSTD(char **line) {
	*line = (char *)realloc(*line, MAX_LINE_LENGTH * sizeof(char));
	assert((*line != NULL));
	fgets(*line, MAX_LINE_LENGTH, stdin);
	return (*line[0]!='\n');
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
#ifdef LINUX_FLAG
		size_t len = 0;
		ssize_t nread;
		nread = getline(line, &len, fp);
		return (nread!=-1);
#endif
#ifndef LINUX_FLAG
		return getNextLineFromFile(fp, line);
#endif
	}
	else {
#ifdef LINUX_FLAG
		size_t len = 0;
		ssize_t nread;
		nread = getline(line, &len, stdin);
		return (nread != -1);
#endif
#ifndef LINUX_FLAG
		return getNextLineFromSTD(line);
#endif
	}
}

void openFile(FILE** fp, const char *file_path) {
	*fp = fopen(file_path, "r");
	assert((*fp != NULL)); 
}
