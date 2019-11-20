#include <stdbool.h>
#include "line_handler.h"

bool isStringInLine(const char *str, const char *line)
{
	const char *str_iterator = str;

	while (*line != '\0') {
		const char *line_iterator = line;
		while (*line_iterator == *str_iterator) {
			str_iterator++;
			line_iterator++;
			if (*str_iterator == '\0') {
				return true;
			}
		}
		str_iterator = str;
		line++;
	}

	return false;
}

