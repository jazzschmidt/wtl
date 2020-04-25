#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>
#include "wtl.h"

int main(int argc, char** argv) {
  char *time;
  char *config;
  float hours;

  int ch;
  while((ch = getopt(argc, argv, "c:h:")) != -1) {
    switch(ch) {
      case 'c':
        config=optarg;
        break;
      case 'h':
        hours = parse_float(optarg);
        break;
      case '?':
      default:
        print_usage();
        exit(1);
    }
  }

  if(hours && config) {
    print_usage();
    exit(1);
  }

  if(argc - optind == 1) {
    time = argv[optind];
  } else {
    print_usage();
    exit(1);
  }

  wtl_time* started = parse_time(time);
  wtl_time* leave = add_time(started, 8, 50);

  printf("You need to work until %s\n", str_time(leave));
  printf("Started: %s\n", str_time(started));
}

void print_usage() {
  printf(
    "Usage: wtl [-c config|-h hours] time\n"
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

float parse_float(const char* string) {
  char *ptr = strchr(string, '.');

  if(ptr == NULL) {
    return (float)parse_int(string);
  }

  int pos = (int)(ptr - string);
  float decimal = (float)parse_int(strsub(string, 0, pos-1));
  float floating = (float)parse_int(strsub(string, pos+1, strlen(string)-1));

  int d=0; // Count decimals of $floating
  for(; floating - pow(10, d) >= 0; d++);

  // Shift float behind the comma, e.g. 123.0 to 0.123
  floating *= pow(10, d * -1);

  return decimal + floating;
}

char* strsub(const char* string, int begin, int end) {
  int length = end - begin + 1;

  char* sub = malloc(length * sizeof(char));
  memcpy(sub, &string[begin], length * sizeof(char));
  sub[length + 1] = '\0';

  return sub;
}
