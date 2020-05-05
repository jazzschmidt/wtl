
typedef void (*Parser)(const char *key, const char *value, const void *config);

void registerParser(const char *key, Parser parser);

void parseConfig(const char *content, const void *config);

void parseConfigFile(FILE *file, const void *config);
