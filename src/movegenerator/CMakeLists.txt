set(SOURCES
        bitboard.h
        bitboard.cpp
        chessboard.h
        chessboard.cpp
        chessboard-fen.cpp
        chessboard-perft.cpp
        chessboard-string.cpp
        move.h
        move.cpp
        move-bishop.cpp
        move-king.cpp
        move-knight.cpp
        move-pawn.cpp
        move-rook.cpp
        move-makemove.cpp
        movearray.h
        rand64.h
        rand64.cpp
        utility.h
        utility.cpp
        zobrist.h
        zobrist.cpp
)
add_library(movegenerator ${SOURCES})
