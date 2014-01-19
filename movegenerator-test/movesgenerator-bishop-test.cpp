#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"
#include "movegenerator.h"

TEST_GROUP(MovesGeneratorBishop)
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


TEST(MovesGeneratorBishop, TestMove)
{
TEST_MOVES(7, "\
   a b c d e f g h      \
 8 - - - - - - - - 8    \
 7 - - - - - - - - 7    \
 6 - - - - - - - - 6    \
 5 - - - - - - - - 5    \
 4 - - - - - - - - 4    \
 3 - - - - - - - - 3    \
 2 - - - - - - - - 2    \
 1 - - - - - - B - 1    \
   a b c d e f g h      \
");


TEST_MOVES(13, "\
   a b c d e f g h      \
 8 - - - - - - - - 8    \
 7 - - - - - - - - 7    \
 6 - - - - - - - - 6    \
 5 - - - B - - - - 5    \
 4 - - - - - - - - 4    \
 3 - - - - - - - - 3    \
 2 - - - - - - - - 2    \
 1 - - - - - - - - 1    \
   a b c d e f g h      \
");

TEST_MOVES(4, "\
   a b c d e f g h      \
 8 - - - - - - - - 8    \
 7 - - - - - - - - 7    \
 6 - - n - n - - - 6    \
 5 - - - B - - - - 5    \
 4 - - n - n - - - 4    \
 3 - - - - - - - - 3    \
 2 - - - - - - - - 2    \
 1 - - - - - - - - 1    \
   a b c d e f g h      \
");

TEST_MOVES(4, "\
  a b c d e f g h      \
8 - - - - - - - - 8    \
7 - - - - - - - - 7    \
6 - - n n n - - - 6    \
5 - - n B n - - - 5    \
4 - - n n n - - - 4    \
3 - - - - - - - - 3    \
2 - - - - - - - - 2    \
1 - - - - - - - - 1    \
  a b c d e f g h      \
");

TEST_MOVES(17, "\
 a b c d e f g h      \
8 - - - - - - - - 8    \
7 - - - - - - - - 7    \
6 - - K - - - - - 6    \
5 - - - B - - - - 5    \
4 - - - - - - - - 4    \
3 - - - - - - - - 3    \
2 - - - - - - - - 2    \
1 - - - - - - - - 1    \
 a b c d e f g h      \
");

TEST_MOVES(7, "\
a b c d e f g h      \
8 B - - - - - - - 8    \
7 - K - - - - - - 7    \
6 - - - - - - - - 6    \
5 - - - - - - - - 5    \
4 - - - - - - - - 4    \
3 - - - - - - - - 3    \
2 - - - - - - - - 2    \
1 - - - - - - - - 1    \
a b c d e f g h      \
");


TEST_MOVES(10, "\
a b c d e f g h      \
8 - - - - - - - - 8    \
7 - B - - - - - - 7    \
6 - - K - - - - - 6    \
5 - - - - - - - - 5    \
4 - - - - - - - - 4    \
3 - - - - - - - - 3    \
2 - - - - - - - - 2    \
1 - - - - - - - - 1    \
a b c d e f g h      \
");
}

