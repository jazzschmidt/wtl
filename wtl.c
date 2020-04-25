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

  wtl_time* started = parse_time(argv[1]);
  wtl_time* leave = add_time(started, 8, 50);

  printf("You need to work until %s\n", str_time(leave));
  printf("Started: %s\n", str_time(started));
}

void print_usage() {
  printf(
    "Usage: wtl [-c config] [time]\n"
    "       wtl time timespan\n"
  );
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

  free(str_hour);
  free(str_minute);

  return t;
}

wtl_time* add_time(const wtl_time* time, int hours, int minutes) {
  wtl_time* t = malloc(sizeof(wtl_time));
  *t = (wtl_time) {
    .hour = time->hour + hours,
    .minute = time->minute
  };

  t->minute += minutes;
  if(t->minute >= 60) {
    t->minute %= 60;
    t->hour++;
  }

  return t;
}

char* str_time(const wtl_time* time) {
  char* string = malloc(5 * sizeof(char));
  sprintf(string, "%02d:%02d", time->hour, time->minute);

  return string;
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
