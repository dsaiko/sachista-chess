#!/bin/bash

rm -rf BUILD-DEBUG 2>/dev/null

mkdir BUILD-DEBUG
cd BUILD-DEBUG
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
cd ..

