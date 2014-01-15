cmake_minimum_required      (VERSION 2.8.7)
project                     (SACHISTA_CHESS)

enable_language             (C)
enable_language             (CXX)

# The version number
set                         (SACHISTA_CHESS_VERSION_MAJOR 0)
set                         (SACHISTA_CHESS_VERSION_MINOR 1)

add_subdirectory            (movegenerator)
add_subdirectory            (movegenerator-test)
