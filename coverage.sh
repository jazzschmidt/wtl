#!/bin/bash

stdin=$(cat)
IFS=$'\n'

FILES=($(echo "${stdin}" | grep "File" | cut -d"'" -f2))

if [[ "${#FILES[@]}" -eq 0 ]]; then
  exit 0 # Cancel formatting when no files in input
fi

FILE=0
FUNC=""
COV=""

COV_LINES=""

echo "COVERAGE SUMMARY"

for line in ${stdin}; do
  if [[ "${line}" = "Function"* ]]; then
    FUNC=$(echo "${line}" | cut -d"'" -f2)
  elif [[ "${line}" = "Lines executed"* ]]; then
    COV=$(echo "${line}" | cut -d":" -f2 | cut -d"%" -f1)
    COV=$(printf "%6.2f%%" "$COV")

    COV_LINES="${COV_LINES}${COV} ${FUNC}\n"
  elif [[ "${line}" = "File"* ]]; then
    echo "File: ${FILES[$((FILE++))]}"
    echo -e ${COV_LINES} | sort -rn
  fi
done
