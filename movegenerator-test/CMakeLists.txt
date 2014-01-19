include_directories     (${SACHISTA_CHESS_SOURCE_DIR}/movegenerator)

link_directories        (${SACHISTA_CHESS_SOURCE_DIR}/movegenerator)

add_executable          (
    movegenerator-test
    bitboard-test
    chesspiece-test
    chessboard-test
    movesgenerator-test
    movesgenerator-pawn-test
    movesgenerator-knight-test
    movesgenerator-king-test
    movesgenerator-queen-test
    movesgenerator-bishop-test
    movesgenerator-rook-test
    main
)

target_link_libraries   (movegenerator-test CppUTest CppUTestExt movegenerator)


