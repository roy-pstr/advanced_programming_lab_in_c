#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define STRINGS_ARE_EQUAL(Str1, Str2) (strcmp((Str1), (Str2)) == 0)

unsigned int strlenWithoutNewline(const char *str);

void upperCaseString(char *str);

bool isDigits(const char *str);

void openFile(FILE **fp, const char *file_path, const char *mode);

#endif
