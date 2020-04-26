
typedef struct {
  int hour; int minute;
} wtl_time;

typedef struct {
  wtl_time* time;
  wtl_time* span;
  FILE *config;
} wtl_args;

typedef struct {
  wtl_time *sun, *mon, *tue, *wed, *thu, *fri, *sat;
} workday_hours;

void print_usage(void);

workday_hours* read_workday_hours(FILE*);

wtl_time* hours_for(workday_hours*, time_t*);

int read_kv(const char*, char**, char**);

wtl_args* parse_args(int argc, char** argv);

wtl_time* parse_ftime(const char*);

wtl_time* parse_time(const char*);

wtl_time* add_time(const wtl_time*, int, int);

char* str_time(const wtl_time*);

int parse_int(const char*);

float parse_float(const char*);

char* strsub(const char*, int, int);

int valid_time_format(const char*);

int strpos(const char*, const char);
