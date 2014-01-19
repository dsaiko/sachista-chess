#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"
#include "movegenerator.h"


extern void testMoves(const int expectedCount, const char *boardString);
extern void testMovesFromFen(const int expectedCount, const char *boardString);
extern void testValidMoves(const int expectedCount, const char *boardString);

TEST_GROUP(MovesGeneratorQueen)
{
};

TEST(MovesGeneratorQueen, TestMove)
{
testMoves(5, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - - - 3\
2 n n n - - - - - 2\
1 n Q n - - - - - 1\
  a b c d e f g h\
");

testMoves(31, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - Q - - - 4\
3 - - - - - - - - 3\
2 n n n - - - - - 2\
1 n Q n - - - - - 1\
  a b c d e f g h\
");

testMoves(46, "\
 a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - Q - - Q 4\
3 - - - - - - - - 3\
2 n n n - - - - - 2\
1 n Q n - - - - - 1\
 a b c d e f g h\
");

testMovesFromFen(218, "3Q4/1Q4Q1/4Q3/2Q4R/Q4Q2/3Q4/1Q4Rp/1K1BBNNk w - - 0 1");
}

