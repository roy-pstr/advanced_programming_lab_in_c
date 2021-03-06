#include "params_parser.h"
#include "utils.h"
#include <assert.h>
#include <stdlib.h>

bool paramsHasFile(Params *params) { return (params->filename != NULL); }

void initializeParams(Params *params)
{
  params->sub_str = NULL;
  params->filename = NULL;
  initializeFlag(&params->A);
  initializeFlag(&params->b);
  initializeFlag(&params->c);
  initializeFlag(&params->i);
  initializeFlag(&params->n);
  initializeFlag(&params->v);
  initializeFlag(&params->x);
  initializeFlag(&params->E);
}

void parseParams(int argc, char **argv, Params *params)
{
  initializeParams(params);
  bool found_substr = false;
  for (int i = 1; i < argc; i++) {
    if (STRINGS_ARE_EQUAL(argv[i], "-A")) {
      onFlag(&params->A);
      i++;
      assert(isDigits(argv[i]));
      setArgument(&params->A, atoi(argv[i]));
      setCounter(&params->A, A_FLAG_COUNTER_INIT);
    } else if (STRINGS_ARE_EQUAL(argv[i], "-b")) {
      onFlag(&params->b);
    } else if (STRINGS_ARE_EQUAL(argv[i], "-c")) {
      onFlag(&params->c);
    } else if (STRINGS_ARE_EQUAL(argv[i], "-i")) {
      onFlag(&params->i);
    } else if (STRINGS_ARE_EQUAL(argv[i], "-n")) {
      onFlag(&params->n);
    } else if (STRINGS_ARE_EQUAL(argv[i], "-v")) {
      onFlag(&params->v);
    } else if (STRINGS_ARE_EQUAL(argv[i], "-x")) {
      onFlag(&params->x);
    } else if (STRINGS_ARE_EQUAL(argv[i], "-E")) {
      onFlag(&params->E);
    } else if (!found_substr) {
      params->sub_str = argv[i];
      found_substr = true;
    } else {
      assert(i == argc - 1);  // We assume filename is last arg
      params->filename = argv[i];
    }
  }
}
