
typedef struct {
  char hour; char minute;
} wtl_time;


void print_usage(void);

wtl_time* parse_time(char*);
