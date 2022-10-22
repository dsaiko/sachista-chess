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

TEST_GROUP(MovesGeneratorKnight)
{
};


TEST(MovesGeneratorKnight, TestMove)
{
    testMovesFromString(6,R"(
       a b c d e f g h
     8 - - - - - - - - 8
     7 - - - - - - - - 7
     6 - - - - - - - - 6
     5 - - - - - - - - 5
     4 - - - - - - - - 4
     3 - - - - - - - - 3
     2 - - - - - - - - 2
     1 - N - - - - N - 1
       a b c d e f g h
    )");

    testMovesFromString(14,R"(
        a b c d e f g h
      8 - - - - - - - - 8
      7 - - - - - - - - 7
      6 - - - - N - - - 6
      5 - - - - - - - - 5
      4 - - - - - N - - 4
      3 - - - - - - - - 3
      2 - - - - - - - - 2
      1 - - - - - - - - 1
        a b c d e f g h
    )");

    testMovesFromString(23,R"(
        a b c d e f g h
      8 - N - - - - - - 8
      7 - - - - - - - - 7
      6 - - - - N - - - 6
      5 - - - - - - - - 5
      4 - - - - - N - - 4
      3 - N - - - - - - 3
      2 - - - - - - - - 2
      1 - - - - - - - - 1
        a b c d e f g h
    )");

    testLegalMovesFromString(1,R"(
        a b c d e f g h
      8 - k q q q - - - 8
      7 - n - - - - - - 7
      6 - - - - - - - - 6
      5 - - - - - - - - 5
      4 - - - - - - - - 4
      3 - - - - - - - - 3
      2 - - - - - - - - 2
      1 - - - K - N - - 1
        a b c d e f g h
    )");

    testLegalMovesFromString(3,R"(
        a b c d e f g h
      8 - k q q q - - - 8
      7 - n - - - - - - 7
      6 - - - - - - - - 6
      5 - - - - - - - - 5
      4 - - - - - - - - 4
      3 - - - - p - - - 3
      2 - - - - - - - - 2
      1 - - - K - N - - 1
        a b c d e f g h
    )");
}

