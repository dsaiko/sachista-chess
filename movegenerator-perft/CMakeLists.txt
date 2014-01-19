include_directories     (${SACHISTA_CHESS_SOURCE_DIR}/movegenerator)
link_directories        (${SACHISTA_CHESS_SOURCE_DIR}/movegenerator)

add_executable (
    movegenerator-perft
    perft
)

target_link_libraries(movegenerator-perft movegenerator)
