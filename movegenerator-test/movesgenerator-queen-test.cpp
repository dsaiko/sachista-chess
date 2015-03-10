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
#include "movesgenerator-test.h"


TEST_GROUP(MovesGeneratorQueen)
{
};

TEST(MovesGeneratorQueen, TestMove)
{
    testMovesFromString(5, R"(
  a b c d e f g h
8 - - - - - - - - 8
7 - - - - - - - - 7
6 - - - - - - - - 6
5 - - - - - - - - 5
4 - - - - - - - - 4
3 - - - - - - - - 3
2 n n n - - - - - 2
1 n Q n - - - - - 1
  a b c d e f g h
)");

    testMovesFromString(31, R"(
  a b c d e f g h
8 - - - - - - - - 8
7 - - - - - - - - 7
6 - - - - - - - - 6
5 - - - - - - - - 5
4 - - - - Q - - - 4
3 - - - - - - - - 3
2 n n n - - - - - 2
1 n Q n - - - - - 1
  a b c d e f g h
)");

    testMovesFromString(46, R"(
 a b c d e f g h
8 - - - - - - - - 8
7 - - - - - - - - 7
6 - - - - - - - - 6
5 - - - - - - - - 5
4 - - - - Q - - Q 4
3 - - - - - - - - 3
2 n n n - - - - - 2
1 n Q n - - - - - 1
 a b c d e f g h
)");

    testMoves(218, ChessBoard("3Q4/1Q4Q1/4Q3/2Q4R/Q4Q2/3Q4/1Q4Rp/1K1BBNNk w - - 0 1"));
}

