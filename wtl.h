
typedef struct {
  int hour; int minute;
} wtl_time;


void print_usage(void);

wtl_time* parse_time(const char*);

wtl_time* add_time(const wtl_time*, int, int);

int parse_int(const char*);

char* strsub(const char*, int, int);
