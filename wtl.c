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

  wtl_time* time = parse_time(argv[1]);
  printf("%02d:%02d\n", time->hour, time->minute);
}

void print_usage() {
  printf("Usage: wtl\n");
}

wtl_time* parse_time(const char* string) {
  char *str_hour, *str_minute;

  str_hour = strsub(string, 0, 1);
  str_minute = strsub(string, 3, 4);

  wtl_time* t = malloc(sizeof(wtl_time));
  *t = (wtl_time) {
    .hour = parse_int(str_hour),
    .minute = parse_int(str_minute)
  };

  return t;
}

int parse_int(const char* string) {
  int number = 0;
  for(int i = strlen(string), n = 1; i > 0; i--, n*=10) {
    number += (string[i-1] - '0') * n;
  }

  return number;
}

char* strsub(const char* string, int begin, int end) {
  int length = end - begin + 1;

  char* sub = malloc(length * sizeof(char));
  memcpy(sub, &string[begin], length * sizeof(char));
  sub[length + 1] = '\0';

  return sub;
}
