/* Time and Duration Functions
 * ---------------------------
 * Transforms time format strings, such as "08:00", into time_t values and vice
 * versa.
 */
#import <stdlib.h>
#import <stdio.h>
#import <ctype.h>
#import <time.h>
#import <string.h>
#import "timeformat.h"

/* --------------------- Global variables --------------------- */


/* Splits hour and minute in the time format */
static const char TIME_SEPARATOR = ':';


/* --------------------- Prototypes --------------------- */


/* Extracts hour and minute of the time string */
static void parseTimeFormat(const char *format, int *hour, int *minute);


/* --------------------- Implementation --------------------- */


/* Function: isTimeFormat
 * ----------------------
 * Checks whether `format` is a time or duration format.
 * Returns 1 if format matches, 0 otherwise.
 */
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


/* Function: timeFromFormat
 * ------------------------
 * Returns todays timestamp at the time of `format`.
 */
time_t timeFromFormat(const char *format) {
  int hour, minute;
  parseTimeFormat(format, &hour, &minute);

  time_t today = time(NULL);
  struct tm *today_local = localtime(&today);
  today_local->tm_hour = hour;
  today_local->tm_min = minute;

  return mktime(today_local);
}


/* Function: durationFromFormat
 * ----------------------------
 * Returns the time of `format` as a duration in seconds.
 */
time_t durationFromFormat(const char *format) {
  int hour, minute;
  parseTimeFormat(format, &hour, &minute);

  return 60 * minute + 60 * 60 * hour;
}


/* Function: formatTime
 * --------------------
 * Returns the textual representation of the given time.
 */
char *formatTime(time_t timestamp) {
  struct tm *local_time = localtime(&timestamp);
  char *format = NULL;

  asprintf(&format, "%02d:%02d", local_time->tm_hour, local_time->tm_min);

  return format;
}


/* --------------------- Internal routines --------------------- */


/* Function: parseTimeFormat
 * -------------------------
 * Extracts hour and minute of the time string.
 */
static void parseTimeFormat(const char *format, int *hour, int *minute) {
  int separator_pos;

  if((separator_pos = strpos(format, TIME_SEPARATOR)) != -1) {
    char *hour_str = strndup(format, separator_pos);
    char *minute_str = strdup(format + separator_pos + 1);

    *hour = (int)strtol(hour_str, NULL, 10);
    *minute = (int)strtol(minute_str, NULL, 10);
  } else {
    *hour = (int)strtol(format, NULL, 10);
    *minute = 0;
  }
}
