#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "line_handler_tests.h"
#include "line_handler.h"
#include "params_parser.h"
#include "flags.h"
#include "regex_handler.h"

#define TEST_LINE_MAX_LEN 80
#define TEST_STR_MAX_LEN  80

void runBasicTest()
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
	Params params;
	initializeParams(&params);
	rChar regex_str[TEST_STR_MAX_LEN];
	putRegex(regex_str, "4:0");
	assert(isLineMatch(&params, regex_str, test_string[0]));
	putRegex(regex_str, ",");
	assert(isLineMatch(&params, regex_str, test_string[0]));
	putRegex(regex_str, "C relm");
	assert(isLineMatch(&params, regex_str, test_string[1]));
	putRegex(regex_str, " StaffCryptographyEngineer ");
	assert(isLineMatch(&params, regex_str, test_string[2]));
	putRegex(regex_str, "chrome");
	assert(!isLineMatch(&params, regex_str, test_string[2]));
	putRegex(regex_str, "tested");
	assert(isLineMatch(&params, regex_str, test_string[3]));
	putRegex(regex_str, "don't");
	assert(isLineMatch(&params, regex_str, test_string[4]));
	putRegex(regex_str, "dont");
	assert(!isLineMatch(&params, regex_str, test_string[4]));
	putRegex(regex_str, "I'm not afraid");
	assert(isLineMatch(&params, regex_str, test_string[5]));
	putRegex(regex_str, "to copy from my friend");
	assert(isLineMatch(&params, regex_str, test_string[5]));
	putRegex(regex_str, "I sometimes have bad jokes");
	assert(isLineMatch(&params, regex_str, test_string[6]));
	putRegex(regex_str, "this");
	assert(isLineMatch(&params, regex_str, test_string[7]));
}

void runTestWIthV_Arg()
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
	Params params;
	initializeParams(&params);
	onFlag(&params.v);
	rChar regex_str[TEST_STR_MAX_LEN];
	putRegex(regex_str, "4:0");
	assert(!isLineMatch(&params, regex_str, test_string[0]));
	putRegex(regex_str, ",");
	assert(!isLineMatch(&params, regex_str, test_string[0]));
	putRegex(regex_str, "C relm");
	assert(!isLineMatch(&params, regex_str, test_string[1]));
	putRegex(regex_str, " StaffCryptographyEngineer ");
	assert(!isLineMatch(&params, regex_str, test_string[2]));
	putRegex(regex_str, "chrome");
	assert(isLineMatch(&params, regex_str, test_string[2]));
	putRegex(regex_str, "tested");
	assert(!isLineMatch(&params, regex_str, test_string[3]));
	putRegex(regex_str, "don't");
	assert(!isLineMatch(&params, regex_str, test_string[4]));
	putRegex(regex_str, "dont");
	assert(isLineMatch(&params, regex_str, test_string[4]));
	putRegex(regex_str, "I'm not afraid");
	assert(!isLineMatch(&params, regex_str, test_string[5]));
	putRegex(regex_str, "to copy from my friend");
	assert(!isLineMatch(&params, regex_str, test_string[5]));
	putRegex(regex_str, "I sometimes have bad jokes");
	assert(!isLineMatch(&params, regex_str, test_string[6]));
	putRegex(regex_str, "this");
	assert(!isLineMatch(&params, regex_str, test_string[7]));
}

void runLineHandlerTests()
{
	runBasicTest();
	runTestWIthV_Arg();
}