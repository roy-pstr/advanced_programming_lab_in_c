#ifndef REGEX_HANDLER_H
#define REGEX_HANDLER_H
#include <stdbool.h>

/*
		Regex handler

	Assumptions:
		- no backslash for now...
		- for now avoided the need fro malloc!

	Done:
		- Putting functions
		- Printing functions
		- Parsing functions
		- Comprasion functions

	To do:
		- Regex str to String functions (malloc strings??)  - do we need it?
*/

enum rCharTypes {
	CHAR,
	POINT,
	OR,
	RANGE
};

typedef struct rOr_st {
	char *left;
	int left_len;
	char *right;
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
}rChar;

void printrChar(const rChar *re_char);
void printRegexStr(const rChar * re_char);

void putChar(rChar *re_char, const char c);
void putPoint(rChar *re_char);
void putRange(rChar *re_char, const char start, const char end);
void putOr(rChar *re_char, const char *left, int left_len, const char *right, int right_len);
void putRegex(rChar * re_str, char * str);

bool isrCharEqual(rChar * left, rChar * right);
bool isRegexStrEqual(rChar * left, rChar * right);

//void freerChar(rChar *re_char);



#endif