#!/usr/bin/env bash

cmake -B build
cmake --build build
./build/cli
echo $?     # prints 1
