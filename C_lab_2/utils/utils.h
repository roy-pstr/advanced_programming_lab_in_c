#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <string.h>

#define STRINGS_ARE_EQUAL( Str1, Str2 ) ( strcmp( (Str1), (Str2) ) == 0 )

int strlen_without_newline(const char *str);

void upperCaseString(char *str);

bool isStringEmpty(const char *str);

bool isStringNewLine(const char *str);

bool isDigits(const char *str);

#endif

