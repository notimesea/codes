#!/bin/bash
set -e
CXX=${CXX:-g++}
CXXFLAGS=${CXXFLAGS:--std=c++20 -O2}
for src in test/*_test.cpp; do
  exe="${src%.cpp}"
  $CXX $CXXFLAGS -I. "$src" -o "$exe"
  "$exe"
  echo "Ran $exe"
done
