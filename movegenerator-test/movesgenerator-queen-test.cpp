#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"
#include "movegenerator.h"


TEST_GROUP(MovesGeneratorQueen)
{
};

#define TEST_MOVES(EXPECTED, BOARD)                         \
{                                                           \
    struct chessBoard board = boardFromString(BOARD);       \
    struct move moves[256];                                 \
    int size = generateMoves(&board, moves, 256);           \
    LONGS_EQUAL((EXPECTED), size);                          \
}

#define TEST_MOVES2(EXPECTED, BOARD)                        \
{                                                           \
    struct chessBoard board = boardFromFEN(BOARD);          \
    struct move moves[256];                                 \
    int size = generateMoves(&board, moves, 256);           \
    LONGS_EQUAL((EXPECTED), size);                          \
}


TEST(MovesGeneratorQueen, TestMove)
{

}

