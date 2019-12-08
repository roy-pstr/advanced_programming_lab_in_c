#include "char_comprasion.h"
#include "flags.h"
#include "regex_handler.h"

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
