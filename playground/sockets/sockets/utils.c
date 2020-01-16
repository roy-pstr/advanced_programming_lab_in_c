#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int get_random_int(int min, int max)
{
  assert(max >= min);
  int range = max - min + 1;
  int random_int = rand();
  random_int = random_int % range;
  return random_int + min;
}

bool isBufferStartsWithStr(const char *buffer, int buffer_size, const char *str)
{
  int str_len = strlen(str);
  for (int i = 0; i < str_len; i++) {
    if (i >= buffer_size) {
      return false;
    }
    if (str[i] != buffer[i]) {
      return false;
    }
  }
  return true;
}

int countSubStrInBuffer(const char *buffer, int buffer_size, const char *str)
{
  int counter = 0;
  for (int i = 0; i < buffer_size; i++) {
    if (isBufferStartsWithStr(buffer + i, buffer_size - i, str)) {
      counter++;
    }
  }
  return counter;
}

void write_int_to_file(int num, const char *file_name)
{
  FILE *f = NULL;
  f = fopen(file_name, "w");
  assert(f);
  fprintf(f, "%d\n", num);
  fclose(f);
}

void initialize_random() { srand(time(NULL)); }
