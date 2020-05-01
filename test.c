#include <stdio.h>
#include "test.h"

static MunitTest tests[] = {
  {
    "/sample-test", /* name */
    sample_test, /* test */
    NULL, /* setup */
    NULL, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  /* Mark the end of the array with an entry where the test
   * function is NULL */
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/wtl-tests", /* name */
  tests, /* tests */
  NULL, /* suites */
  1, /* iterations */
  MUNIT_SUITE_OPTION_NONE /* options */
};

MunitResult sample_test(const MunitParameter params[], void* user_data_or_fuxture) {
  munit_assert_int(42, ==, 42);

  return MUNIT_OK;
}

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
