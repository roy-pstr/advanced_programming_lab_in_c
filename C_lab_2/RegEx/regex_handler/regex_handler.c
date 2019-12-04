#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "regex_handler.h"

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
		break;
	}
}

void printRegexStr(const rChar *re_char) {
	while (true) {
		if (re_char->dataType == CHAR && re_char->data.c == '\0') {
			break;
		}
		printrChar(re_char);
		re_char++;
	}
}

/* putting value in rChar */
void allocString(char **str_ptr, int len) {
	if (NULL == (*str_ptr = (char*)malloc(len))) {
		printf("allocation memory for string - failed!");
		exit(-1);
	}
}
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
	/*allocString(&re_char->data.or.left, left_len);
	allocString(&re_char->data.or.right, right_len);*/
	/*strcpy_s(re_char->data.or.left, left_len, left);
	strcpy_s(re_char->data.or.right, right_len, right);*/
	re_char->data.or.left = left;
	re_char->data.or.left_len = left_len;
	re_char->data.or.right = right;
	re_char->data.or.right_len = right_len;
}

/* free allocated memory in rChar */
void freerChar(rChar *re_char) {
	if (re_char->dataType == OR) {
		free(re_char->data.or.left);
		free(re_char->data.or.right);
	}
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
//void parseRange(char *range_str, rRange *re_range) {}
//void parsePoint(char *point_str, rPoint *re_point) {}
void parseStrToRegex(char *str, rChar *regex) {
	char *left=NULL, *right = NULL, *end, *start;
	int left_len=0, right_len=0;

	while (*str != '\0') {
		switch (checkType(*str)) {
		case CHAR:
			putChar(regex, *str);
			break;
		case POINT:
			putPoint(regex);
			break;
		case OR:
			parseOr(str, &left, &left_len, &right, &right_len);
			putOr(regex, left, left_len, right, right_len);
			str += left_len+ right_len +2; //jump to )
			break;
		case RANGE:
			start = str + 1;
			end = str + 3;
			putRange(regex, *start, *end);
			str += 4; //jump to ]
			break;
		default:
			assert(false);
			break;
		}
		str++;
		regex++;
	}
}

