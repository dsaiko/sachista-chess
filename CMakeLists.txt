cmake_minimum_required      (VERSION 2.8.7)
project                     (SACHISTA_CHESS)

SET(CMAKE_BUILD_TYPE RELEASE)

enable_language             (C)

add_subdirectory            (movegenerator)
add_subdirectory            (movegenerator-perft)

enable_language             (CXX)

add_subdirectory            (movegenerator-test)

