
typedef struct {
  int hour; int minute;
} wtl_time;

typedef struct {
  wtl_time* time;
  wtl_time* span;
  char *config_file;
} wtl_args;

typedef struct {
  wtl_time *sun, *mon, *tue, *wed, *thu, *fri, *sat;
} workday_hours;

typedef struct {
  workday_hours* hours;
  wtl_time* start_time;
} wtl_config;

wtl_config* read_config(char*);

void print_usage(void);

FILE* default_cfg(void);

char* default_cfg_file(void);

workday_hours* read_workday_hours(FILE*);

wtl_time* hours_for(workday_hours*, time_t*);

int read_kv(const char*, char**, char**);

wtl_args* parse_args(int argc, char** argv);

wtl_time* parse_ftime(const char*);

wtl_time* parse_time(const char*);

char* time_to_string(wtl_time*);

wtl_time* add_time(const wtl_time*, int, int);

char* str_time(const wtl_time*);

int parse_int(const char*);

float parse_float(const char*);

char* strsub(const char*, int, int);

int valid_time_format(const char*);

int strpos(const char*, const char);
