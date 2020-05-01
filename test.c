#include <stdio.h>
#include "lib/munit/munit.h"

int main(int argc, const char** argv) {
  printf("Started tests!\n");
  munit_assert_int(42, ==, 42);

  return 0;
}
