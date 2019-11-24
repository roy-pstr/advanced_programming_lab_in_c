#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "line_handler_tests.h"
#include "line_handler.h"
#include "params_parser.h"
#include "flags.h"

#define TEST_LINE_MAX_LEN 80


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

	params.sub_str = "4:0";
	assert(isLineMatch(&params, test_string[0]));
	params.sub_str = ",";
	assert(isLineMatch(&params, test_string[0]));
	params.sub_str = "C relm";
	assert(isLineMatch(&params, test_string[1]));
	params.sub_str = ".";
	assert(isLineMatch(&params, test_string[1]));
	params.sub_str = " StaffCryptographyEngineer ";
	assert(isLineMatch(&params, test_string[2]));
	params.sub_str = "chrome";
	assert(!isLineMatch(&params, test_string[2]));
	params.sub_str = "tested";
	assert(isLineMatch(&params, test_string[3]));
	params.sub_str = "don't";
	assert(isLineMatch(&params, test_string[4]));
	params.sub_str = "dont";
	assert(!isLineMatch(&params, test_string[4]));
	params.sub_str = "I'm not afraid";
	assert(isLineMatch(&params, test_string[5]));
	params.sub_str = "to copy from my friend";
	assert(isLineMatch(&params, test_string[5]));
	params.sub_str = "I sometimes have bad jokes.";
	assert(isLineMatch(&params, test_string[6]));
	params.sub_str = "this";
	assert(isLineMatch(&params, test_string[7]));
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
	params.sub_str = "4:0";
	assert(!isLineMatch(&params, test_string[0]));
	params.sub_str = ",";
	assert(!isLineMatch(&params, test_string[0]));
	params.sub_str = "C relm";
	assert(!isLineMatch(&params, test_string[1]));
	params.sub_str = ".";
	assert(!isLineMatch(&params, test_string[1]));
	params.sub_str = " StaffCryptographyEngineer ";
	assert(!isLineMatch(&params, test_string[2]));
	params.sub_str = "chrome";
	assert(isLineMatch(&params, test_string[2]));
	params.sub_str = "tested";
	assert(!isLineMatch(&params, test_string[3]));
	params.sub_str = "don't";
	assert(!isLineMatch(&params, test_string[4]));
	params.sub_str = "dont";
	assert(isLineMatch(&params, test_string[4]));
	params.sub_str = "I'm not afraid";
	assert(!isLineMatch(&params, test_string[5]));
	params.sub_str = "to copy from my friend";
	assert(!isLineMatch(&params, test_string[5]));
	params.sub_str = "I sometimes have bad jokes.";
	assert(!isLineMatch(&params, test_string[6]));
	params.sub_str = "this";
	assert(!isLineMatch(&params, test_string[7]));
}

void runLineHandlerTests()
{
	runBasicTest();
	runTestWIthV_Arg();
}