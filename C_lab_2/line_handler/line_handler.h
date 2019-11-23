#ifndef LINE_HANDLER_H
#define LINE_HANDLER_H
#include "params_parser.h"

bool isLineMatch(Params *params, const char *line);

void handleLine(Params *params, const char *line);
#endif