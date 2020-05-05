
typedef void (*ConfigReader)(const char *key, const char *value, const void *config);
typedef void (*ConfigWriter)(const char *key, const void *config);

void registerParser(const char *key, ConfigReader reader, ConfigWriter writer);

void parseConfig(const char *content, const void *config);

void parseConfigFile(FILE *file, const void *config);

void writeConfigFile(FILE *file, const void *config);
