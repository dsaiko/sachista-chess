#!/usr/bin/env bash

set -eu

BUILD_DEBUG=build-debug
BUILD_RELEASE=build-release

[[ -d "${BUILD_DEBUG}" ]] && rm -rf "${BUILD_DEBUG}"
[[ -d "${BUILD_RELEASE}" ]] && rm -rf "${BUILD_RELEASE}"

mkdir -p ${BUILD_DEBUG}
mkdir -p ${BUILD_RELEASE}

cd ${BUILD_DEBUG}
cmake -DCMAKE_BUILD_TYPE=Debug ../
make -j4
cd ..

cd ${BUILD_RELEASE}
cmake -DCMAKE_BUILD_TYPE=Release ../
make -j4
cd ..

