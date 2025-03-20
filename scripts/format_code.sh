#!/bin/bash

[[ ! $(clang-format --version) ]] && exit 1

[[ ! -d ./src ]] && (echo "Please run script from the project root"; exit 1)

files=$(find src -name "*.?pp")

[[ "$files" == "" ]] && (echo "-- No source files found"; exit)

clang-format -i $files || exit 1
echo -e "-- Formatted Files:\n$files\n"

exit
