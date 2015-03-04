/*
  sachista-chess copyright (C) 2014,2015 dusan.saiko@gmail.com

  sachista-chess is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  sachista-chess is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"

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

testValidMoves(1, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - - - 3\
2 q - - - - k - - 2\
1 - - - K - - - - 1\
  a b c d e f g h\
");
}

