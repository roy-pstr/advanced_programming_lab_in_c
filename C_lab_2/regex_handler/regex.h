#ifndef REGEX_H
#define REGEX_H
#include <stdbool.h>

enum rCharTypes { CHAR, POINT, OR, RANGE };

#define OR_LENGTH(or) (or.left_len + or.right_len + OR_ADD_TO_STRINGS_LENGTH)

typedef struct rOr_st {
  const char *left;
  int left_len;
  const char *right;
  int right_len;
} rOr;
typedef struct rRange_st {
  char start;
  char end;
} rRange;
typedef bool rPoint;
typedef struct rChar_st {
  enum rCharTypes dataType;
  union values_un {
    char c;
    rPoint p;
    rOr or ;
    rRange rng;
  } data;
} rChar;

bool endOfRegexStr(const rChar *regex_str);
void setRegex(rChar *re_str, char *str);
unsigned int regexlen(rChar *regex);

/*	Decleration for tests:	*/
void setChar(rChar *re_char, const char c);

void setPoint(rChar *re_char);

void setRange(rChar *re_char, const char start, const char end);

void setOr(rChar *re_char, const char *left, int left_len, const char *right, int right_len);
#endif