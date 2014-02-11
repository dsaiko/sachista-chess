/*
  sachista-chess copyright (C) 2014 dusan.saiko@gmail.com

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


TEST_GROUP(MovesGeneratorRook)
{
};


TEST(MovesGeneratorRook, TestMove)
{

testMoves(14, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - - - 3\
2 - - - - - - - - 2\
1 R - - - - - - - 1\
  a b c d e f g h\
");


testMoves(2, "\
  a b c d e f g h\
8 - - - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - - - - - 6\
5 - - - - - - - - 5\
4 - - - - - - - - 4\
3 - - - - - - - - 3\
2 n - - - - - - - 2\
1 R n - - - - - - 1\
  a b c d e f g h\
");

testMoves(8, "\
  a b c d e f g h\
8 - n - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - n - - - 6\
5 - - - - - - - - 5\
4 - - - - - n - - 4\
3 - n - - - - - - 3\
2 - - n - - - - - 2\
1 - - R - - - - - 1\
  a b c d e f g h\
");


testMoves(12, "\
  a b c d e f g h\
8 - n - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - n - - - 6\
5 - - - - - - - - 5\
4 - - - R - n - - 4\
3 - n - - - - - - 3\
2 - - n - - - - - 2\
1 n - - - n - - - 1\
  a b c d e f g h\
");

testMoves(17, "\
  a b c d e f g h\
8 - n - n - - - - 8\
7 - - - - - - - - 7\
6 - - - - n - - - 6\
5 - - - - - - - - 5\
4 - - - - - n - - 4\
3 - n - R - - - n 3\
2 n - - - - - - - 2\
1 R - - n - - - - 1\
  a b c d e f g h\
");


testMoves(3, "\
  a b c d e f g h\
8 - n - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - n - - - 6\
5 n - - - - - - - 5\
4 R n - - - n - - 4\
3 n n - - - - - - 3\
2 - - - - - - - - 2\
1 - - - - - - n - 1\
  a b c d e f g h\
");

testMoves(5, "\
  a b c d e f g h\
8 - n - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - n - - - 6\
5 - - - - - - - - 5\
4 - - - - - n - - 4\
3 - n - - - - - - 3\
2 K - n - - - - - 2\
1 R n - n - - - - 1\
  a b c d e f g h\
");

testMoves(13, "\
  a b c d e f g h\
8 - n - - - - - - 8\
7 - - - - - - - - 7\
6 - - - - n - - - 6\
5 n - - - - - - - 5\
4 - n - - - n - - 4\
3 n n - - - - - - 3\
2 - - - K - - - - 2\
1 - - - R - - n - 1\
  a b c d e f g h\
");

}

