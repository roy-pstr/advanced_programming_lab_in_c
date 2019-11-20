#ifndef LINE_HANDLER_H
#define LINE_HANDLER_H
#include "params_parser.h"

bool isStringInLine(const char *str, const char *line);

void handleLine(char *line, Params params);
#endif