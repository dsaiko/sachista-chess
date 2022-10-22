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

TEST_GROUP(MovesGeneratorRook)
{
};


TEST(MovesGeneratorRook, TestMove)
{

    testMovesFromString(14, R"(
  a b c d e f g h
8 - - - - - - - - 8
7 - - - - - - - - 7
6 - - - - - - - - 6
5 - - - - - - - - 5
4 - - - - - - - - 4
3 - - - - - - - - 3
2 - - - - - - - - 2
1 R - - - - - - - 1
  a b c d e f g h
)");


    testMovesFromString(2, R"(
  a b c d e f g h
8 - - - - - - - - 8
7 - - - - - - - - 7
6 - - - - - - - - 6
5 - - - - - - - - 5
4 - - - - - - - - 4
3 - - - - - - - - 3
2 n - - - - - - - 2
1 R n - - - - - - 1
  a b c d e f g h
)");

    testMovesFromString(8, R"(
  a b c d e f g h
8 - n - - - - - - 8
7 - - - - - - - - 7
6 - - - - n - - - 6
5 - - - - - - - - 5
4 - - - - - n - - 4
3 - n - - - - - - 3
2 - - n - - - - - 2
1 - - R - - - - - 1
  a b c d e f g h
)");


    testMovesFromString(12, R"(
  a b c d e f g h
8 - n - - - - - - 8
7 - - - - - - - - 7
6 - - - - n - - - 6
5 - - - - - - - - 5
4 - - - R - n - - 4
3 - n - - - - - - 3
2 - - n - - - - - 2
1 n - - - n - - - 1
  a b c d e f g h
)");

    testMovesFromString(17, R"(
  a b c d e f g h
8 - n - n - - - - 8
7 - - - - - - - - 7
6 - - - - n - - - 6
5 - - - - - - - - 5
4 - - - - - n - - 4
3 - n - R - - - n 3
2 n - - - - - - - 2
1 R - - n - - - - 1
  a b c d e f g h
)");


    testMovesFromString(3, R"(
  a b c d e f g h
8 - n - - - - - - 8
7 - - - - - - - - 7
6 - - - - n - - - 6
5 n - - - - - - - 5
4 R n - - - n - - 4
3 n n - - - - - - 3
2 - - - - - - - - 2
1 - - - - - - n - 1
  a b c d e f g h
)");

    testMovesFromString(5, R"(
  a b c d e f g h
8 - n - - - - - - 8
7 - - - - - - - - 7
6 - - - - n - - - 6
5 - - - - - - - - 5
4 - - - - - n - - 4
3 - n - - - - - - 3
2 K - n - - - - - 2
1 R n - n - - - - 1
  a b c d e f g h
)");

    testMovesFromString(13, R"(
  a b c d e f g h
8 - n - - - - - - 8
7 - - - - - - - - 7
6 - - - - n - - - 6
5 n - - - - - - - 5
4 - n - - - n - - 4
3 n n - - - - - - 3
2 - - - K - - - - 2
1 - - - R - - n - 1
  a b c d e f g h
)");

}

