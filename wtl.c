#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include "wtl.h"

void cleanup() {
  fflush(NULL);
}

const char TIME_SEPARATOR = ':';

int main(int argc, char** argv) {
  FILE* f = fopen("wtl.cfg", "r");
  assert(read_workday_hours(f) != NULL);
  assert(read_workday_hours(f)->mon->hour == 8);
  assert(read_workday_hours(f)->fri->hour == 6);
  exit(0);

  atexit(cleanup);

  wtl_args* args = parse_args(argc, argv);

  if(!args || (args->span && args->config)) {
    print_usage();
    exit(1);
  }

  wtl_time* started = args->time;

  wtl_time* leave = add_time(started, 8, 50);
  if(args->span) {
    leave = add_time(started, args->span->hour, args->span->minute);
  }

  printf("You need to work until %s\n", str_time(leave));
  printf("Started: %s\n", str_time(started));
}

void print_usage() {
  printf(
    "Usage: wtl [-c config] [time]\n"
    "       wtl -h hours time\n"
  );
}

workday_hours* read_workday_hours(FILE* file) {
  workday_hours* hours = malloc(sizeof(workday_hours));
  wtl_time* no_time = parse_ftime("0");

  *hours = (workday_hours)
    { no_time, no_time, no_time, no_time, no_time, no_time, no_time };

  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  while((linelen = getline(&line, &linecap, file)) != -1) {
    char *key, *value;
    if(read_kv(line, &key, &value)) {
      printf("%s => %s\n", key, value);
    }
  }

  return hours;
}

int read_kv(const char* string, char **key, char **value) {
  int pos = strpos(string, '=');

  if(pos <= 0) {
    return 0;
  }

  *key=strsub(string, 0, pos-1);
  *value=strsub(string, pos+1, strlen(string)-1);

  return 1;
}

wtl_time* parse_ftime(const char* format) {
  if(!valid_time_format(format)) {
    return NULL;
  }

  int hour = 0, minute = 0;

  int pos;
  if((pos = strpos(format, TIME_SEPARATOR)) != -1) {
    hour = atoi(strsub(format, 0, pos-1));
    minute = atoi(strsub(format, pos+1, strlen(format)-1));
  } else {
    hour = atoi(format);
  }

  if(hour < 0 || hour > 23 || minute < 0 || minute > 59) {
    return NULL;
  }

  wtl_time* t = malloc(sizeof(wtl_time));
  *t = (wtl_time){ .hour = hour, .minute = minute };

  return t;
}

int valid_time_format(const char* format) {
  while (*format != '\0') {
    if(!isdigit(*format) && *format != TIME_SEPARATOR) {
      return 0;
    }
    format++;
  }

  return 1;
}

wtl_args* parse_args(int argc, char** argv) {
  wtl_args* args = malloc(sizeof(wtl_args));
  args->config = NULL;
  args->time = NULL;
  args->span = NULL;

  FILE* config;

  int ch;
  while((ch = getopt(argc, argv, "c:h:")) != -1) {
    switch(ch) {
      case 'c':
        config = fopen(optarg, "r");

        if(!config) {
          perror(NULL);
          return NULL;
        }

        args->config = config;
        break;
      case 'h':
        args->span = parse_ftime(optarg);
        break;
      case '?':
      default:
        return NULL;
    }
  }

  if(argc - optind == 1) {
    args->time = parse_time(argv[optind]);
  }

  return args;
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

int strpos(const char* haystack, const char needle) {
  char *ptr;
  if((ptr = strchr(haystack, needle)) != NULL) {
    return (int)(ptr - haystack);
  } else {
    return -1;
  }
}
