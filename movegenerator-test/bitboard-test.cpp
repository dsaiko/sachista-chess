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

TEST_GROUP(BitBoardTest)
{
};

TEST(BitBoardTest, Test64BitLong)
{
    bitboard b = 1;

    int size = 0;
    while (b != 0) {
        size++;
        b <<= 1;
    }

    LONGS_EQUAL(64, size);
}


TEST(BitBoardTest, TestLeastSignificantBit)
{
    const int i = bitScan(BITMASK_H2);
    char notation[3];

    fieldNotation(i, notation, sizeof(notation)/sizeof(char));

    STRCMP_EQUAL("h2", notation);
}


TEST(BitBoardTest, TestBitCount)
{
    LONGS_EQUAL(28, popCount(BITMASK_FRAME));
    LONGS_EQUAL(64, popCount(BITMASK_UNIVERSE));
    LONGS_EQUAL(0, popCount(~BITMASK_UNIVERSE));

    LONGS_EQUAL(BITMASK_FILE_A, BITMASK_FILE[0]);
    LONGS_EQUAL(BITMASK_FILE_H, BITMASK_FILE[7]);

    LONGS_EQUAL(BITMASK_RANK_1, BITMASK_RANK[0]);
    LONGS_EQUAL(BITMASK_RANK_8, BITMASK_RANK[7]);

    LONGS_EQUAL(BITMASK_UNIVERSE, BITMASK_FILE[0] | BITMASK_FILE[1] | BITMASK_FILE[2] | BITMASK_FILE[3] | BITMASK_FILE[4] | BITMASK_FILE[5] | BITMASK_FILE[6] | BITMASK_FILE[7] );
    LONGS_EQUAL(BITMASK_UNIVERSE, BITMASK_RANK[0] | BITMASK_RANK[1] | BITMASK_RANK[2] | BITMASK_RANK[3] | BITMASK_RANK[4] | BITMASK_RANK[5] | BITMASK_RANK[6] | BITMASK_RANK[7] );

    LONGS_EQUAL(BITMASK_UNIVERSE, BITMASK_A1H8[0] | BITMASK_A1H8[1] | BITMASK_A1H8[2] | BITMASK_A1H8[3] | BITMASK_A1H8[4] | BITMASK_A1H8[5] | BITMASK_A1H8[6] | BITMASK_A1H8[7] | BITMASK_A1H8[8] | BITMASK_A1H8[9] | BITMASK_A1H8[10] | BITMASK_A1H8[11] | BITMASK_A1H8[12] | BITMASK_A1H8[13] | BITMASK_A1H8[14]);
    LONGS_EQUAL(BITMASK_UNIVERSE, BITMASK_A8H1[0] | BITMASK_A8H1[1] | BITMASK_A8H1[2] | BITMASK_A8H1[3] | BITMASK_A8H1[4] | BITMASK_A8H1[5] | BITMASK_A8H1[6] | BITMASK_A8H1[7] | BITMASK_A8H1[8] | BITMASK_A8H1[9] | BITMASK_A8H1[10] | BITMASK_A8H1[11] | BITMASK_A8H1[12] | BITMASK_A8H1[13] | BITMASK_A8H1[14]);

}

TEST(BitBoardTest, TestIndexes)
{
    for(int i=0; i<64; i++) {
        bitboard b = BITMASK_SQUARE(i);

        LONGS_EQUAL((1ULL << i), b);
        LONGS_EQUAL(1, popCount(b));
    }
}

TEST(BitBoardTest, TestBasicOperations)
{
    LONGS_EQUAL(13, popCount(ONE_NORTH_EAST(BITMASK_FRAME)));
    LONGS_EQUAL(13, popCount(ONE_SOUTH_WEST(BITMASK_FRAME)));

    bitboard b = flipDiagA1H8(BITMASK_A1 | BITMASK_H1 | BITMASK_H8);
    LONGS_EQUAL(BITMASK_A1 | BITMASK_A8 | BITMASK_H8, b);
    LONGS_EQUAL(BITMASK_FILE[1], mirrorHorizontal(BITMASK_FILE[6]));

    LONGS_EQUAL(BITMASK_A8, ONE_NORTH(BITMASK_A7));
    LONGS_EQUAL(BITMASK_A7, ONE_SOUTH(BITMASK_A8));
    LONGS_EQUAL(BITMASK_B7, ONE_EAST(BITMASK_A7));
    LONGS_EQUAL(BITMASK_B7, ONE_WEST(BITMASK_C7));

    LONGS_EQUAL(BITMASK_A3, ONE_NORTH_WEST(BITMASK_B2));
    LONGS_EQUAL(BITMASK_C3, ONE_NORTH_EAST(BITMASK_B2));
    LONGS_EQUAL(BITMASK_C1, ONE_SOUTH_EAST(BITMASK_B2));
    LONGS_EQUAL(BITMASK_A1, ONE_SOUTH_WEST(BITMASK_B2));

    LONGS_EQUAL(0, ONE_NORTH(BITMASK_A8));
    LONGS_EQUAL(0, ONE_NORTH_WEST(BITMASK_A8));
    LONGS_EQUAL(0, ONE_WEST(BITMASK_A8));

    LONGS_EQUAL(0, ONE_NORTH(BITMASK_H8));
    LONGS_EQUAL(0, ONE_NORTH_EAST(BITMASK_H8));
    LONGS_EQUAL(0, ONE_EAST(BITMASK_H8));
}

