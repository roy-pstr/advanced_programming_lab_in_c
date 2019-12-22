#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "regex_handler.h"
#include "regex_handler_tests.h"

#define MAX_TEST_STRING_LEN 256 

bool isrOrEqual(rChar * left, rChar * right)
{
	if (left->data. or .left_len != right->data. or .left_len)
		return false;
	if (left->data. or .right_len != right->data. or .right_len)
		return false;
	return (!strncmp(left->data. or .left, right->data. or .left, left->data. or .left_len)) &&
		(!strncmp(left->data. or .right, right->data. or .right, left->data. or .right_len));
}

bool isrRangeEqual(rChar * left, rChar * right)
{
	return ((left->data.rng.start == right->data.rng.start) && (left->data.rng.end == right->data.rng.end));
}

bool isrCharEqual(rChar * left, rChar * right)
{
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

bool isRegexStrEqual(rChar * left, rChar * right)
{
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

void printrOr(const rOr * or )
{
	const char *left, *right;
	int i;
	left = or ->left;
	right = or ->right;
	printf("(");
	for (i = 0; i < or ->left_len; i++)
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

void printrRange(const rRange * rng)
{
	printf("[%c-%c]", rng->start, rng->end);
}

void printrPoint()
{
	printf(".");
}

void printrChar(const rChar *re_char)
{
	switch (re_char->dataType)
	{
	case CHAR:
		printf("%c", re_char->data.c);
		break;
	case POINT:
		printrPoint();
		break;
	case OR:
		printrOr(&re_char->data. or );
		break;
	case RANGE:
		printrRange(&re_char->data.rng);
		break;
	default:
		assert(false);
		break;
	}
}

void printRegexStr(const rChar *re_char)
{
	while (!endOfRegexStr(re_char)) {
		printrChar(re_char);
		re_char++;
	}
	printf("\n");
}

bool parsingTest()
{
	rChar regex[50], ref_regex[50];
	char regex_test_str[MAX_TEST_STRING_LEN] = "[0-9]; .; char; (str1|str2);\n";
	setRange(&ref_regex[0], '0', '9');
	setChar(&ref_regex[1], ';');
	setChar(&ref_regex[2], ' ');
	setPoint(&ref_regex[3]);
	setChar(&ref_regex[4], ';');
	setChar(&ref_regex[5], ' ');
	setChar(&ref_regex[6], 'c');
	setChar(&ref_regex[7], 'h');
	setChar(&ref_regex[8], 'a');
	setChar(&ref_regex[9], 'r');
	setChar(&ref_regex[10], ';');
	setChar(&ref_regex[11], ' ');
	setOr(&ref_regex[12], "str1", 4,"str2",4);
	setChar(&ref_regex[13], ';');
	setChar(&ref_regex[14], '\n');
	setChar(&ref_regex[15], '\0');
	setRegex(&regex[0], &regex_test_str[0]);

	return isRegexStrEqual(regex, ref_regex);
}

bool parsingTestWithBackslash() 
{
	rChar regex[50], ref_regex[50];
	char regex_test_str[MAX_TEST_STRING_LEN] = "[a-t].(Aba|saBa) bla\\. \\]\\[\\(\\) (str1|str2);\n";
	setRange(&ref_regex[0], 'a', 't');
	setPoint(&ref_regex[1]);
	setOr(&ref_regex[2], "Aba", 3, "saBa", 4);
	setChar(&ref_regex[3], ' ');
	setChar(&ref_regex[4], 'b');
	setChar(&ref_regex[5], 'l');
	setChar(&ref_regex[6], 'a');
	setChar(&ref_regex[7], '.');
	setChar(&ref_regex[8], ' ');
	setChar(&ref_regex[9], ']');
	setChar(&ref_regex[10], '[');
	setChar(&ref_regex[11], '(');
	setChar(&ref_regex[12], ')');
	setChar(&ref_regex[13], ' ');
	setOr(&ref_regex[14], "str1", 4, "str2", 4);
	setChar(&ref_regex[15], ';');
	setChar(&ref_regex[16], '\n');

	setChar(&ref_regex[17], '\0');
	setRegex(&regex[0], &regex_test_str[0]);

	return isRegexStrEqual(regex, ref_regex);
}

bool regexlenTest()
{
	rChar ref_regex[50];
	setRange(&ref_regex[0], '0', '9');
	setChar(&ref_regex[1], ';');
	setChar(&ref_regex[2], ' ');
	setPoint(&ref_regex[3]);
	setChar(&ref_regex[4], ';');
	setChar(&ref_regex[5], ' ');
	setChar(&ref_regex[6], 'c');
	setChar(&ref_regex[7], 'h');
	setChar(&ref_regex[8], 'a');
	setChar(&ref_regex[9], 'r');
	setChar(&ref_regex[10], ';');
	setChar(&ref_regex[11], ' ');
	setOr(&ref_regex[12], "str1", 4, "str2", 4);
	setChar(&ref_regex[13], ';');
	setChar(&ref_regex[14], '\n');
	setChar(&ref_regex[15], '\0');

	return (29 == regexlen(ref_regex));
}

int main()
{
	assert(parsingTest());
	assert(parsingTestWithBackslash());
	assert(regexlenTest());
}