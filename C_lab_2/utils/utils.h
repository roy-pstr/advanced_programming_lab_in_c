#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define STRINGS_ARE_EQUAL( Str1, Str2 ) ( strcmp( (Str1), (Str2) ) == 0 )

bool isStringEmpty(char *str);

bool isDigits(char *str);

#endif

