#include "flags.h"
#include "line_handler.h"
#include "params_parser.h"
#include "regex.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define TEST_LINE_MAX_LEN 80
#define TEST_STR_MAX_LEN 80

void runBasicTest(const char test_string[][TEST_LINE_MAX_LEN])
{
  Params params;
  initializeParams(&params);
  rChar regex_str[TEST_STR_MAX_LEN];
  setRegex(regex_str, "4:0");
  assert(isLineMatch(&params, regex_str, test_string[0]));
  setRegex(regex_str, ",");
  assert(isLineMatch(&params, regex_str, test_string[0]));
  setRegex(regex_str, "C relm");
  assert(isLineMatch(&params, regex_str, test_string[1]));
  setRegex(regex_str, " StaffCryptographyEngineer ");
  assert(isLineMatch(&params, regex_str, test_string[2]));
  setRegex(regex_str, "chrome");
  assert(!isLineMatch(&params, regex_str, test_string[2]));
  setRegex(regex_str, "tested");
  assert(isLineMatch(&params, regex_str, test_string[3]));
  setRegex(regex_str, "don't");
  assert(isLineMatch(&params, regex_str, test_string[4]));
  setRegex(regex_str, "dont");
  assert(!isLineMatch(&params, regex_str, test_string[4]));
  setRegex(regex_str, "I'm not afraid");
  assert(isLineMatch(&params, regex_str, test_string[5]));
  setRegex(regex_str, "to copy from my friend");
  assert(isLineMatch(&params, regex_str, test_string[5]));
  setRegex(regex_str, "I sometimes have bad jokes");
  assert(isLineMatch(&params, regex_str, test_string[6]));
  setRegex(regex_str, "this");
  assert(isLineMatch(&params, regex_str, test_string[7]));
}

void runTestWIthV_Arg(const char test_string[][TEST_LINE_MAX_LEN])
{
  Params params;
  initializeParams(&params);
  onFlag(&params.v);
  rChar regex_str[TEST_STR_MAX_LEN];
  setRegex(regex_str, "4:0");
  assert(!isLineMatch(&params, regex_str, test_string[0]));
  setRegex(regex_str, ",");
  assert(!isLineMatch(&params, regex_str, test_string[0]));
  setRegex(regex_str, "C relm");
  assert(!isLineMatch(&params, regex_str, test_string[1]));
  setRegex(regex_str, " StaffCryptographyEngineer ");
  assert(!isLineMatch(&params, regex_str, test_string[2]));
  setRegex(regex_str, "chrome");
  assert(isLineMatch(&params, regex_str, test_string[2]));
  setRegex(regex_str, "tested");
  assert(!isLineMatch(&params, regex_str, test_string[3]));
  setRegex(regex_str, "don't");
  assert(!isLineMatch(&params, regex_str, test_string[4]));
  setRegex(regex_str, "dont");
  assert(isLineMatch(&params, regex_str, test_string[4]));
  setRegex(regex_str, "I'm not afraid");
  assert(!isLineMatch(&params, regex_str, test_string[5]));
  setRegex(regex_str, "to copy from my friend");
  assert(!isLineMatch(&params, regex_str, test_string[5]));
  setRegex(regex_str, "I sometimes have bad jokes");
  assert(!isLineMatch(&params, regex_str, test_string[6]));
  setRegex(regex_str, "this");
  assert(!isLineMatch(&params, regex_str, test_string[7]));
}

void runTestWithEscapes(const char test_string[][TEST_LINE_MAX_LEN])
{
  Params params;
  initializeParams(&params);
  onFlag(&params.E);
  rChar regex_str[TEST_STR_MAX_LEN];
  setRegex(regex_str, "\\[4:00\\]");
  assert(isLineMatch(&params, regex_str, test_string[0]));
  setRegex(regex_str, "\\[");
  assert(isLineMatch(&params, regex_str, test_string[0]));
  setRegex(regex_str, "\\[3");
  assert(!isLineMatch(&params, regex_str, test_string[0]));
  setRegex(regex_str, "C relm\\.");
  assert(isLineMatch(&params, regex_str, test_string[1]));
  setRegex(regex_str, "Chrome");
  assert(isLineMatch(&params, regex_str, test_string[2]));
  setRegex(regex_str, "\\.");
  assert(!isLineMatch(&params, regex_str, test_string[3]));
  setRegex(regex_str, "I'm not afraid");
  assert(isLineMatch(&params, regex_str, test_string[5]));
  setRegex(regex_str, "I sometimes have bad jokes\\.\\.\\.");
  assert(isLineMatch(&params, regex_str, test_string[6]));
  setRegex(regex_str, "I sometimes have bad jokes\\.\\.\\.\\.");
  assert(!isLineMatch(&params, regex_str, test_string[6]));
  setRegex(regex_str, "\\(!\\)");
  assert(isLineMatch(&params, regex_str, test_string[7]));
}

void runTestXFlag(const char test_string[][TEST_LINE_MAX_LEN])
{
  Params params;
  initializeParams(&params);
  onFlag(&params.x);
  rChar regex_str[TEST_STR_MAX_LEN];

  setRegex(regex_str, "we dive into the C relm.");
  assert(isLineMatch(&params, regex_str, test_string[1]));

  setRegex(regex_str, "we dive into the C relm. ");
  assert(!isLineMatch(&params, regex_str, test_string[1]));

  setRegex(regex_str, " we dive into the C relm.");
  assert(!isLineMatch(&params, regex_str, test_string[1]));
}

int main()
{
  const char test_string[][TEST_LINE_MAX_LEN] = {"Every sunday at [4:00] PM,",
                                                 "we dive into the C relm.",
                                                 "Mozilla is seeking StaffCryptographyEngineer \
	to develop featurs for Chrome",
                                                 "You believe that test doesn't exist unless it is tested",
                                                 "and that tests don't exist unless they are tested.",
                                                 "I'm not afraid to copy from my friend.",
                                                 "I sometimes have bad jokes...",
                                                 "tthis is an important line(!)"};

  runBasicTest(test_string);
  runTestWIthV_Arg(test_string);
  runTestWithEscapes(test_string);
  runTestXFlag(test_string);
  return 0;
}