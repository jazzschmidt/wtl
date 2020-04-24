#!/bin/bash

# Remove previous build
if [[ -f wtl ]]; then
  rm -f wtl
fi

# Compile
gcc -o wtl wtl.c

# Test formatter methods
_testname=
function startTest() {
  _testname=$1
}

function evalText() {
  local success=$?
  echo -n "${_testname:-UNDEFINED TEST} - "
  if [[ $success -eq 0 ]]; then
    echo "success"
  else
    echo "failure"
  fi
}

# Tests

startTest "Shows usage help"
usage=$(./wtl)
[[ "${usage:0:5}" == "Usage" ]]
evalText

startTest "Outputs leaving time"
time=$(./wtl 08:00)
[[ "$time" == "16:20" ]]
evalText
