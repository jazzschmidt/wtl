#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

typedef struct {
  const char *key; Parser parser;
} ParserKeyLink;

static ParserKeyLink **parserList = NULL;
static int registeredParsers = 0;


void strkeyvalue(const char *line, char **key, char **value);

void registerParser(const char *key, Parser parser) {
  void *ptr = realloc(parserList, (registeredParsers + 1) * sizeof((void *)0));
  if(ptr == NULL) {
    return;
  }

  parserList = ptr;

  ParserKeyLink *link = malloc(sizeof(ParserKeyLink));
  *link = (ParserKeyLink){
    .key = key, .parser = parser
  };

  *(parserList + registeredParsers) = link;
  registeredParsers++;
}


static Parser getParser(char *key) {
  ParserKeyLink *link = NULL;
  for(int i = 0; i < registeredParsers; ++i) {
    link = *(parserList + i);
    if(strcmp(link->key, key) == 0) {
      return link->parser;
    }
  }

  return NULL;
}

void parseConfigLine(const char *line, const void *config);

void parseConfig(const char *content, const void *config) {
  char *src = strdup(content);

  for (char *line = strtok(src, "\n"); line != NULL; line = strtok(NULL, "\n")) {
    parseConfigLine(line, config);
  }
}

void parseConfigLine(const char *line, const void *config) {
  char *key, *value;
  strkeyvalue(line, &key, &value);

  Parser parser;
  if((parser = getParser(key))) {
    parser(key, value, config);
  }
}

void strkeyvalue(const char *line, char **key, char **value) {
	char *assignment = index(line, '=');
	int index = strlen(line) - strlen(assignment);

	*key = malloc(sizeof(char) * (index + 1));
	strncpy(*key, line, index);
  *(*key + index) = '\0';

	*value = malloc(sizeof(char) * (strlen(assignment++)));
	strncpy(*value, assignment, strlen(assignment));
  *(*value + strlen(*value)) = '\0';
}
