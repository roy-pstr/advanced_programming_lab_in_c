#include <stddef.h>
#include "utils.h"

bool isStringEmpty(char *str) {
	return (str[0] == '\n' || str[0] == '\0');
}