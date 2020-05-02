#include <stdio.h>
#include "lib/munit/munit.h"
#include "wtl.h"

#ifndef TEST
#define TEST
#endif

static MunitResult ok() { return MUNIT_OK; }


static MunitResult
sample_test(const MunitParameter params[], void* user_data_or_fuxture) {
  munit_assert_int(42, ==, 42);

  return ok();
}


static MunitResult
test_strpos() {
  char* str = "Hello, world";

  munit_assert_int(strpos(str, ','), ==, 5);
  munit_assert_int(strpos(str, 'd'), ==, 11);

  /* Not found in string = -1 */
  munit_assert_int(strpos(str, '#'), ==, -1);

  return ok();
}


static MunitResult
test_strsub() {
  const char* str = "Hello, World";

  munit_assert_string_equal(strsub(str, 0, 5), "Hello");
  munit_assert_string_equal(strsub(str, 7, strlen(str)-1), "World");

  return ok();
}


static MunitResult
test_str_time() {
  struct TestData {
    wtl_time time; char* result;
  };

  struct TestData testData[] = {
    {{ .hour = 8, .minute = 5 }, "08:05"},
    {{ .hour = 10, .minute = 0 }, "10:00"},
    {{ .hour = 23, .minute = 59 }, "23:59"},
  };

  for(int i = 0; i < sizeof(testData) / sizeof(struct TestData); ++i) {
    munit_assert_string_equal(str_time(&testData[i].time), testData[i].result);
  }

  return ok();
}



static MunitTest tests[] = {
  { "/sample-test", sample_test },
  { "/finds char position", test_strpos },
  { "/extracts substring", test_strsub },
  { "/formats time struct", test_str_time },

  /* Mark the end of the array with an entry where the test function is NULL */
  { NULL, NULL }
};

static const MunitSuite suite = { "/wtl-tests", tests };

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
