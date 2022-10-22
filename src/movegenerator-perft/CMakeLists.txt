add_executable(movegenerator-perft main.cpp)

target_link_libraries(movegenerator-perft movegenerator)
target_include_directories(movegenerator-perft PRIVATE ../movegenerator)
