#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "line_handler_tests.h"
#include "line_handler.h"

#define TEST_LINE_MAX_LEN 80

void runLineHandlerTests()
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

	assert(isLineMatches("4:0", test_string[0]));
	assert(isLineMatches(",", test_string[0]));
	assert(isLineMatches("C relm", test_string[1]));
	assert(isLineMatches(".", test_string[1]));
	assert(isLineMatches(" StaffCryptographyEngineer ", test_string[2]));
	assert(!isLineMatches("chrome", test_string[2]));
	assert(isLineMatches("tested", test_string[3]));
	assert(isLineMatches("don't", test_string[4]));
	assert(!isLineMatches("dont", test_string[4]));
	assert(isLineMatches("I'm not afraid", test_string[5]));
	assert(isLineMatches("to copy from my friend", test_string[5]));
	assert(isLineMatches("I sometimes have bad jokes.", test_string[6]));
	assert(isLineMatches("this", test_string[7]));
}