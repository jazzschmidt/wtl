#!/bin/bash

# Remove previous build
if [[ -f wtl ]]; then
  rm -f wtl
fi

# Compile
gcc -o wtl wtl.c

# Test
function passText() {
  if [[ $? -eq 0 ]]; then
    echo "success"
  else
    echo "failure"
  fi
}

echo -n "Shows usage help - "
usage=$(./wtl)
[[ "${usage:0:5}" == "Usage" ]]
passText
