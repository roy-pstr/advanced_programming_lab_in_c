#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <string.h>

#define STRINGS_ARE_EQUAL( Str1, Str2 ) ( strcmp( (Str1), (Str2) ) == 0 )

void upperCaseString(char *str);

bool isStringEmpty(const char *str);
bool isStringNewLine(const char *str);

bool isDigits(const char *str);

#endif

