#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"


extern void testMoves(const int expectedCount, const char *boardString);
extern void testMovesFromFen(const int expectedCount, const char *boardString);
extern void testValidMoves(const int expectedCount, const char *boardString);

TEST_GROUP(MovesGeneratorKnight)
{
};



TEST(MovesGeneratorKnight, TestMove)
{
testMoves(6,"\
   a b c d e f g h\
 8 - - - - - - - - 8\
 7 - - - - - - - - 7\
 6 - - - - - - - - 6\
 5 - - - - - - - - 5\
 4 - - - - - - - - 4\
 3 - - - - - - - - 3\
 2 - - - - - - - - 2\
 1 - N - - - - N - 1\
   a b c d e f g h\
");

testMoves(14,"\
   a b c d e f g h\
 8 - - - - - - - - 8\
 7 - - - - - - - - 7\
 6 - - - - N - - - 6\
 5 - - - - - - - - 5\
 4 - - - - - N - - 4\
 3 - - - - - - - - 3\
 2 - - - - - - - - 2\
 1 - - - - - - - - 1\
   a b c d e f g h\
");

testMoves(23,"\
   a b c d e f g h\
 8 - N - - - - - - 8\
 7 - - - - - - - - 7\
 6 - - - - N - - - 6\
 5 - - - - - - - - 5\
 4 - - - - - N - - 4\
 3 - N - - - - - - 3\
 2 - - - - - - - - 2\
 1 - - - - - - - - 1\
   a b c d e f g h\
");

}

