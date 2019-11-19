#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "line_handler_tests.h"
#include "line_handler.h"

#define TEST_LINE_MAX_LEN 80

void testBasicCases()
{
	const char test_string[][TEST_LINE_MAX_LEN] = {
	   "Every sunday at 4:00 PM,",
	   "we dive into the C relm.",
	   "Mozilla is seeking StaffCryptographyEngineer \
	   to develop featurs for Chrome",
	   "You believe that test doesn't exist unless it is tested",
	   "and that tests don't exist unless they are tested.",
	   "I'm not afraid to copy from my friend.",
	   "I sometimes have bad jokes.",
	   "tthis is an important line!"
	};

	assert(isStringInLine("4:0", test_string[0]));
	assert(isStringInLine(",", test_string[0]));
	assert(isStringInLine("C relm", test_string[1]));
	assert(isStringInLine(".", test_string[1]));
	assert(isStringInLine(" StaffCryptographyEngineer ", test_string[2]));
	assert(!isStringInLine("chrome", test_string[2]));
	assert(isStringInLine("tested", test_string[3]));
	assert(isStringInLine("don't", test_string[4]));
	assert(!isStringInLine("dont", test_string[4]));
	assert(isStringInLine("I'm not afraid", test_string[5]));
	assert(isStringInLine("to copy from my friend", test_string[5]));
	assert(isStringInLine("I sometimes have bad jokes.", test_string[6]));
	assert(isStringInLine("this", test_string[7]));
}