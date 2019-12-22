#include "utils_tests.h"
#include "utils.h"
#include "assert.h"
#include <string.h>
#include <stdbool.h>

void testIsDigits()
{
	assert(isDigits("123123"));
	assert(isDigits("129387129387"));
	assert(!isDigits("12938 7187"));
	assert(!isDigits("1293a187"));
	assert(!isDigits("1414\n"));
}

void testStrLenWithoutNetLine()
{
	char str1[] = "bla bla\n";
	assert(strlen(str1) - 1 == strlenWithoutNewline(str1));
	char str2[] = "bla bla bli";
	assert(strlen(str2)  == strlenWithoutNewline(str2));
}

void testUpperCaseString()
{
	char str1[] = "blA bLa\n";
	upperCaseString(str1);
	assert(STRINGS_ARE_EQUAL(str1, "BLA BLA \n"));
	char str2[] = "bla bla bli";
	upperCaseString(str2);
	assert(STRINGS_ARE_EQUAL(str2, "BLA BLA BLI"));
}

void main()
{
	testIsDigits();
	testStrLenWithoutNetLine();
	testUpperCaseString();
}

