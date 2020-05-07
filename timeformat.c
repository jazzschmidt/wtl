#import <stdlib.h>
#import <stdio.h>
#import <ctype.h>
#import <time.h>
#import <string.h>
#import "timeformat.h"

static const char TIME_SEPARATOR = ':';

int isTimeFormat(const char *format) {
  if(strlen(format) > 5) return 0;

  int unit_len = 0;

  while (*format != '\0') {
    if(!isdigit(*format) && *format != TIME_SEPARATOR) {
      return 0;
    } else if (*format == TIME_SEPARATOR) {
      unit_len = -1; /* next char is next unit number */
    }

    if(++unit_len > 2) { return 0; }

    format++;
  }

  return 1;
}

time_t timeFromFormat(const char *format) {
  int hour, minute;
  int separator_pos;

  if((separator_pos = strpos(format, TIME_SEPARATOR)) != -1) {
    char *hour_str = strndup(format, separator_pos);
    char *minute_str = strdup(format + separator_pos + 1);

    hour = (int)strtol(hour_str, NULL, 10);
    minute = (int)strtol(minute_str, NULL, 10);
  } else {
    hour = (int)strtol(format, NULL, 10);
    minute = 0;
  }

  time_t today = time(NULL);
  struct tm *today_local = localtime(&today);
  today_local->tm_hour = hour;
  today_local->tm_min = minute;

  return mktime(today_local);
}


char *formatTime(time_t timestamp) {
  return 0;
}
