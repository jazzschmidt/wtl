#include <stdio.h>
#include "lib/munit/munit.h"
#include "wtl.h"

#ifndef TEST
#define TEST
#endif

static MunitResult ok() { return MUNIT_OK; }
static MunitResult skip() { return MUNIT_SKIP; }
static MunitResult fail() { return MUNIT_FAIL; }
static MunitResult error() { return MUNIT_ERROR; }


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
  return skip();

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


static MunitResult
test_add_time() {
  struct TestData {
    wtl_time time; int hours, minutes, expectedHour, expectedMinute;
  };

  struct TestData testData[] = {
    {{ .hour = 8, .minute = 5 }, 2, 10, 10, 15},
    {{ .hour = 10, .minute = 0 }, 10, 70, 21, 10},
    {{ .hour = 23, .minute = 59 }, 0, 1, 0, 0},
  };

  for(int i = 0; i < sizeof(testData) / sizeof(struct TestData); ++i) {
    struct TestData data = testData[i];

    wtl_time *result = add_time(&data.time, data.hours, data.minutes);

    munit_assert_int(result->hour, ==, data.expectedHour);
    munit_assert_int(result->minute, ==, data.expectedMinute);
  }

  return ok();
}


static MunitResult
test_valid_time_format() {
  int valid = 1; int invalid = 0;

  struct TestData {
    char *format; int expected;
  };

  struct TestData testData[] = {
    { "8:15", valid },
    { "18:5", valid },
    { "8:1", valid },
    { "18:15", valid },
    { "8", valid },
    { "8:", valid },
    { "-7", invalid },
    { "100.", invalid },
  };

  for(int i = 0; i < sizeof(testData) / sizeof(struct TestData); ++i) {
    int result = valid_time_format(testData[i].format);
    munit_assert_int(result, ==, testData[i].expected);
  }

  return ok();
}


static MunitResult
test_time_to_string() {
  struct TestData {
    wtl_time time; char *expected;
  };

  struct TestData testData[] = {
    {{ .hour = 8, .minute = 5 }, "08:05"},
    {{ .hour = 10, .minute = 0 }, "10:00"},
    {{ .hour = 23, .minute = 59 }, "23:59"}
  };

  for(int i = 0; i < sizeof(testData) / sizeof(struct TestData); ++i) {
    char *result = time_to_string(&testData[i].time);
    char *expected = testData[i].expected;

    munit_assert_string_equal(result, expected);
  }

  return ok();
}


static MunitTest tests[] = {
  { "/sample-test", sample_test },
  { "/finds char position", test_strpos },
  { "/extracts substring", test_strsub },
  { "/formats time struct", test_str_time },
  { "/additions times", test_add_time },
  { "/validates time formats", test_valid_time_format },
  { "/coverts time to string", test_time_to_string },

  /* Mark the end of the array with an entry where the test function is NULL */
  { NULL, NULL }
};

static const MunitSuite suite = { "/wtl-tests", tests };

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
