#include <stdio.h>
#include <stdlib.h>
#include "wtl.h"

int main(const int argc, const char** argv) {
  if (argc != 2) {
    print_usage();
    exit(1);
  }

  wtl_time* time = parse_time("");
  printf("%d:%d\n", time->hour, time->minute);
}

void print_usage() {
  printf("Usage: wtl\n");
}

wtl_time* parse_time(char* string) {
  return &(wtl_time){16,20};
}
