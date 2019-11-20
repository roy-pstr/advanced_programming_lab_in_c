#include <stddef.h>
#include "utils.h"

bool isStringEmpty(char *str) {
	return (str[0] == '\n' || str[0] == '\0');
}

bool isDigits(char *str)
{
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			return false;
	}
}