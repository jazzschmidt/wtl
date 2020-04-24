#include <stdio.h>
#include <stdlib.h>
#include "wtl.h"

int main(const int argc, const char** argv) {
  if (argc != 2) {
    print_usage();
    exit(1);
  }
}

void print_usage() {
  printf("Usage: wtl\n");
}
