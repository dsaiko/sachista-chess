#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"
#include "movegenerator.h"


TEST_GROUP(MovesGeneratorPawn)
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


TEST(MovesGeneratorPawn, TestMove)
{
   TEST_MOVES(2, "      \
a b c d e f g h         \
8 - - - - - - - - 8     \
7 - - - - - - - - 7     \
6 - - - - - - - - 6     \
5 - - - - - - - - 5     \
4 - - - - - - - - 4     \
3 - - - - - - - - 3     \
2 - - - - - - - P 2     \
1 - - - - - - - - 1     \
 a b c d e f g h        \
");

TEST_MOVES(0, "         \
  a b c d e f g h       \
8 - - - - - - - - 8     \
7 - - - - - - - - 7     \
6 - - - - - - - - 6     \
5 - - - - - - - - 5     \
4 - - - - - - - - 4     \
3 - - - - - - - k 3     \
2 - - - - - - - P 2     \
1 - - - - - - - - 1     \
  a b c d e f g h       \
");

TEST_MOVES(3, "         \
a b c d e f g h         \
8 - - - - - - - - 8     \
7 - - - - - - - - 7     \
6 - - - - - - - - 6     \
5 - - - - - - - - 5     \
4 - - - - - - - - 4     \
3 - - - - - - n - 3     \
2 - - - - - - - P 2     \
1 - - - - - - - - 1     \
a b c d e f g h         \
");


TEST_MOVES(4, "         \
   a b c d e f g h      \
 8 - - - - - - - - 8    \
 7 - - - - - - - - 7    \
 6 - - - - - - - - 6    \
 5 - - - - - - - - 5    \
 4 - - - - - - - - 4    \
 3 - - n - n - n - 3    \
 2 - - - P - - - - 2    \
 1 - - - - - - - - 1    \
   a b c d e f g h      \
");

TEST_MOVES(2, "         \
   a b c d e f g h      \
 8 - - - - - - - - 8    \
 7 - - - - - - - - 7    \
 6 - - n - - - - - 6    \
 5 - - - P - - - - 5    \
 4 - - - - - - - - 4    \
 3 - - n - n - n - 3    \
 2 - - - - - - - - 2    \
 1 - - - - - - - - 1    \
   a b c d e f g h      \
");


TEST_MOVES(12, "        \
   a b c d e f g h      \
 8 - - - n - n - - 8    \
 7 - - - - P - - - 7    \
 6 - - n - - - - - 6    \
 5 - - - - - - - - 5    \
 4 - - - - - - - - 4    \
 3 - - n - n - n - 3    \
 2 - - - - - - - - 2    \
 1 - - - - - - - - 1    \
   a b c d e f g h\
");

TEST_MOVES2(2, "111n1n111/11111111/11n11pP1/11111111/11111111/11n1n1n1/11111111/11111111 w KQkq f7 0 1");

}

