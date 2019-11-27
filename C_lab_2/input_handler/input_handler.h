#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <stdio.h>
#include "params_parser.h"

//#define RUNNING_ON_WINDOWS

bool getNextLine(bool read_from_file, FILE *fp, char **line);

void openFile(FILE** fp, const char *file_path);
#ifdef RUNNING_ON_WINDOWS
int getline(char **line, size_t *n, FILE *stream);
#endif // RUNNING_ON_WINDOWS


#endif