#include "utils.h"
#include <assert.h>

void upperCaseChar(char *p_char)
{
  if (*p_char >= 'a' && *p_char <= 'z') {
    *p_char -= ' ';
  }
}

void upperCaseString(char *str)
{
  while (*str != '\0') {
    upperCaseChar(str);
    str++;
  }
}

bool isDigits(const char *str)
{
  while (*str != '\0') {
    if (!(*str >= '0' && *str <= '9')) {
      return false;
    }
    str++;
  }
  return true;
}

unsigned int strlenWithoutNewline(const char *str)
{
  int len = strlen(str);
  return (str[len - 1] == '\n') ? (len - 1) : len;
}

void openFile(FILE **fp, const char *file_path, const char *mode)
{
  *fp = fopen(file_path, mode);
  assert((*fp != NULL));
}