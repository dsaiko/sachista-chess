#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"
#include "movegenerator.h"

TEST_GROUP(MovesGeneratorKing)
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


TEST(MovesGeneratorKing, TestMove)
{

    TEST_MOVES(8, "     \
  a b c d e f g h       \
8 - n - - - - - - 8     \
7 - - - - - - - - 7     \
6 - - - - n - - - 6     \
5 - - - - - - - - 5     \
4 - - - - - n - - 4     \
3 - n - - - - - - 3     \
2 - - - K - - - - 2     \
1 - - - - - - - - 1     \
  a b c d e f g h       \
");

}

