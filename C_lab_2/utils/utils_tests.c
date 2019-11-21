#include "utils_tests.h"
#include "utils.h"
#include "assert.h"
#include <stdbool.h>

void testIsDigits()
{
	assert(isDigits("123123"));
	assert(isDigits("129387129387"));
	assert(!isDigits("12938 7187"));
	assert(!isDigits("1293a187"));
	assert(!isDigits("1414\n"));
}

void runUtilstests()
{
	testIsDigits();
}

