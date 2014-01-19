#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"
#include "movegenerator.h"


TEST_GROUP(MovesGeneratorKnight)
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


TEST(MovesGeneratorKnight, TestMove)
{
TEST_MOVES(6,"\
   a b c d e f g h      \
 8 - - - - - - - - 8    \
 7 - - - - - - - - 7    \
 6 - - - - - - - - 6    \
 5 - - - - - - - - 5    \
 4 - - - - - - - - 4    \
 3 - - - - - - - - 3    \
 2 - - - - - - - - 2    \
 1 - N - - - - N - 1    \
   a b c d e f g h      \
");

TEST_MOVES(14,"\
   a b c d e f g h      \
 8 - - - - - - - - 8    \
 7 - - - - - - - - 7    \
 6 - - - - N - - - 6    \
 5 - - - - - - - - 5    \
 4 - - - - - N - - 4    \
 3 - - - - - - - - 3    \
 2 - - - - - - - - 2    \
 1 - - - - - - - - 1    \
   a b c d e f g h      \
");

TEST_MOVES(23,"\
   a b c d e f g h      \
 8 - N - - - - - - 8    \
 7 - - - - - - - - 7    \
 6 - - - - N - - - 6    \
 5 - - - - - - - - 5    \
 4 - - - - - N - - 4    \
 3 - N - - - - - - 3    \
 2 - - - - - - - - 2    \
 1 - - - - - - - - 1    \
   a b c d e f g h      \
");

}

