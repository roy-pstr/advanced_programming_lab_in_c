#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regex_handler.h"

/* printing rChar */
void printrOr(const rOr *or) {
	printf("(%s|%s)",or->left,or->right);
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
	allocString(&re_char->data.or.left, left_len);
	allocString(&re_char->data.or.right, right_len);
	strcpy_s(re_char->data.or.left, left_len, left);
	strcpy_s(re_char->data.or.right, right_len, right);
}

/* free allocated memory in rChar */
void freerChar(rChar *re_char) {
	if (re_char->dataType == OR) {
		free(re_char->data.or.left);
		free(re_char->data.or.right);
	}
}