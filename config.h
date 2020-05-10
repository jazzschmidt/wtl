
typedef void (*ConfigReader)(const char *key, const char *value, const void *config);
typedef char *(*ConfigWriter)(const char *key, const void *config);

void registerParser(const char *key, ConfigReader reader, ConfigWriter writer);

void clearParser(void);

void parseConfig(const char *content, const void *config);

void parseConfigFile(char *file, const void *config);

void writeConfigFile(char *file, const void *config);
