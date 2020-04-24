#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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

int parse_int(char* string) {
  int number = 0;
  for(int i = strlen(string), n = 1; i > 0; i--, n*=10) {
    number += (string[i-1] - '0') * n;
  }

  return number;
}
