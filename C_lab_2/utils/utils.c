#include <stddef.h>
#include "utils.h"

 void upperCaseChar(char *p_char)
{
	if (*p_char >= 'a' && *p_char <= 'z') {
		*p_char -= ' ';
	}
}

 void upperCaseString(char *str)
 {
	 while (*str != '\0'){
		 upperCaseChar(str);
		 str++;
	 }
 }


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

int strlen_without_newline(char *str) {
	int len = strlen(str);
	return (str[len-1] == '\n') ? (len - 1) : len;
}