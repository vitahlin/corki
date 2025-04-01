#!/usr/bin/env bash

rm -rf CMakeCache.txt CMakeFiles
cmake .
cmake --build .