#!/bin/bash

rm -rf BUILD-RELEASE 2>/dev/null
rm -rf BUILD-DEBUG 2>/dev/null

mkdir BUILD-RELEASE
cd BUILD-RELEASE
cmake -DCMAKE_BUILD_TYPE=Release ..
make
find . -type f -executable | grep -v CMakeFiles | xargs strip -s
cd ..

mkdir BUILD-DEBUG
cd BUILD-DEBUG
cmake -DCMAKE_BUILD_TYPE=DEBUG ..
make
cd ..
