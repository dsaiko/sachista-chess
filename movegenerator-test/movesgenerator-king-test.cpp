#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"
#include "movegenerator.h"

extern void testMoves(const int expectedCount, const char *boardString);
extern void testMovesFromFen(const int expectedCount, const char *boardString);
extern void testValidMoves(const int expectedCount, const char *boardString);

TEST_GROUP(MovesGeneratorKing)
{
};


TEST(MovesGeneratorKing, TestMove)
{

testMoves(8, "\
  a b c d e f g h\
8 - n - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - n - - - 6\
5 - - - - - - - - 5\
4 - - - - - n - - 4\
3 - n - - - - - - 3\
2 - - - K - - - - 2\
1 - - - - - - - - 1\
  a b c d e f g h\
");

testMoves(26, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - - - 3\
2 - - - - - - - - 2\
1 R - - - K - - R 1\
  a b c d e f g h\
");


testMoves(24, "\
 a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - n - - 3\
2 - - - - - - - - 2\
1 R - - - K - - R 1\
 a b c d e f g h\
");

testValidMoves(4,"\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - n - - 3\
2 - - - - - - - - 2\
1 R - - - K - - R 1\
  a b c d e f g h\
");


testMoves(19, "\
 a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - r - - 3\
2 r - - - - - - - 2\
1 R - - - K - - R 1\
 a b c d e f g h\
");


testValidMoves(1,"\
  a b c d e f g h\
8 - - - q - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - n - - 3\
2 r - - - - - - - 2\
1 R - - - K - - R 1\
  a b c d e f g h\
");

testValidMoves(0,"\
  a b c d e f g h\
8 - - - q - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - n - - 3\
2 r - - - - - p - 2\
1 R - - - K - - R 1\
  a b c d e f g h\
");

testMoves(18, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - r - - - 3\
2 r - - - - - - - 2\
1 R - - - K - - R 1\
  a b c d e f g h\
");


testMoves(20, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - - n 3\
2 - - - - - - - - 2\
1 R - - - K - - R 1\
  a b c d e f g h\
");


testMoves(19, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - n - - - - - n 3\
2 - - - - - - - - 2\
1 R - - - K - - R 1\
  a b c d e f g h\
");

testMoves(14, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - n - - - - 3\
2 - - - - - - - - 2\
1 - - - - K - - R 1\
  a b c d e f g h\
");

testMoves(15, "\
  a b c d e f g h\
8 - - - q - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - - - 3\
2 - - - - - - - - 2\
1 - - - K - - - R 1\
  a b c d e f g h\
");
}

