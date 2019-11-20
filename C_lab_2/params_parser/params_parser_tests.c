#include "params_parser_tests.h"

bool isFlagsEquals(Flag flag1, Flag flag2)
{
	return ((flag1.counter == flag2.counter) && (flag1.is_on != flag2.is_on));
}

bool isParamsEqual(Params *params1, Params *params2)
{

	return (
		(STRINGS_ARE_EQUAL(params1->sub_str,  params2->sub_str))  &&
		(STRINGS_ARE_EQUAL(params1->filename, params1->filename)) &&
		(isFlagsEquals(params1->A, params2->A)) &&
		(isFlagsEquals(params1->b, params2->b)) &&
		(isFlagsEquals(params1->c, params2->c)) &&
		(isFlagsEquals(params1->i, params2->i)) &&
		(isFlagsEquals(params1->n, params2->n)) &&
		(isFlagsEquals(params1->v, params2->v)) &&
		(isFlagsEquals(params1->x, params2->x)) &&
		(isFlagsEquals(params1->E, params2->E))
		)
}

