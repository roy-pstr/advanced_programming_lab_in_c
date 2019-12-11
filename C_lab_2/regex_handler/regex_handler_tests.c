#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "regex_handler.h"
#include "regex_handler_tests.h"
#define MAX_TEST_STRING_LEN 256 

bool parsingTest() {
	rChar regex[50], ref_regex[50];
	char regex_test_str[MAX_TEST_STRING_LEN] = "[0-9]; .; char; (str1|str2);\n";
	putRange(&ref_regex[0], '0', '9');
	putChar(&ref_regex[1], ';');
	putChar(&ref_regex[2], ' ');
	putPoint(&ref_regex[3]);
	putChar(&ref_regex[4], ';');
	putChar(&ref_regex[5], ' ');
	putChar(&ref_regex[6], 'c');
	putChar(&ref_regex[7], 'h');
	putChar(&ref_regex[8], 'a');
	putChar(&ref_regex[9], 'r');
	putChar(&ref_regex[10], ';');
	putChar(&ref_regex[11], ' ');
	putOr(&ref_regex[12], "str1", 4,"str2",4);
	putChar(&ref_regex[13], ';');
	putChar(&ref_regex[14], '\n');
	putChar(&ref_regex[15], '\0');
	putRegex(&regex[0], &regex_test_str[0]);

	return isRegexStrEqual(regex, ref_regex);
}

bool parsingTestWithBackslash() {
	rChar regex[50], ref_regex[50];
	char regex_test_str[MAX_TEST_STRING_LEN] = "[a-t].(Aba|saBa) bla\\. \\]\\[\\(\\) (str1|str2);\n";
	putRange(&ref_regex[0], 'a', 't');
	putPoint(&ref_regex[1]);
	putOr(&ref_regex[2], "Aba", 3, "saBa", 4);
	putChar(&ref_regex[3], ' ');
	putChar(&ref_regex[4], 'b');
	putChar(&ref_regex[5], 'l');
	putChar(&ref_regex[6], 'a');
	putChar(&ref_regex[7], '.');
	putChar(&ref_regex[8], ' ');
	putChar(&ref_regex[9], ']');
	putChar(&ref_regex[10], '[');
	putChar(&ref_regex[11], '(');
	putChar(&ref_regex[12], ')');
	putChar(&ref_regex[13], ' ');
	putOr(&ref_regex[14], "str1", 4, "str2", 4);
	putChar(&ref_regex[15], ';');
	putChar(&ref_regex[16], '\n');

	putChar(&ref_regex[17], '\0');
	putRegex(&regex[0], &regex_test_str[0]);

	printf("[Doron]: printing ref_regex:\n");
	printRegexStr(ref_regex);
	printf("[Doron]: printing regex:\n");
	printRegexStr(regex);

	return isRegexStrEqual(regex, ref_regex);
}

bool regexMatchTest() {
	int len;
	rChar regex;
	char temp_chars[MAX_TEST_STRING_LEN] = "a\n*.[(\\";
	char temp_line[MAX_TEST_STRING_LEN] = "[a,n] (doron|roy)";
	putChar(&regex, 'a');
	if (!isRegexMatch(&regex, &temp_chars[0],&len)) { return false; }

	putChar(&regex, '\n');
	if (!isRegexMatch(&regex, &temp_chars[1], &len)) { return false; }

	putChar(&regex, '*');
	if (!isRegexMatch(&regex, &temp_chars[2], &len)) { return false; }

	putChar(&regex, '.');
	if (!isRegexMatch(&regex, &temp_chars[3], &len)) { return false; }

	putChar(&regex, '[');
	if (!isRegexMatch(&regex, &temp_chars[4], &len)) { return false; }

	putChar(&regex, '(');
	if (!isRegexMatch(&regex, &temp_chars[5], &len)) { return false; }

	putChar(&regex, '\\');
	if (!isRegexMatch(&regex, &temp_chars[6], &len)) { return false; }
	if (len != 1) { return false; }

	putRange(&regex, 'a', 'n');
	if (!isRegexMatch(&regex, &temp_line[0], &len)) { return false; }
	if (len != 5) { return false; }

	putOr(&regex, "doron", 5, "roy", 3);
	if (!isRegexMatch(&regex, &temp_line[6], &len)) { return false; }
	if (len!=11) { return false; }

	putPoint(&regex);
	if (!isRegexMatch(&regex, &temp_chars[0], &len)) { return false; }

	putPoint(&regex);
	if (isRegexMatch(&regex, &temp_chars[7], &len)) { return false; }
	return true;
}

void runRegexHandlerTests() {

	assert(parsingTest());
	assert(parsingTestWithBackslash());
	assert(regexMatchTest());
	/* naive tests */
	printf("naive tests:\n");
	rChar re_char;
	putChar(&re_char, 'r');
	//putRegex(&re_char, "r");
	printrChar(&re_char);
	printf("\n");
	putPoint(&re_char);
	//putRegex(&re_char, ".");
	printrChar(&re_char);
	printf("\n");
	putRange(&re_char, 'a', 'z');
	//putRegex(&re_char, "[a-z]");
	printrChar(&re_char);
	printf("\n");
	putOr(&re_char, "str1", 4, "str2", 4);
	//putRegex(&re_char, "(str1|str2)");
	printrChar(&re_char);

	/* regex string tests */
	printf("\n\nregex string tests:\n");
	putChar(&re_char, '\0');
	printRegexStr(&re_char);

	rChar re_str[4];
	putChar(&re_str[0], 'a');
	putChar(&re_str[1], 'b');
	putChar(&re_str[2], '\n');
	putChar(&re_str[3], '\0');
	printRegexStr(&re_str[0]);

	/* regex parsing tests */
	rChar regex[100];
	char regex_test_str[MAX_TEST_STRING_LEN] = "A regex range: [0-9]; regex point: .; \
regex char: those are just regular char; regex or: (str1|str2);\n";
	putRegex(&regex[0], &regex_test_str[0]);
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
}