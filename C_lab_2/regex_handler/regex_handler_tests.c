#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "regex_handler.h"
#include "regex_handler_tests.h"
#define MAX_TEST_STRING_LEN 256 

/* comprasion regex to regex */
bool isrOrEqual(rChar * left, rChar * right) {
	if (left->data. or .left_len != right->data. or .left_len)
		return false;
	if (left->data. or .right_len != right->data. or .right_len)
		return false;
	return (!strncmp(left->data. or .left, right->data. or .left, left->data. or .left_len)) &&
		(!strncmp(left->data. or .right, right->data. or .right, left->data. or .right_len));
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

bool parsingTest() {
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

bool parsingTestWithBackslash() {
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

	printf("[Doron]: printing ref_regex:\n");
	printRegexStr(ref_regex);
	printf("[Doron]: printing regex:\n");
	printRegexStr(regex);

	return isRegexStrEqual(regex, ref_regex);
}

bool regexlenTest() {
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

	return (29==regexlen(ref_regex));
}

void runRegexHandlerTests() {

	assert(parsingTest());
	assert(parsingTestWithBackslash());
	/*assert(regexMatchTest());*/
	assert(regexlenTest());
	/* naive tests */
	printf("naive tests:\n");
	rChar re_char;
	setChar(&re_char, 'r');
	//putRegex(&re_char, "r");
	printrChar(&re_char);
	printf("\n");
	setPoint(&re_char);
	//putRegex(&re_char, ".");
	printrChar(&re_char);
	printf("\n");
	setRange(&re_char, 'a', 'z');
	//putRegex(&re_char, "[a-z]");
	printrChar(&re_char);
	printf("\n");
	setOr(&re_char, "str1", 4, "str2", 4);
	//putRegex(&re_char, "(str1|str2)");
	printrChar(&re_char);

	/* regex string tests */
	printf("\n\nregex string tests:\n");
	setChar(&re_char, '\0');
	printRegexStr(&re_char);

	rChar re_str[4];
	setChar(&re_str[0], 'a');
	setChar(&re_str[1], 'b');
	setChar(&re_str[2], '\n');
	setChar(&re_str[3], '\0');
	printRegexStr(&re_str[0]);

	/* regex parsing tests */
	rChar regex[100];
	char regex_test_str[MAX_TEST_STRING_LEN] = "A regex range: [0-9]; regex point: .; \
regex char: those are just regular char; regex or: (str1|str2);\n";
	setRegex(&regex[0], &regex_test_str[0]);
	printrChar(&regex[15]);
	printf("\n");
	printRegexStr(&regex[0]);

	printf("\n");
	printf("well done.");

	printf("\n\n!!! The console output above should match the reference below !!!\n\n");
	char console_output[MAX_TEST_STRING_LEN] = "naive tests:\nr\n.\n[a-z]\n(str1|str2)\n\n\
regex string tests:\nab\n[0-9]\nA regex range: [0-9]; regex point: .; regex char: those are\
 just regular char; regex or: (str1|str2);\n\nwell done.";
	printf("%s", console_output);
	printf("\n");
	printf("\n");
}