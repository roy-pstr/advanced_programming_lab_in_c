#include <assert.h>
#include "params_parser_tests.h"
#include "params_parser.h"
#include "utils.h"
#include "flags.h"

#define TEST_PARAMS_MAX_ARG_LEN 20

bool areFlagsEquals(Flag flag1, Flag flag2)
{
	return ((flag1.counter == flag2.counter) &&
			(flag1.is_on == flag2.is_on) &&
			(flag1.argument == flag2.argument));
}

bool areParamsEqual(Params *params1, Params *params2)
{
	bool are_file_names_equal;
	if (paramsHasFile(params1) && paramsHasFile(params2)) {
		are_file_names_equal = STRINGS_ARE_EQUAL(params1->filename, params2->filename);
	}
	else if (!paramsHasFile(params1) && !paramsHasFile(params2)) {
		are_file_names_equal = true;
	}
	else
		are_file_names_equal = false;

	return (
		(are_file_names_equal) &&
		(areFlagsEquals(params1->A, params2->A)) &&
		(areFlagsEquals(params1->b, params2->b)) &&
		(areFlagsEquals(params1->c, params2->c)) &&
		(areFlagsEquals(params1->i, params2->i)) &&
		(areFlagsEquals(params1->n, params2->n)) &&
		(areFlagsEquals(params1->v, params2->v)) &&
		(areFlagsEquals(params1->x, params2->x)) &&
		(areFlagsEquals(params1->E, params2->E)) &&
		(STRINGS_ARE_EQUAL(params1->sub_str, params2->sub_str))
		);
}

void printParams(Params *params) //debugging funciton
{
	printf("@@@ Printing Params@@@\n");
	printf("sub_str = %s\n", params->sub_str);
	if (paramsHasFile(params))
		printf("filename = %s\n", params->filename);
	else
		printf("params has no file\n");
	printf("flags on:\n");
	if (isFlagOn(&params->A)) {
		printf("-A, %d\n", params->A.argument);
	}
	if (isFlagOn(&params->b)) {
		printf("-b, %d\n", params->b.counter);
	}
	if (isFlagOn(&params->c)) {
		printf("-c, %d\n", params->c.counter);
	}
	if (isFlagOn(&params->i)) {
		printf("-i, %d\n", params->i.counter);
	}
	if (isFlagOn(&params->n)) {
		printf("-n, %d\n", params->n.counter);
	}
	if (isFlagOn(&params->v)) {
		printf("-v, %d\n", params->v.counter);
	}
	if (isFlagOn(&params->x)) {
		printf("-x, %d\n", params->x.counter);
	}
	if (isFlagOn(&params->E)) {
		printf("-E, %d\n", params->E.counter);
	}
	printf("@@ Done Printing Params @@ \n");
}

void ParamsParserTest1()
{
	char *argv[TEST_PARAMS_MAX_ARG_LEN] = { "my_grep","-n","-i","search_me","2013.html" };
	int argc = 5;
	Params expected_params;
	initializeParams(&expected_params);
	onFlag(&expected_params.n);
	onFlag(&expected_params.i);
	expected_params.filename = argv[4];
	expected_params.sub_str = argv[3];

	Params params;
	parseParams(argc, argv, &params);

	printParams(&params);
	printParams(&expected_params);

	assert(areParamsEqual(&params, &expected_params));
}

void ParamsParserTest2()
{
	char *argv[TEST_PARAMS_MAX_ARG_LEN] = { "my_grep","search_me","-A","3", "-x","file.txt" };
	int argc = 6;
	Params expected_params;
	initializeParams(&expected_params);
	onFlag(&expected_params.A);
	setArgument(&expected_params.A, 3);
	setCounter(&expected_params.A, A_FLAG_COUNTER_INIT);
	onFlag(&expected_params.x);
	expected_params.filename = argv[5];
	expected_params.sub_str = argv[1];

	Params params;
	parseParams(argc, argv, &params);
	printParams(&params);
	printParams(&expected_params);
	assert(areParamsEqual(&params, &expected_params));
}

void ParamsParserTest3()
{
	char *argv[TEST_PARAMS_MAX_ARG_LEN] = { "my_grep","-c","-A","32","search_me" };
	int argc = 5;
	Params expected_params;
	initializeParams(&expected_params);
	onFlag(&expected_params.A);
	setArgument(&expected_params.A, 32);
	setCounter(&expected_params.A, A_FLAG_COUNTER_INIT);
	onFlag(&expected_params.c);
	expected_params.sub_str = argv[4];

	Params params;
	parseParams(argc, argv, &params);
	printParams(&params);
	printParams(&expected_params);
	assert(areParamsEqual(&params, &expected_params));
}

void testParamsParser()
{
	ParamsParserTest1();
	ParamsParserTest2();
	ParamsParserTest3();
}

void runParamsParserTests()
{
	testParamsParser();
}






