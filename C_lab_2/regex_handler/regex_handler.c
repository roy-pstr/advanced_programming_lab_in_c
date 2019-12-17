#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "regex_handler.h"


/*
TODO:	
	support or regex in shape of (str|)
	check about the range of point (33-126) ascii
*/
bool endOfRegexStr(const rChar *regex_str)
{
	return regex_str->dataType == CHAR && regex_str->data.c == '\0';
}

/* printing rChar */
void printrOr(const rOr *or) {
	char *left, *right;
	int i;
	left = or->left;
	right = or->right;
	printf("(");
	for (i = 0; i < or->left_len; i++)
	{
		printf("%c", *left);
		left++;
	}
	printf("|");
	for (i = 0; i < or ->right_len; i++)
	{
		printf("%c", *right);
		right++;
	}
	printf(")");
}

void printrRange(const rRange * rng ) {
	printf("[%c-%c]", rng->start, rng->end);
}

void printrPoint() {
	printf(".");
}

void printrChar(const rChar *re_char) {
	switch (re_char->dataType)
	{
	case CHAR:
		printf("%c", re_char->data.c);
		break;
	case POINT:
		printrPoint();
		break;
	case OR:
		printrOr(&re_char->data.or);
		break;
	case RANGE:
		printrRange(&re_char->data.rng);
		break;
	default:
		assert(false);
		break;
	}
}

void printRegexStr(const rChar *re_char) {
	while (!endOfRegexStr(re_char)) {
		printrChar(re_char);
		re_char++;
	}
	printf("\n");
}


/* misc */
enum rCharTypes checkType(const char str_ptr) {
	switch (str_ptr) {
	case '.':
		return POINT;
		break;
	case '[':
		return RANGE;
		break;
	case '(':
		return OR;
		break;
	default:
		return CHAR;
		break;
	}
}

int rCharSize(rChar *re_char) {
	switch (re_char->dataType)
	{
	case CHAR:
		return CHAR_LENGTH;
	case POINT:
		return CHAR_LENGTH;
	case OR:
		return OR_LENGTH(re_char->data.or);
	case RANGE:
		return RANGE_LENGTH;
	default:
		assert(false);
		return -1;
	}
}

int regexlen(rChar * regex)
{
	int len = 0;
	while (!endOfRegexStr(regex)) {
		len = len + rCharSize(regex);
		regex++;
	}
	return len;
}


/* parsing */
void parseOr(const char *or_str, char **left, int *left_len, char **right, int *right_len){
	/* validate */
	if (*or_str != '(') {
		return;
	}

	/* search for left length */
	*left_len = 0;
	or_str++;
	*left = or_str;
	while (*or_str != '|') {
		*left_len+=1;
		or_str++;
	}

	/* search for right length */
	*right_len = 0;
	or_str++;
	*right = or_str;
	while (*or_str != ')') {
		*right_len += 1;
		or_str++;
	}
}

/* putting value in rChar */
void putChar(rChar *re_char, const char c) {
	re_char->dataType = CHAR;
	re_char->data.c = c;
}

void putPoint(rChar *re_char) {
	re_char->dataType = POINT;
	re_char->data.p = true;
}

void putRange(rChar *re_char, const char start, const char end) {
	re_char->dataType = RANGE;
	re_char->data.rng.start = start;
	re_char->data.rng.end = end;
}

void putOr(rChar *re_char, const char *left, int left_len, const char *right, int right_len) {
	re_char->dataType = OR;
	re_char->data. or .left = left;
	re_char->data. or .left_len = left_len;
	re_char->data. or .right = right;
	re_char->data. or .right_len = right_len;
}

void putRegex(rChar * re_str, char * str) {
	char *left=NULL, *right = NULL, *end, *start;
	int left_len=0, right_len=0;
	while (*str != '\0') {
		switch (checkType(*str)) {
		case CHAR:
			if (*str == '\\'){ 
				str++;
			}
			putChar(re_str, *str); 
			break;
		case POINT:
			putPoint(re_str);
			break;
		case OR:
			parseOr(str, &left, &left_len, &right, &right_len);
			putOr(re_str, left, left_len, right, right_len);
			str += left_len+ right_len +2; //jump to )
			break;
		case RANGE:
			start = str + 1;
			end = str + 3;
			putRange(re_str, *start, *end);
			str += 4; //jump to ]
			break;
		default:
			assert(false);
			break;
		}
		str++;
		re_str++;
	}
	putChar(re_str, '\0');
}


/* comprasion regex to regex */
bool isrOrEqual(rChar * left, rChar * right) {
	if (left->data.or.left_len != right->data.or.left_len)
		return false;
	if (left->data.or.right_len != right->data.or.right_len)
		return false;
	return (!strncmp(left->data.or.left, right->data.or.left, left->data.or.left_len)) &&
		   (!strncmp(left->data.or.right, right->data.or.right, left->data.or.right_len));
}

bool isrRangeEqual(rChar * left, rChar * right) {
	return ((left->data.rng.start == right->data.rng.start) && (left->data.rng.end == right->data.rng.end));
}

bool isrCharEqual(rChar * left, rChar * right) {
	if (left->dataType != right->dataType) {
		return false;
	}

	switch (left->dataType) {
	case CHAR:
		return (left->data.c == right->data.c);
	case POINT:
		return true;
	case OR:
		return isrOrEqual(left, right);
	case RANGE:
		return isrRangeEqual(left, right);
	default:
		assert(false);
		return false;
	}
}
/*naive!*/
bool isRegexStrEqual(rChar * left, rChar * right) {
	while (isrCharEqual(left, right)) {
		if (endOfRegexStr(left) || endOfRegexStr(right)) {
			if ((endOfRegexStr(left) && endOfRegexStr(right))) {
				return true;
			}
			else {
				return false;
			}
		}
		left++;
		right++;
	}
	assert(false);
	return false;
}


/* comprasion regex char to string */ //[Doron: tests???]
bool isOrMatch(rChar * regex, const char * str) {
	return (strncmp(regex->data.or.left, str, regex->data.or.left_len))||
		(strncmp(regex->data.or.right, str, regex->data.or.right_len));
}

bool isRangeMatch(rChar * regex, const char * str) {
		char temp_rng[RANGE_LENGTH] = { '[',regex->data.rng.start ,',',regex->data.rng.end, ']' };
		return (strncmp(temp_rng, str, RANGE_LENGTH) == 0);
}

bool isRegexMatch(rChar * regex, const char * str, int * len) {
	switch (regex->dataType) {
	case CHAR:
		*len = 1;
		return (regex->data.c == *str);
	case POINT:
		*len = 1;
		return (*str != '\0');
	case OR:
		*len = OR_LENGTH(regex->data. or );
		return isOrMatch(regex, str);
	case RANGE:
		*len = RANGE_LENGTH;
		return isRangeMatch(regex, str);
	default:
		assert(false);
		return false;
	}
}



