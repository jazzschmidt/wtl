/* Simple Configuration Parsing
 * ----------------------------
 * Parses a key-value configuration string, coverts the values with registered
 * parser functions, and applies them to a structure.
 *
 * Example:
 *  struct Config { char *name; };
 *
 *  void parseName(const char *key, const char *value, const void *cfg) {
 *    struct Config *config = (struct Config *)cfg;
 *    asprintf(&(cfg->name), "%s", value);
 *  }
 *
 *  void configure() {
 *    struct Config cfg;
 *    registerParser("name", &parseName);
 *    parseConfig("name=foo", &cfg);
 *  }
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

/* --------------------- Global variables --------------------- */


/* Links a parser function to a key of the fonfiguration */
typedef struct {
  const char *key;
  ConfigReader reader;
  ConfigWriter writer;
} KeyParser;

/* List of registered parser functions */
static KeyParser **parserList = NULL;
static int registeredParsers = 0;


/* --------------------- Prototypes --------------------- */


/* Parses a configuration string */
static void parseConfigLine(const char *line, const void *config);

/* Retrieves both the key and the value of a string */
static void strkeyvalue(const char *line, char **key, char **value);

/* Removes trailing new line */
static void stripNewline(char *line);

/* Removes all parsers. Will be called automatically */
static void clearParser(void);

/* --------------------- Implementation --------------------- */

/* Function: registerParser
 * ------------------------
 * Registers a parser function for a specific key.
 *
 * key: which configuration key the parser will be linked to
 * parser: applies the value to the configuration
 */
void registerParser(const char *key, ConfigReader reader, ConfigWriter writer) {
  void *ptr = realloc(parserList, (registeredParsers + 1) * sizeof((void *)0));
  if(ptr == NULL) {
    return;
  }

  /* Frees all parsers on exit */
  if(registeredParsers == 0) {
    atexit(clearParser);
  }

  parserList = ptr;

  KeyParser *link = malloc(sizeof(KeyParser));
  *link = (KeyParser){
    .key = key, .reader = reader, .writer = writer
  };

  *(parserList + registeredParsers) = link;
  registeredParsers++;
}


/* Function: parseConfig
 * ---------------------
 * Parses a multi-line string and applies the values to the configuration
 * struct. There must be parsers registered via `registerParser` in order to
 * process the configuration keys.
 *
 * content: multi-line key-value string
 * config: configuration structure
 */
void parseConfig(const char *content, const void *config) {
  char *src = strdup(content);

  for (char *line = strtok(src, "\n"); line != NULL; line = strtok(NULL, "\n")) {
    parseConfigLine(line, config);
  }

  clearParser();
}


void parseConfigFile(FILE *file, const void *config) {
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  while((linelen = getline(&line, &linecap, file)) != -1) {
    parseConfigLine(line, config);
  }

  clearParser();
}


void writeConfigFile(FILE *file, const void *config) {

}

/* --------------------- Internal routines --------------------- */


/* Function: getParser
 * -------------------
 * Returns the parser for a specific key or `NULL` if no parser is present for
 * the given key.
 */
static KeyParser *getParser(char *key) {
  KeyParser *parser = NULL;

  for(int i = 0; i < registeredParsers; ++i) {
    parser = *(parserList + i);
    if(strcmp(parser->key, key) == 0) {
      return parser;
    }
 }

 return NULL;
}

static ConfigReader getReaderFor(char *key) {
  return (ConfigReader)(getParser(key)->reader);
}

static ConfigWriter getWriterFor(char *key) {
  return (ConfigWriter)(getParser(key)->writer);
}


/* Function: parseConfigLine
 * -------------------------
 * Parses a configuration line and applies its value to the configuration
 * struct.
 */
static void parseConfigLine(const char *line, const void *config) {
  char *key, *value;
  strkeyvalue(line, &key, &value);

  stripNewline(value);

  ConfigReader reader;
  if((reader = getReaderFor(key))) {
    reader(key, value, config);
  }
}


/* Function strkeyvalue
 * --------------------
 * Splits the string `line` into its key and value.
 */
static void strkeyvalue(const char *line, char **key, char **value) {
	const char *assignment = index(line, '=');
	const int index = strlen(line) - strlen(assignment);

	*key = strndup(line, index);
	*value = strdup(++assignment);
}


static void stripNewline(char *line) {
  char *last = line + strlen(line)-1;

  if(*last == '\n') {
    *last = '\0';
  }
}


/* Function: clearParser
 * ---------------------
 * Frees all registered parsers
 */
static void clearParser(void) {
  for(int i = 0; i < registeredParsers; ++i) {
    KeyParser *parser = *(parserList + i);
    free(parser);
  }

  registeredParsers = 0;
}
