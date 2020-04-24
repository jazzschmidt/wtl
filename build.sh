#!/bin/bash

# Remove previous build
if [[ -f wtl ]]; then
  rm -f wtl
fi

# Compile
gcc -o wtl wtl.c || exit 1

# Test formatter methods
_testname=
function startTest() {
  _testname=$1
}

function evalTest() {
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
evalTest

startTest "Outputs leaving time for 08:00"
time=$(./wtl 08:00)
[[ "$time" == "16:20" ]]
evalTest

startTest "Outputs leaving time for 10:00"
time=$(./wtl 10:00)
[[ "$time" == "18:20" ]]
evalTest
