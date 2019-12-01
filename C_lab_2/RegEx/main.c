#include "regex_handler/regex_handler.h"

int main() {
	rChar re_char;
	putChar(&re_char, 'r');
	printrChar(&re_char);
	putPoint(&re_char);
	printrChar(&re_char);
	putRange(&re_char, 'a', 'z');
	printrChar(&re_char);
	putOr(&re_char, "str1", 5, "str2", 5);
	printrChar(&re_char);
	freerChar(&re_char);
	return 0;
}