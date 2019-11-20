#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <stdio.h>
#include "params_parser.h"

void getNextLine(bool read_from_file, FILE *fp, char *line);

bool isFileInUse(Params params);
#endif