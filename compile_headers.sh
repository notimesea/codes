#!/bin/bash
set -e
for header in *.hpp; do
  echo "Testing $header"
  echo -e "#include \"$header\"\nint main(){}" > _tmp.cpp
  g++ -std=c++17 -c _tmp.cpp
  rm -f _tmp.o
done
rm -f _tmp.cpp
