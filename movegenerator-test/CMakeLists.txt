include_directories     (${SACHISTA_CHESS_SOURCE_DIR}/movegenerator)

link_directories        (${HELLO_BINARY_DIR}/movegenerator)

add_executable          (movegenerator-test bitboard-test chesspiece-test main)

target_link_libraries   (movegenerator-test CppUTest CppUTestExt movegenerator)


