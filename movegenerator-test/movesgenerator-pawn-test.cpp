#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"


extern void testMoves(const int expectedCount, const char *boardString);
extern void testMovesFromFen(const int expectedCount, const char *boardString);
extern void testValidMoves(const int expectedCount, const char *boardString);


TEST_GROUP(MovesGeneratorPawn)
{
};


TEST(MovesGeneratorPawn, TestMove)
{
   testMoves(2, "\
a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - - - 3\
2 - - - - - - - P 2\
1 - - - - - - - - 1\
 a b c d e f g h\
");

testMoves(0, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - - k 3\
2 - - - - - - - P 2\
1 - - - - - - - - 1\
  a b c d e f g h\
");

testMoves(3, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - n - 3\
2 - - - - - - - P 2\
1 - - - - - - - - 1\
  a b c d e f g h\
");


testMoves(4, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - n - n - n - 3\
2 - - - P - - - - 2\
1 - - - - - - - - 1\
  a b c d e f g h\
");

testMoves(2, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - n - - - - - 6\
5 - - - P - - - - 5\
4 - - - - - - - - 4\
3 - - n - n - n - 3\
2 - - - - - - - - 2\
1 - - - - - - - - 1\
  a b c d e f g h\
");


testMoves(12, "\
  a b c d e f g h\
8 - - - n - n - - 8\
7 - - - - P - - - 7\
6 - - n - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - n - n - n - 3\
2 - - - - - - - - 2\
1 - - - - - - - - 1\
  a b c d e f g h\
");

testMovesFromFen(2, "111n1n111/11111111/11n11pP1/11111111/11111111/11n1n1n1/11111111/11111111 w KQkq f7 0 1");

}

