
typedef struct {
  int hour; int minute;
} wtl_time;


void print_usage(void);

wtl_time* parse_time(char*);
