#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

typedef struct {
  const char *key; Parser parser;
} ParserKeyLink;

static ParserKeyLink **parserList = NULL;
static int registeredParsers = 0;


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

void parseConfig(const char *content, const void *config) {
  char *fields[] = {
    "name", "num", "fnum"
  };
  char *values[] = {
    "test", "42", "4.5"
  };

  for(int i = 0; i < 3; ++i) {
    char *field = fields[i];
    char *value = values[i];
    Parser parser = getParser(field);

    if(!parser) {
      fprintf(stderr, ">> No Parser!\n");
    } else {
      parser(field, value, config);
    }
  }
}
