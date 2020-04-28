#!/bin/bash

# Remove previous build
if [[ -f wtl ]]; then
  rm -f wtl
fi

# Compile
gcc --analyze --analyzer-output html -o wtl wtl.c || exit 1
mv wtl report
