#ifndef CHAR_COMPRATION_H
#define CHAR_COMPRATION_H

#include <stdbool.h>
#include "regex_handler.h"
#include "params_parser.h"

bool regexCharMatch(rChar regex_string, char *mid_line_ptr, int *chars_proceed_in_line);
bool charsAreEqual(Params *params, char line_char, char substr_char);


#endif