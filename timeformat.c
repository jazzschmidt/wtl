#import <stdlib.h>
#import <stdio.h>
#import <ctype.h>
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

int timeFromFormat(const char *format) {
  return 0;
}


char *formatTime(long timestamp) {
  return 0;
}
