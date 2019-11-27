#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <stdio.h>
#include "params_parser.h"

bool getNextLine(bool read_from_file, FILE *fp, char **line);

void openFile(FILE** fp, const char *file_path);
#endif