#include <stddef.h>
#include "utils.h"

bool isStringEmpty(const char *str) {
	return (str[0] == '\0');
}
bool isStringNewLine(const char *str) {
	return (str[0] == '\n');
}
bool isDigits(const char *str)
{
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			return false;
		str++;
	}
	return true;
}