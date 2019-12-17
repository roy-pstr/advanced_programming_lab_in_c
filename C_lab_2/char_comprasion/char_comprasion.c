#include <assert.h>
#include "char_comprasion.h"
#include "flags.h"

//[Doron]: this modul is dead :)
bool regexCharMatch(Params* params, rChar regex_char, char *line_ptr, int *chars_proceed_in_line)
{
	*chars_proceed_in_line = 0;
	switch (regex_char.dataType)
	{
	case CHAR:
		(*chars_proceed_in_line)++;
		return (regex_char.data.c == *line_ptr);
	case POINT:
		break;
	case RANGE:
		break;
	case OR:
		break;
	default:
		assert(false);
	}
}

