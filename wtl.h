
typedef struct {
  int hour; int minute;
} wtl_time;

typedef struct {
  wtl_time* time;
  FILE *config;
  float hours;
} wtl_args;

void print_usage(void);

wtl_args* parse_args(int argc, char** argv);

wtl_time* parse_time(const char*);

wtl_time* add_time(const wtl_time*, int, int);

char* str_time(const wtl_time*);

int parse_int(const char*);

float parse_float(const char*);

char* strsub(const char*, int, int);
