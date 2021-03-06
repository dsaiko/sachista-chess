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

TEST_GROUP(MovesGeneratorBishop) {
};


TEST(MovesGeneratorBishop, TestMove) {
    testMovesFromString(7, R"(
   a b c d e f g h
 8 - - - - - - - - 8
 7 - - - - - - - - 7
 6 - - - - - - - - 6
 5 - - - - - - - - 5
 4 - - - - - - - - 4
 3 - - - - - - - - 3
 2 - - - - - - - - 2
 1 - - - - - - B - 1
   a b c d e f g h
)");


    testMovesFromString(13, R"(
   a b c d e f g h
 8 - - - - - - - - 8
 7 - - - - - - - - 7
 6 - - - - - - - - 6
 5 - - - B - - - - 5
 4 - - - - - - - - 4
 3 - - - - - - - - 3
 2 - - - - - - - - 2
 1 - - - - - - - - 1
   a b c d e f g h
)");

    testMovesFromString(4, R"(
   a b c d e f g h
 8 - - - - - - - - 8
 7 - - - - - - - - 7
 6 - - n - n - - - 6
 5 - - - B - - - - 5
 4 - - n - n - - - 4
 3 - - - - - - - - 3
 2 - - - - - - - - 2
 1 - - - - - - - - 1
   a b c d e f g h
)");

    testMovesFromString(4, R"(
  a b c d e f g h
8 - - - - - - - - 8
7 - - - - - - - - 7
6 - - n n n - - - 6
5 - - n B n - - - 5
4 - - n n n - - - 4
3 - - - - - - - - 3
2 - - - - - - - - 2
1 - - - - - - - - 1
  a b c d e f g h
)");

    testMovesFromString(17, R"(
 a b c d e f g h
8 - - - - - - - - 8
7 - - - - - - - - 7
6 - - K - - - - - 6
5 - - - B - - - - 5
4 - - - - - - - - 4
3 - - - - - - - - 3
2 - - - - - - - - 2
1 - - - - - - - - 1
 a b c d e f g h
)");

    testMovesFromString(7, R"(
  a b c d e f g h
8 B - - - - - - - 8
7 - K - - - - - - 7
6 - - - - - - - - 6
5 - - - - - - - - 5
4 - - - - - - - - 4
3 - - - - - - - - 3
2 - - - - - - - - 2
1 - - - - - - - - 1
  a b c d e f g h
)");


    testMovesFromString(10, R"(
  a b c d e f g h
8 - - - - - - - - 8
7 - B - - - - - - 7
6 - - K - - - - - 6
5 - - - - - - - - 5
4 - - - - - - - - 4
3 - - - - - - - - 3
2 - - - - - - - - 2
1 - - - - - - - - 1
  a b c d e f g h
)");
}

