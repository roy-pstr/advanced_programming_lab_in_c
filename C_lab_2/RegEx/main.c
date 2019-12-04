#include <stdio.h>
#include "regex_handler/regex_handler.h"

#define MAX_TEST_STRING_LEN 256 

int main() {
	/* naive tests */
	printf("naive tests:\n");
	rChar re_char;
	putChar(&re_char, 'r');
	printrChar(&re_char);
	printf("\n");
	putPoint(&re_char);
	printrChar(&re_char);
	printf("\n");
	putRange(&re_char, 'a', 'z');
	printrChar(&re_char);
	printf("\n");
	putOr(&re_char, "str1", 4, "str2", 4);
	printrChar(&re_char);
	//freerChar(&re_char);

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
	char regex_test_str[MAX_TEST_STRING_LEN] = "A regex range: [0-9]; regex point: .; regex char: those are just regular char; regex or: (str1|str2);\n";
	parseStrToRegex(&regex_test_str[0], &regex[0]);
	printrChar(&regex[15]);
	printf("\n");
	printRegexStr(&regex[0]);

	printf("\n");
	printf("well done.");

	printf("\n\n!!! The console output above should match the reference below !!!\n\n");
	char console_output[MAX_TEST_STRING_LEN] = "naive tests:\nr\n.\n[a-z]\n(str1|str2)\n\nregex string tests:\nab\n[0-9]\nA regex range: [0-9]; regex point: .; regex char: those are just regular char; regex or: (str1|str2);\n\nwell done.";
	printf("%s", console_output);
	return 0;
}