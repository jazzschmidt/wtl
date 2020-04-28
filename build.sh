#!/bin/bash

# Remove previous build
if [[ -f wtl ]]; then
  rm -f wtl
fi

# Remove previous reports
if [[ -d report ]]; then
  rm -f report/*
fi

# Analyze
gcc --analyze --analyzer-output html -o report wtl.c || exit 1
# Compile
gcc -o wtl wtl.c || exit 1
