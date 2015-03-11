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

    CHECK(64 == size);
}

TEST(BitBoardTest, TestUniverse)
{
    bitmask b =  BitMask::UNIVERSE;

    int count = 0;
    while (b) {
        count++;
        b >>= 1;
    }

    CHECK(64 == count);
}


TEST(BitBoardTest, TestOneEast)
{
    bitmask b =  BitMask::A1; b = BitBoard::oneEast(b);
    CHECK(BitMask::B1 == b); b = BitBoard::oneEast(b);
    CHECK(BitMask::C1 == b); b = BitBoard::oneEast(b);
    CHECK(BitMask::D1 == b); b = BitBoard::oneEast(b);
    CHECK(BitMask::E1 == b); b = BitBoard::oneEast(b);
    CHECK(BitMask::F1 == b); b = BitBoard::oneEast(b);
    CHECK(BitMask::G1 == b); b = BitBoard::oneEast(b);
    CHECK(BitMask::H1 == b); b = BitBoard::oneEast(b);
    CHECK(0 == b);
}

TEST(BitBoardTest, TestOneWest)
{
    bitmask b =  BitMask::H8; b = BitBoard::oneWest(b);
    CHECK(BitMask::G8 == b); b = BitBoard::oneWest(b);
    CHECK(BitMask::F8 == b); b = BitBoard::oneWest(b);
    CHECK(BitMask::E8 == b); b = BitBoard::oneWest(b);
    CHECK(BitMask::D8 == b); b = BitBoard::oneWest(b);
    CHECK(BitMask::C8 == b); b = BitBoard::oneWest(b);
    CHECK(BitMask::B8 == b); b = BitBoard::oneWest(b);
    CHECK(BitMask::A8 == b); b = BitBoard::oneWest(b);
    CHECK(0 == b);
}

TEST(BitBoardTest, TestOneSouth)
{
    bitmask b =  BitMask::H8; b = BitBoard::oneSouth(b);
    CHECK(BitMask::H7 == b); b = BitBoard::oneSouth(b);
    CHECK(BitMask::H6 == b); b = BitBoard::oneSouth(b);
    CHECK(BitMask::H5 == b); b = BitBoard::oneSouth(b);
    CHECK(BitMask::H4 == b); b = BitBoard::oneSouth(b);
    CHECK(BitMask::H3 == b); b = BitBoard::oneSouth(b);
    CHECK(BitMask::H2 == b); b = BitBoard::oneSouth(b);
    CHECK(BitMask::H1 == b); b = BitBoard::oneSouth(b);
    CHECK(0 == b);
}

TEST(BitBoardTest, TestOneNorth)
{
    bitmask b =  BitMask::A1; b = BitBoard::oneNorth(b);
    CHECK(BitMask::A2 == b); b = BitBoard::oneNorth(b);
    CHECK(BitMask::A3 == b); b = BitBoard::oneNorth(b);
    CHECK(BitMask::A4 == b); b = BitBoard::oneNorth(b);
    CHECK(BitMask::A5 == b); b = BitBoard::oneNorth(b);
    CHECK(BitMask::A6 == b); b = BitBoard::oneNorth(b);
    CHECK(BitMask::A7 == b); b = BitBoard::oneNorth(b);
    CHECK(BitMask::A8 == b); b = BitBoard::oneNorth(b);
    CHECK(0 == b);
}

TEST(BitBoardTest, TestOneNorthEast)
{
    bitmask b =  BitMask::A1; b = BitBoard::oneNorthEast(b);
    CHECK(BitMask::B2 == b); b = BitBoard::oneNorthEast(b);
    CHECK(BitMask::C3 == b); b = BitBoard::oneNorthEast(b);
    CHECK(BitMask::D4 == b); b = BitBoard::oneNorthEast(b);
    CHECK(BitMask::E5 == b); b = BitBoard::oneNorthEast(b);
    CHECK(BitMask::F6 == b); b = BitBoard::oneNorthEast(b);
    CHECK(BitMask::G7 == b); b = BitBoard::oneNorthEast(b);
    CHECK(BitMask::H8 == b); b = BitBoard::oneNorthEast(b);
    CHECK(0 == b);

    b =  BitMask::A8; b = BitBoard::oneNorthEast(b);
    CHECK(0 == b);
}

TEST(BitBoardTest, TestOneSouthWest)
{
    bitmask b =  BitMask::H8; b = BitBoard::oneSouthWest(b);
    CHECK(BitMask::G7 == b); b = BitBoard::oneSouthWest(b);
    CHECK(BitMask::F6 == b); b = BitBoard::oneSouthWest(b);
    CHECK(BitMask::E5 == b); b = BitBoard::oneSouthWest(b);
    CHECK(BitMask::D4 == b); b = BitBoard::oneSouthWest(b);
    CHECK(BitMask::C3 == b); b = BitBoard::oneSouthWest(b);
    CHECK(BitMask::B2 == b); b = BitBoard::oneSouthWest(b);
    CHECK(BitMask::A1 == b); b = BitBoard::oneSouthWest(b);
    CHECK(0 == b);

    b =  BitMask::H1; b = BitBoard::oneSouthWest(b);
    CHECK(0 == b);
}


TEST(BitBoardTest, TestOneSouthEast)
{
    bitmask b =  BitMask::A8; b = BitBoard::oneSouthEast(b);
    CHECK(BitMask::B7 == b); b = BitBoard::oneSouthEast(b);
    CHECK(BitMask::C6 == b); b = BitBoard::oneSouthEast(b);
    CHECK(BitMask::D5 == b); b = BitBoard::oneSouthEast(b);
    CHECK(BitMask::E4 == b); b = BitBoard::oneSouthEast(b);
    CHECK(BitMask::F3 == b); b = BitBoard::oneSouthEast(b);
    CHECK(BitMask::G2 == b); b = BitBoard::oneSouthEast(b);
    CHECK(BitMask::H1 == b); b = BitBoard::oneSouthEast(b);
    CHECK(0 == b);

    b =  BitMask::H8; b = BitBoard::oneSouthEast(b);
    CHECK(0 == b);
}

TEST(BitBoardTest, TestOneNorthWest)
{
    bitmask b =  BitMask::H1; b = BitBoard::oneNorthWest(b);
    CHECK(BitMask::G2 == b); b = BitBoard::oneNorthWest(b);
    CHECK(BitMask::F3 == b); b = BitBoard::oneNorthWest(b);
    CHECK(BitMask::E4 == b); b = BitBoard::oneNorthWest(b);
    CHECK(BitMask::D5 == b); b = BitBoard::oneNorthWest(b);
    CHECK(BitMask::C6 == b); b = BitBoard::oneNorthWest(b);
    CHECK(BitMask::B7 == b); b = BitBoard::oneNorthWest(b);
    CHECK(BitMask::A8 == b); b = BitBoard::oneNorthWest(b);
    CHECK(0 == b);

    b =  BitMask::A1; b = BitBoard::oneSouthEast(b);
    CHECK(0 == b);
}

TEST(BitBoardTest, TestRankFileIndex)
{
    CHECK(BitBoard::rankIndex(BoardIndex::A1) == 0);
    CHECK(BitBoard::rankIndex(BoardIndex::B2) == 1);
    CHECK(BitBoard::rankIndex(BoardIndex::C3) == 2);
    CHECK(BitBoard::rankIndex(BoardIndex::D4) == 3);
    CHECK(BitBoard::rankIndex(BoardIndex::E5) == 4);
    CHECK(BitBoard::rankIndex(BoardIndex::F6) == 5);
    CHECK(BitBoard::rankIndex(BoardIndex::G7) == 6);
    CHECK(BitBoard::rankIndex(BoardIndex::H8) == 7);


    CHECK(BitBoard::fileIndex(BoardIndex::A1) == 0);
    CHECK(BitBoard::fileIndex(BoardIndex::B2) == 1);
    CHECK(BitBoard::fileIndex(BoardIndex::C3) == 2);
    CHECK(BitBoard::fileIndex(BoardIndex::D4) == 3);
    CHECK(BitBoard::fileIndex(BoardIndex::E5) == 4);
    CHECK(BitBoard::fileIndex(BoardIndex::F6) == 5);
    CHECK(BitBoard::fileIndex(BoardIndex::G7) == 6);
    CHECK(BitBoard::fileIndex(BoardIndex::H8) == 7);
}

TEST(BitBoardTest, TestSquareBitmask)
{
    CHECK(BitBoard::squareBitmask(BoardIndex::A1) == BitMask::A1);
    CHECK(BitBoard::squareBitmask(BoardIndex::A2) == BitMask::A2);
    CHECK(BitBoard::squareBitmask(BoardIndex::A3) == BitMask::A3);
    CHECK(BitBoard::squareBitmask(BoardIndex::A4) == BitMask::A4);
    CHECK(BitBoard::squareBitmask(BoardIndex::A5) == BitMask::A5);
    CHECK(BitBoard::squareBitmask(BoardIndex::A6) == BitMask::A6);
    CHECK(BitBoard::squareBitmask(BoardIndex::A7) == BitMask::A7);
    CHECK(BitBoard::squareBitmask(BoardIndex::A8) == BitMask::A8);

    CHECK(BitBoard::squareBitmask(BoardIndex::B1) == BitMask::B1);
    CHECK(BitBoard::squareBitmask(BoardIndex::B2) == BitMask::B2);
    CHECK(BitBoard::squareBitmask(BoardIndex::B3) == BitMask::B3);
    CHECK(BitBoard::squareBitmask(BoardIndex::B4) == BitMask::B4);
    CHECK(BitBoard::squareBitmask(BoardIndex::B5) == BitMask::B5);
    CHECK(BitBoard::squareBitmask(BoardIndex::B6) == BitMask::B6);
    CHECK(BitBoard::squareBitmask(BoardIndex::B7) == BitMask::B7);
    CHECK(BitBoard::squareBitmask(BoardIndex::B8) == BitMask::B8);

    CHECK(BitBoard::squareBitmask(BoardIndex::C1) == BitMask::C1);
    CHECK(BitBoard::squareBitmask(BoardIndex::C2) == BitMask::C2);
    CHECK(BitBoard::squareBitmask(BoardIndex::C3) == BitMask::C3);
    CHECK(BitBoard::squareBitmask(BoardIndex::C4) == BitMask::C4);
    CHECK(BitBoard::squareBitmask(BoardIndex::C5) == BitMask::C5);
    CHECK(BitBoard::squareBitmask(BoardIndex::C6) == BitMask::C6);
    CHECK(BitBoard::squareBitmask(BoardIndex::C7) == BitMask::C7);
    CHECK(BitBoard::squareBitmask(BoardIndex::C8) == BitMask::C8);

    CHECK(BitBoard::squareBitmask(BoardIndex::D1) == BitMask::D1);
    CHECK(BitBoard::squareBitmask(BoardIndex::D2) == BitMask::D2);
    CHECK(BitBoard::squareBitmask(BoardIndex::D3) == BitMask::D3);
    CHECK(BitBoard::squareBitmask(BoardIndex::D4) == BitMask::D4);
    CHECK(BitBoard::squareBitmask(BoardIndex::D5) == BitMask::D5);
    CHECK(BitBoard::squareBitmask(BoardIndex::D6) == BitMask::D6);
    CHECK(BitBoard::squareBitmask(BoardIndex::D7) == BitMask::D7);
    CHECK(BitBoard::squareBitmask(BoardIndex::D8) == BitMask::D8);

    CHECK(BitBoard::squareBitmask(BoardIndex::E1) == BitMask::E1);
    CHECK(BitBoard::squareBitmask(BoardIndex::E2) == BitMask::E2);
    CHECK(BitBoard::squareBitmask(BoardIndex::E3) == BitMask::E3);
    CHECK(BitBoard::squareBitmask(BoardIndex::E4) == BitMask::E4);
    CHECK(BitBoard::squareBitmask(BoardIndex::E5) == BitMask::E5);
    CHECK(BitBoard::squareBitmask(BoardIndex::E6) == BitMask::E6);
    CHECK(BitBoard::squareBitmask(BoardIndex::E7) == BitMask::E7);
    CHECK(BitBoard::squareBitmask(BoardIndex::E8) == BitMask::E8);

    CHECK(BitBoard::squareBitmask(BoardIndex::F1) == BitMask::F1);
    CHECK(BitBoard::squareBitmask(BoardIndex::F2) == BitMask::F2);
    CHECK(BitBoard::squareBitmask(BoardIndex::F3) == BitMask::F3);
    CHECK(BitBoard::squareBitmask(BoardIndex::F4) == BitMask::F4);
    CHECK(BitBoard::squareBitmask(BoardIndex::F5) == BitMask::F5);
    CHECK(BitBoard::squareBitmask(BoardIndex::F6) == BitMask::F6);
    CHECK(BitBoard::squareBitmask(BoardIndex::F7) == BitMask::F7);
    CHECK(BitBoard::squareBitmask(BoardIndex::F8) == BitMask::F8);

    CHECK(BitBoard::squareBitmask(BoardIndex::G1) == BitMask::G1);
    CHECK(BitBoard::squareBitmask(BoardIndex::G2) == BitMask::G2);
    CHECK(BitBoard::squareBitmask(BoardIndex::G3) == BitMask::G3);
    CHECK(BitBoard::squareBitmask(BoardIndex::G4) == BitMask::G4);
    CHECK(BitBoard::squareBitmask(BoardIndex::G5) == BitMask::G5);
    CHECK(BitBoard::squareBitmask(BoardIndex::G6) == BitMask::G6);
    CHECK(BitBoard::squareBitmask(BoardIndex::G7) == BitMask::G7);
    CHECK(BitBoard::squareBitmask(BoardIndex::G8) == BitMask::G8);

    CHECK(BitBoard::squareBitmask(BoardIndex::H1) == BitMask::H1);
    CHECK(BitBoard::squareBitmask(BoardIndex::H2) == BitMask::H2);
    CHECK(BitBoard::squareBitmask(BoardIndex::H3) == BitMask::H3);
    CHECK(BitBoard::squareBitmask(BoardIndex::H4) == BitMask::H4);
    CHECK(BitBoard::squareBitmask(BoardIndex::H5) == BitMask::H5);
    CHECK(BitBoard::squareBitmask(BoardIndex::H6) == BitMask::H6);
    CHECK(BitBoard::squareBitmask(BoardIndex::H7) == BitMask::H7);
    CHECK(BitBoard::squareBitmask(BoardIndex::H8) == BitMask::H8);
}


TEST(BitBoardTest, TestReverseRanks)
{
    bitmask b =  BitMask::FRAME;
    CHECK(b == BitBoard::reverseRanks(b));

    b = ~BitMask::A1H8[7];

    bitmask b2 = BitBoard::reverseRanks(b);
    CHECK(b != b2);
    b2 = BitBoard::reverseRanks(b2);
    CHECK(b == b2);
}


TEST(BitBoardTest, TestFlipDiagA8H1)
{
    bitmask diag1 = ~BitMask::A1H8[7];
    bitmask diag2 = ~BitMask::A1H8[5];

    CHECK(BitBoard::flipDiagA1H8(diag1) == diag1);
    CHECK(BitBoard::flipDiagA1H8(diag2) != diag2);
    CHECK(BitBoard::flipDiagA1H8(BitBoard::flipDiagA1H8(diag2)) == diag2);


    bitmask b1 = BitMask::A1 | BitMask::H1 | BitMask::H8;
    bitmask b2 = BitMask::A1 | BitMask::A8 | BitMask::H8;

    CHECK(b2 = BitBoard::flipDiagA1H8(b1));
}


TEST(BitBoardTest, TestMirrorHorizontal)
{
    bitmask diag1 =  BitMask::FRAME;
    bitmask diag2 = ~BitMask::A1H8[7];

    CHECK(BitBoard::mirrorHorizontal(diag1) == diag1);
    CHECK(BitBoard::mirrorHorizontal(diag2) != diag2);
    CHECK(BitBoard::mirrorHorizontal(BitBoard::mirrorHorizontal(diag2)) == diag2);


    CHECK(BitMask::FILE[1] == BitBoard::mirrorHorizontal(BitMask::FILE[6]));
}


TEST(BitBoardTest, TestNotation)
{
    CHECK(BitBoard::bitmaskFromNotation("h5") == BitBoard::squareBitmask(BoardIndex::H5));
    CHECK(BitBoard::fieldNotation(BoardIndex::H5) == "h5");
}

TEST(BitBoardTest, TestRankArray)
{
    bitmask board = 0;
    for(int i=0; i<8; i++) {
        CHECK(board != BitMask::UNIVERSE);
        board |= BitMask::RANK[i];
    }
    CHECK(board == BitMask::UNIVERSE);
}

TEST(BitBoardTest, TestFileArray)
{
    bitmask board = 0;
    for(int i=0; i<8; i++) {
        CHECK(board != BitMask::UNIVERSE);
        board |= BitMask::FILE[i];
    }
    CHECK(board == BitMask::UNIVERSE);
}

TEST(BitBoardTest, TestA1H8Array)
{
    bitmask board = 0;
    for(int i=0; i<15; i++) {
        CHECK(board != BitMask::UNIVERSE);
        board |= BitMask::A1H8[i];
    }
    CHECK(board == BitMask::UNIVERSE);
}

TEST(BitBoardTest, TestA8H1Array)
{
    bitmask board = 0;
    for(int i=0; i<15; i++) {
        CHECK(board != BitMask::UNIVERSE);
        board |= BitMask::A8H1[i];
    }
    CHECK(board == BitMask::UNIVERSE);
}

TEST(BitBoardTest, TestConstantArrayts)
{
    CHECK(BitMask::FILE_A == BitMask::FILE[0]);
    CHECK(BitMask::FILE_H == BitMask::FILE[7]);

    CHECK(BitMask::RANK_1 == BitMask::RANK[0]);
    CHECK(BitMask::RANK_8 == BitMask::RANK[7]);
}



TEST(BitBoardTest, TestBitScan)
{
    int i = BitBoard::bitScan(BitMask::H2);
    auto notation = BitBoard::fieldNotation(i);

    CHECK("h2" == notation);

    bitmask b =  BitMask::H1 |  BitMask::A1;

    i = BitBoard::bitPop(b);
    CHECK((int)BoardIndex::A1 == i);
    CHECK( BitMask::H1 == b);

    CHECK(BitBoard::popCount(0) == 0)
}


TEST(BitBoardTest, TestPopCount)
{
    CHECK(28 == BitBoard::popCount( BitMask::FRAME));
    CHECK(64 == BitBoard::popCount( BitMask::UNIVERSE));
    CHECK(0 == BitBoard::popCount(~ BitMask::UNIVERSE));

    CHECK(13 == BitBoard::popCount(BitBoard::oneNorthEast(BitMask::FRAME)));
    CHECK(13 == BitBoard::popCount(BitBoard::oneSouthEast(BitMask::FRAME)));
}
