#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

int get_random_int(int min, int max);

int countSubStrInBuffer(const char *buffer, int buffer_size, const char *str);

void write_int_to_file(int num, const char *file_name);

void initialize_random();

#endif