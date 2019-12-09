#include <assert.h>
#include "char_comprasion.h"
#include "flags.h"

bool regexCharMatch(Params* params, rChar regex_char, char *mid_line_ptr, int *chars_proceed_in_line)
{
	//TBD: recursive
	/* supporting only char case */
	*chars_proceed_in_line = 0;
	switch (regex_char.dataType)
	{
	case CHAR:
		(*chars_proceed_in_line)++;
		return (regex_char.data.c == *mid_line_ptr);
	default:
		assert(false);
	}
}
