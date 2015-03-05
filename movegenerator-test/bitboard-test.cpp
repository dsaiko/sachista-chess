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


#include <iostream>
#include <CppUTest/CommandLineTestRunner.h>
#include "bitboard.h"

TEST_GROUP(BitBoardTest)
{
};

TEST(BitBoardTest, Test64BitLong)
{
    bitmask b = 1;

    int size = 0;
    while (b != 0) {
        size++;
        b <<= 1;
    }

    LONGS_EQUAL(64, size);
}

TEST(BitBoardTest, TestUniverse)
{
    bitmask b = (bitmask) BitMask::UNIVERSE;

    int count = 0;
    while (b) {
        count++;
        b >>= 1;
    }

    LONGS_EQUAL(64, count);
}


TEST(BitBoardTest, TestOneEast)
{
    bitmask b = (bitmask) BitMask::A1; b = BitBoard::oneEast(b);
    LONGS_EQUAL(BitMask::B1, b); b = BitBoard::oneEast(b);
    LONGS_EQUAL(BitMask::C1, b); b = BitBoard::oneEast(b);
    LONGS_EQUAL(BitMask::D1, b); b = BitBoard::oneEast(b);
    LONGS_EQUAL(BitMask::E1, b); b = BitBoard::oneEast(b);
    LONGS_EQUAL(BitMask::F1, b); b = BitBoard::oneEast(b);
    LONGS_EQUAL(BitMask::G1, b); b = BitBoard::oneEast(b);
    LONGS_EQUAL(BitMask::H1, b); b = BitBoard::oneEast(b);
    LONGS_EQUAL(0, b);
}

TEST(BitBoardTest, TestOneWest)
{
    bitmask b = (bitmask) BitMask::H8; b = BitBoard::oneWest(b);
    LONGS_EQUAL(BitMask::G8, b); b = BitBoard::oneWest(b);
    LONGS_EQUAL(BitMask::F8, b); b = BitBoard::oneWest(b);
    LONGS_EQUAL(BitMask::E8, b); b = BitBoard::oneWest(b);
    LONGS_EQUAL(BitMask::D8, b); b = BitBoard::oneWest(b);
    LONGS_EQUAL(BitMask::C8, b); b = BitBoard::oneWest(b);
    LONGS_EQUAL(BitMask::B8, b); b = BitBoard::oneWest(b);
    LONGS_EQUAL(BitMask::A8, b); b = BitBoard::oneWest(b);
    LONGS_EQUAL(0, b);
}

TEST(BitBoardTest, TestOneSouth)
{
    bitmask b = (bitmask) BitMask::H8; b = BitBoard::oneSouth(b);
    LONGS_EQUAL(BitMask::H7, b); b = BitBoard::oneSouth(b);
    LONGS_EQUAL(BitMask::H6, b); b = BitBoard::oneSouth(b);
    LONGS_EQUAL(BitMask::H5, b); b = BitBoard::oneSouth(b);
    LONGS_EQUAL(BitMask::H4, b); b = BitBoard::oneSouth(b);
    LONGS_EQUAL(BitMask::H3, b); b = BitBoard::oneSouth(b);
    LONGS_EQUAL(BitMask::H2, b); b = BitBoard::oneSouth(b);
    LONGS_EQUAL(BitMask::H1, b); b = BitBoard::oneSouth(b);
    LONGS_EQUAL(0, b);
}

TEST(BitBoardTest, TestOneNorth)
{
    bitmask b = (bitmask) BitMask::A1; b = BitBoard::oneNorth(b);
    LONGS_EQUAL(BitMask::A2, b); b = BitBoard::oneNorth(b);
    LONGS_EQUAL(BitMask::A3, b); b = BitBoard::oneNorth(b);
    LONGS_EQUAL(BitMask::A4, b); b = BitBoard::oneNorth(b);
    LONGS_EQUAL(BitMask::A5, b); b = BitBoard::oneNorth(b);
    LONGS_EQUAL(BitMask::A6, b); b = BitBoard::oneNorth(b);
    LONGS_EQUAL(BitMask::A7, b); b = BitBoard::oneNorth(b);
    LONGS_EQUAL(BitMask::A8, b); b = BitBoard::oneNorth(b);
    LONGS_EQUAL(0, b);
}

TEST(BitBoardTest, TestOneNorthEast)
{
    bitmask b = (bitmask) BitMask::A1; b = BitBoard::oneNorthEast(b);
    LONGS_EQUAL(BitMask::B2, b); b = BitBoard::oneNorthEast(b);
    LONGS_EQUAL(BitMask::C3, b); b = BitBoard::oneNorthEast(b);
    LONGS_EQUAL(BitMask::D4, b); b = BitBoard::oneNorthEast(b);
    LONGS_EQUAL(BitMask::E5, b); b = BitBoard::oneNorthEast(b);
    LONGS_EQUAL(BitMask::F6, b); b = BitBoard::oneNorthEast(b);
    LONGS_EQUAL(BitMask::G7, b); b = BitBoard::oneNorthEast(b);
    LONGS_EQUAL(BitMask::H8, b); b = BitBoard::oneNorthEast(b);
    LONGS_EQUAL(0, b);

    b = (bitmask) BitMask::A8; b = BitBoard::oneNorthEast(b);
    LONGS_EQUAL(0, b);
}

TEST(BitBoardTest, TestOneSouthWest)
{
    bitmask b = (bitmask) BitMask::H8; b = BitBoard::oneSouthWest(b);
    LONGS_EQUAL(BitMask::G7, b); b = BitBoard::oneSouthWest(b);
    LONGS_EQUAL(BitMask::F6, b); b = BitBoard::oneSouthWest(b);
    LONGS_EQUAL(BitMask::E5, b); b = BitBoard::oneSouthWest(b);
    LONGS_EQUAL(BitMask::D4, b); b = BitBoard::oneSouthWest(b);
    LONGS_EQUAL(BitMask::C3, b); b = BitBoard::oneSouthWest(b);
    LONGS_EQUAL(BitMask::B2, b); b = BitBoard::oneSouthWest(b);
    LONGS_EQUAL(BitMask::A1, b); b = BitBoard::oneSouthWest(b);
    LONGS_EQUAL(0, b);

    b = (bitmask) BitMask::H1; b = BitBoard::oneSouthWest(b);
    LONGS_EQUAL(0, b);
}


TEST(BitBoardTest, TestOneSouthEast)
{
    bitmask b = (bitmask) BitMask::A8; b = BitBoard::oneSouthEast(b);
    LONGS_EQUAL(BitMask::B7, b); b = BitBoard::oneSouthEast(b);
    LONGS_EQUAL(BitMask::C6, b); b = BitBoard::oneSouthEast(b);
    LONGS_EQUAL(BitMask::D5, b); b = BitBoard::oneSouthEast(b);
    LONGS_EQUAL(BitMask::E4, b); b = BitBoard::oneSouthEast(b);
    LONGS_EQUAL(BitMask::F3, b); b = BitBoard::oneSouthEast(b);
    LONGS_EQUAL(BitMask::G2, b); b = BitBoard::oneSouthEast(b);
    LONGS_EQUAL(BitMask::H1, b); b = BitBoard::oneSouthEast(b);
    LONGS_EQUAL(0, b);

    b = (bitmask) BitMask::H8; b = BitBoard::oneSouthEast(b);
    LONGS_EQUAL(0, b);
}

TEST(BitBoardTest, TestOneNorthWest)
{
    bitmask b = (bitmask) BitMask::H1; b = BitBoard::oneNorthWest(b);
    LONGS_EQUAL(BitMask::G2, b); b = BitBoard::oneNorthWest(b);
    LONGS_EQUAL(BitMask::F3, b); b = BitBoard::oneNorthWest(b);
    LONGS_EQUAL(BitMask::E4, b); b = BitBoard::oneNorthWest(b);
    LONGS_EQUAL(BitMask::D5, b); b = BitBoard::oneNorthWest(b);
    LONGS_EQUAL(BitMask::C6, b); b = BitBoard::oneNorthWest(b);
    LONGS_EQUAL(BitMask::B7, b); b = BitBoard::oneNorthWest(b);
    LONGS_EQUAL(BitMask::A8, b); b = BitBoard::oneNorthWest(b);
    LONGS_EQUAL(0, b);

    b = (bitmask) BitMask::A1; b = BitBoard::oneSouthEast(b);
    LONGS_EQUAL(0, b);
}

TEST(BitBoardTest, TestRankFileIndex)
{
    LONGS_EQUAL(BitBoard::rankIndex(BoardIndex::A1), 0);
    LONGS_EQUAL(BitBoard::rankIndex(BoardIndex::B2), 1);
    LONGS_EQUAL(BitBoard::rankIndex(BoardIndex::C3), 2);
    LONGS_EQUAL(BitBoard::rankIndex(BoardIndex::D4), 3);
    LONGS_EQUAL(BitBoard::rankIndex(BoardIndex::E5), 4);
    LONGS_EQUAL(BitBoard::rankIndex(BoardIndex::F6), 5);
    LONGS_EQUAL(BitBoard::rankIndex(BoardIndex::G7), 6);
    LONGS_EQUAL(BitBoard::rankIndex(BoardIndex::H8), 7);


    LONGS_EQUAL(BitBoard::fileIndex(BoardIndex::A1), 0);
    LONGS_EQUAL(BitBoard::fileIndex(BoardIndex::B2), 1);
    LONGS_EQUAL(BitBoard::fileIndex(BoardIndex::C3), 2);
    LONGS_EQUAL(BitBoard::fileIndex(BoardIndex::D4), 3);
    LONGS_EQUAL(BitBoard::fileIndex(BoardIndex::E5), 4);
    LONGS_EQUAL(BitBoard::fileIndex(BoardIndex::F6), 5);
    LONGS_EQUAL(BitBoard::fileIndex(BoardIndex::G7), 6);
    LONGS_EQUAL(BitBoard::fileIndex(BoardIndex::H8), 7);
}

TEST(BitBoardTest, TestSquareBitmask)
{
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::A1), BitMask::A1);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::A2), BitMask::A2);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::A3), BitMask::A3);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::A4), BitMask::A4);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::A5), BitMask::A5);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::A6), BitMask::A6);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::A7), BitMask::A7);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::A8), BitMask::A8);

    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::B1), BitMask::B1);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::B2), BitMask::B2);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::B3), BitMask::B3);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::B4), BitMask::B4);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::B5), BitMask::B5);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::B6), BitMask::B6);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::B7), BitMask::B7);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::B8), BitMask::B8);

    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::C1), BitMask::C1);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::C2), BitMask::C2);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::C3), BitMask::C3);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::C4), BitMask::C4);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::C5), BitMask::C5);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::C6), BitMask::C6);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::C7), BitMask::C7);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::C8), BitMask::C8);

    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::D1), BitMask::D1);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::D2), BitMask::D2);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::D3), BitMask::D3);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::D4), BitMask::D4);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::D5), BitMask::D5);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::D6), BitMask::D6);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::D7), BitMask::D7);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::D8), BitMask::D8);

    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::E1), BitMask::E1);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::E2), BitMask::E2);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::E3), BitMask::E3);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::E4), BitMask::E4);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::E5), BitMask::E5);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::E6), BitMask::E6);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::E7), BitMask::E7);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::E8), BitMask::E8);

    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::F1), BitMask::F1);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::F2), BitMask::F2);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::F3), BitMask::F3);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::F4), BitMask::F4);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::F5), BitMask::F5);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::F6), BitMask::F6);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::F7), BitMask::F7);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::F8), BitMask::F8);

    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::G1), BitMask::G1);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::G2), BitMask::G2);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::G3), BitMask::G3);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::G4), BitMask::G4);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::G5), BitMask::G5);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::G6), BitMask::G6);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::G7), BitMask::G7);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::G8), BitMask::G8);

    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::H1), BitMask::H1);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::H2), BitMask::H2);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::H3), BitMask::H3);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::H4), BitMask::H4);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::H5), BitMask::H5);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::H6), BitMask::H6);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::H7), BitMask::H7);
    LONGS_EQUAL(BitBoard::squareBitmask(BoardIndex::H8), BitMask::H8);
}


TEST(BitBoardTest, TestReverseRanks)
{
    bitmask b = (bitmask) BitMask::FRAME;
    LONGS_EQUAL(b, BitBoard::reverseRanks(b));

    b = ~BitBoard::A1H8[7];

    bitmask b2 = BitBoard::reverseRanks(b);
    CHECK(b != b2);
    b2 = BitBoard::reverseRanks(b2);
    LONGS_EQUAL(b, b2);
}


TEST(BitBoardTest, TestFlipDiagA8H1)
{
    bitmask diag1 = ~BitBoard::A1H8[7];
    bitmask diag2 = ~BitBoard::A1H8[5];

    CHECK(BitBoard::flipDiagA1H8(diag1) == diag1);
    CHECK(BitBoard::flipDiagA1H8(diag2) != diag2);
    CHECK(BitBoard::flipDiagA1H8(BitBoard::flipDiagA1H8(diag2)) == diag2);
}


TEST(BitBoardTest, TestMirrorHorizontal)
{
    bitmask diag1 = (bitmask) BitMask::FRAME;
    bitmask diag2 = ~BitBoard::A1H8[7];

    CHECK(BitBoard::mirrorHorizontal(diag1) == diag1);
    CHECK(BitBoard::mirrorHorizontal(diag2) != diag2);
    CHECK(BitBoard::mirrorHorizontal(BitBoard::mirrorHorizontal(diag2)) == diag2);
}


TEST(BitBoardTest, TestNotation)
{
    CHECK(BitBoard::fromNotation("h5") == BitBoard::squareBitmask(BoardIndex::H5));
    CHECK(BitBoard::fieldNotation(BoardIndex::H5) == "h5");
}

TEST(BitBoardTest, TestRankArray)
{
    bitmask board = 0;
    for(int i=0; i<8; i++) {
        CHECK(board != (bitmask)BitMask::UNIVERSE);
        board |= BitBoard::RANK[i];
    }
    CHECK(board == (bitmask)BitMask::UNIVERSE);
}

TEST(BitBoardTest, TestFileArray)
{
    bitmask board = 0;
    for(int i=0; i<8; i++) {
        CHECK(board != (bitmask)BitMask::UNIVERSE);
        board |= BitBoard::FILE[i];
    }
    CHECK(board == (bitmask)BitMask::UNIVERSE);
}

TEST(BitBoardTest, TestA1H8Array)
{
    bitmask board = 0;
    for(int i=0; i<15; i++) {
        CHECK(board != (bitmask)BitMask::UNIVERSE);
        board |= BitBoard::A1H8[i];
    }
    CHECK(board == (bitmask)BitMask::UNIVERSE);
}

TEST(BitBoardTest, TestA8H1Array)
{
    bitmask board = 0;
    for(int i=0; i<15; i++) {
        CHECK(board != (bitmask)BitMask::UNIVERSE);
        board |= BitBoard::A8H1[i];
    }
    CHECK(board == (bitmask)BitMask::UNIVERSE);
}

//TEST(BitBoardTest, TestLeastSignificantBit)
//{
//    const int i = bitScan(BITMASK_H2);
//    char notation[3];
//
//    fieldNotation(i, notation, sizeof(notation)/sizeof(char));
//
//    STRCMP_EQUAL("h2", notation);
//}

//
//TEST(BitBoardTest, TestBitCount)
//{
//    LONGS_EQUAL(28, popCount(BITMASK_FRAME));
//    LONGS_EQUAL(64, popCount(BITMASK_UNIVERSE));
//    LONGS_EQUAL(0, popCount(~BITMASK_UNIVERSE));
//
//    LONGS_EQUAL(BITMASK_FILE_A, BITMASK_FILE[0]);
//    LONGS_EQUAL(BITMASK_FILE_H, BITMASK_FILE[7]);
//
//    LONGS_EQUAL(BITMASK_RANK_1, BITMASK_RANK[0]);
//    LONGS_EQUAL(BITMASK_RANK_8, BITMASK_RANK[7]);
//
//    LONGS_EQUAL(BITMASK_UNIVERSE, BITMASK_FILE[0] | BITMASK_FILE[1] | BITMASK_FILE[2] | BITMASK_FILE[3] | BITMASK_FILE[4] | BITMASK_FILE[5] | BITMASK_FILE[6] | BITMASK_FILE[7] );
//    LONGS_EQUAL(BITMASK_UNIVERSE, BITMASK_RANK[0] | BITMASK_RANK[1] | BITMASK_RANK[2] | BITMASK_RANK[3] | BITMASK_RANK[4] | BITMASK_RANK[5] | BITMASK_RANK[6] | BITMASK_RANK[7] );
//
//    LONGS_EQUAL(BITMASK_UNIVERSE, BITMASK_A1H8[0] | BITMASK_A1H8[1] | BITMASK_A1H8[2] | BITMASK_A1H8[3] | BITMASK_A1H8[4] | BITMASK_A1H8[5] | BITMASK_A1H8[6] | BITMASK_A1H8[7] | BITMASK_A1H8[8] | BITMASK_A1H8[9] | BITMASK_A1H8[10] | BITMASK_A1H8[11] | BITMASK_A1H8[12] | BITMASK_A1H8[13] | BITMASK_A1H8[14]);
//    LONGS_EQUAL(BITMASK_UNIVERSE, BITMASK_A8H1[0] | BITMASK_A8H1[1] | BITMASK_A8H1[2] | BITMASK_A8H1[3] | BITMASK_A8H1[4] | BITMASK_A8H1[5] | BITMASK_A8H1[6] | BITMASK_A8H1[7] | BITMASK_A8H1[8] | BITMASK_A8H1[9] | BITMASK_A8H1[10] | BITMASK_A8H1[11] | BITMASK_A8H1[12] | BITMASK_A8H1[13] | BITMASK_A8H1[14]);
//
//}

//
//TEST(BitBoardTest, TestIndexes)
//{
//    for(int i=0; i<64; i++) {
//        bitboard b = BITMASK_SQUARE(i);
//
//        LONGS_EQUAL((1ULL << i), b);
//        LONGS_EQUAL(1, popCount(b));
//    }
//}

//TEST(BitBoardTest, TestBasicOperations)
//{
//    LONGS_EQUAL(13, popCount(ONE_NORTH_EAST(BITMASK_FRAME)));
//    LONGS_EQUAL(13, popCount(ONE_SOUTH_WEST(BITMASK_FRAME)));
//
//    bitboard b = flipDiagA1H8(BITMASK_A1 | BITMASK_H1 | BITMASK_H8);
//    LONGS_EQUAL(BITMASK_A1 | BITMASK_A8 | BITMASK_H8, b);
//    LONGS_EQUAL(BITMASK_FILE[1], mirrorHorizontal(BITMASK_FILE[6]));
//
//    LONGS_EQUAL(BITMASK_A8, ONE_NORTH(BITMASK_A7));
//    LONGS_EQUAL(BITMASK_A7, ONE_SOUTH(BITMASK_A8));
//    LONGS_EQUAL(BITMASK_B7, ONE_EAST(BITMASK_A7));
//    LONGS_EQUAL(BITMASK_B7, ONE_WEST(BITMASK_C7));
//
//    LONGS_EQUAL(BITMASK_A3, ONE_NORTH_WEST(BITMASK_B2));
//    LONGS_EQUAL(BITMASK_C3, ONE_NORTH_EAST(BITMASK_B2));
//    LONGS_EQUAL(BITMASK_C1, ONE_SOUTH_EAST(BITMASK_B2));
//    LONGS_EQUAL(BITMASK_A1, ONE_SOUTH_WEST(BITMASK_B2));
//
//    LONGS_EQUAL(0, ONE_NORTH(BITMASK_A8));
//    LONGS_EQUAL(0, ONE_NORTH_WEST(BITMASK_A8));
//    LONGS_EQUAL(0, ONE_WEST(BITMASK_A8));
//
//    LONGS_EQUAL(0, ONE_NORTH(BITMASK_H8));
//    LONGS_EQUAL(0, ONE_NORTH_EAST(BITMASK_H8));
//    LONGS_EQUAL(0, ONE_EAST(BITMASK_H8));
//}
//
