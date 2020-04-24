#!/bin/bash

# Remove previous build
if [[ -f wtl ]]; then
  rm -f wtl
fi

# Compile
gcc -o wtl wtl.c || exit 1
