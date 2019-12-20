#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STRINGS_ARE_EQUAL( Str1, Str2 ) ( strcmp( (Str1), (Str2) ) == 0 )

int strlen_without_newline(const char *str);

void upperCaseString(char *str);

bool isDigits(const char *str);

void openFile(FILE** fp, const char *file_path, const char *mode);

#endif

