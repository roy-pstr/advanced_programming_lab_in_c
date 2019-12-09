#include <assert.h>
#include "char_comprasion.h"
#include "flags.h"

void upperCase(char *p_char)
{
	if (*p_char >= 'a' && *p_char <= 'z') {
		*p_char -= ' ';
	}
}

bool charsAreEqual(Params *params, char line_char, char substr_char)
{
	if (isFlagOn(&params->i))
	{
		upperCase(&line_char);
		upperCase(&substr_char);
	}

	return (line_char == substr_char);

	/* To Be Continued: add regex support */
}

bool regexCharMatch(rChar regex_string, char *mid_line_ptr, int *chars_proceed_in_line)
{
	//recursive
	/* supporting only char case */
	*chars_proceed_in_line = 0;
	switch (regex_string.dataType)
	{
	case CHAR:
		(*chars_proceed_in_line)++;
		return (regex_string.data.c == *mid_line_ptr);
	default:
		assert(false);
	}
}
