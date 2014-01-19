#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"
#include "movegenerator.h"


TEST_GROUP(MovesGeneratorRook)
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


TEST(MovesGeneratorRook, TestMove)
{

TEST_MOVES(14, "\
    a b c d e f g h     \
  8 - - - - - - - - 8   \
  7 - - - - - - - - 7   \
  6 - - - - - - - - 6   \
  5 - - - - - - - - 5   \
  4 - - - - - - - - 4   \
  3 - - - - - - - - 3   \
  2 - - - - - - - - 2   \
  1 R - - - - - - - 1   \
    a b c d e f g h     \
");


TEST_MOVES(2, "\
   a b c d e f g h     \
 8 - - - - - - - - 8   \
 7 - - - - - - - - 7   \
 6 - - - - - - - - 6   \
 5 - - - - - - - - 5   \
 4 - - - - - - - - 4   \
 3 - - - - - - - - 3   \
 2 n - - - - - - - 2   \
 1 R n - - - - - - 1   \
   a b c d e f g h     \
");

TEST_MOVES(8, "\
   a b c d e f g h          \
 8 - n - - - - - - 8        \
 7 - - - - - - - - 7        \
 6 - - - - n - - - 6        \
 5 - - - - - - - - 5        \
 4 - - - - - n - - 4        \
 3 - n - - - - - - 3        \
 2 - - n - - - - - 2        \
 1 - - R - - - - - 1        \
   a b c d e f g h          \
");


TEST_MOVES(12, "\
   a b c d e f g h          \
 8 - n - - - - - - 8        \
 7 - - - - - - - - 7        \
 6 - - - - n - - - 6        \
 5 - - - - - - - - 5        \
 4 - - - R - n - - 4        \
 3 - n - - - - - - 3        \
 2 - - n - - - - - 2        \
 1 n - - - n - - - 1        \
   a b c d e f g h          \
");

TEST_MOVES(17, "\
   a b c d e f g h         \
 8 - n - n - - - - 8       \
 7 - - - - - - - - 7       \
 6 - - - - n - - - 6       \
 5 - - - - - - - - 5       \
 4 - - - - - n - - 4       \
 3 - n - R - - - n 3       \
 2 n - - - - - - - 2       \
 1 R - - n - - - - 1       \
   a b c d e f g h         \
");


TEST_MOVES(3, "\
   a b c d e f g h          \
 8 - n - - - - - - 8        \
 7 - - - - - - - - 7        \
 6 - - - - n - - - 6        \
 5 n - - - - - - - 5        \
 4 R n - - - n - - 4        \
 3 n n - - - - - - 3        \
 2 - - - - - - - - 2        \
 1 - - - - - - n - 1        \
   a b c d e f g h          \
");

TEST_MOVES(5, "\
  a b c d e f g h      \
8 - n - - - - - - 8    \
7 - - - - - - - - 7    \
6 - - - - n - - - 6    \
5 - - - - - - - - 5    \
4 - - - - - n - - 4    \
3 - n - - - - - - 3    \
2 K - n - - - - - 2    \
1 R n - n - - - - 1    \
  a b c d e f g h      \
");

TEST_MOVES(13, "\
   a b c d e f g h         \
 8 - n - - - - - - 8       \
 7 - - - - - - - - 7       \
 6 - - - - n - - - 6       \
 5 n - - - - - - - 5       \
 4 - n - - - n - - 4       \
 3 n n - - - - - - 3       \
 2 - - - K - - - - 2       \
 1 - - - R - - n - 1       \
   a b c d e f g h         \
");

}

