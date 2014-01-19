#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"
#include "movegenerator.h"

TEST_GROUP(MovesGeneratorBishop)
{
};

extern void testMoves(const int expectedCount, const char *boardString);
extern void testMovesFromFen(const int expectedCount, const char *boardString);
extern void testValidMoves(const int expectedCount, const char *boardString);

TEST(MovesGeneratorBishop, TestMove)
{
testMoves(7, "\
   a b c d e f g h\
 8 - - - - - - - - 8\
 7 - - - - - - - - 7\
 6 - - - - - - - - 6\
 5 - - - - - - - - 5\
 4 - - - - - - - - 4\
 3 - - - - - - - - 3\
 2 - - - - - - - - 2\
 1 - - - - - - B - 1\
   a b c d e f g h\
");


testMoves(13, "\
   a b c d e f g h\
 8 - - - - - - - - 8\
 7 - - - - - - - - 7\
 6 - - - - - - - - 6\
 5 - - - B - - - - 5\
 4 - - - - - - - - 4\
 3 - - - - - - - - 3\
 2 - - - - - - - - 2\
 1 - - - - - - - - 1\
   a b c d e f g h\
");

testMoves(4, "\
   a b c d e f g h\
 8 - - - - - - - - 8\
 7 - - - - - - - - 7\
 6 - - n - n - - - 6\
 5 - - - B - - - - 5\
 4 - - n - n - - - 4\
 3 - - - - - - - - 3\
 2 - - - - - - - - 2\
 1 - - - - - - - - 1\
   a b c d e f g h\
");

testMoves(4, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - n n n - - - 6\
5 - - n B n - - - 5\
4 - - n n n - - - 4\
3 - - - - - - - - 3\
2 - - - - - - - - 2\
1 - - - - - - - - 1\
  a b c d e f g h\
");

testMoves(17, "\
 a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - K - - - - - 6\
5 - - - B - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - - - 3\
2 - - - - - - - - 2\
1 - - - - - - - - 1\
 a b c d e f g h\
");

testMoves(7, "\
  a b c d e f g h\
8 B - - - - - - - 8\
7 - K - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - - - 3\
2 - - - - - - - - 2\
1 - - - - - - - - 1\
  a b c d e f g h\
");


testMoves(10, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - B - - - - - - 7\
6 - - K - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - - - 3\
2 - - - - - - - - 2\
1 - - - - - - - - 1\
  a b c d e f g h\
");
}

