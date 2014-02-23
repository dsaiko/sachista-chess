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


void testMoves(const int expectedCount, const char *boardString)
{
    ChessBoard board = boardFromString(boardString);
    Move moves[256];
    Move *pointer = moves;

    ChessBoardComputedInfo boardInfo = computeInfo(&board);
    generateMoves(&board, &boardInfo, &pointer);

    int size = pointer - moves;
    LONGS_EQUAL(expectedCount, size);
}

void testMovesFromFen(const int expectedCount, const char *boardString)
{
    ChessBoard board = boardFromFEN(boardString);
    Move moves[256];
    Move *pointer = moves;

    ChessBoardComputedInfo boardInfo = computeInfo(&board);
    generateMoves(&board, &boardInfo, &pointer);

    int size = pointer - moves;
    LONGS_EQUAL(expectedCount, size);
}

void testValidMoves(const int expectedCount, const char *boardString)
{

    ChessBoard board = boardFromString(boardString);
    int validCount = perft(&board, 1);

    LONGS_EQUAL(expectedCount, validCount);
}


TEST_GROUP(MovesGenerator)
{
};

TEST(MovesGenerator, HashCode)
{
    ChessBoard board = boardFromFEN("rnbqkb1r/pp1ppppp/7n/2p5/5P2/N1P5/PP1PP1PP/R1BQKBNR b KQkq - 0 3");
    ChessBoard board2 = boardFromFEN("rnbqkb1r/pp1ppppp/2p4n/8/5P2/N1P5/PP1PP1PP/R1BQKBNR b KQkq - 0 3");

    uint64_t key1 = zobristKey(&board);
    uint64_t key2 = zobristKey(&board2);
    CHECK_FALSE(key1 == key2);

    board = boardFromFEN("rnbqkbnr/p1ppppp1/1p5B/8/3P4/8/PPP1PPPP/RN1QKBNR b KQkq - 0 3");
    board2 = boardFromFEN("rnbqkbnr/p1ppBpp1/1p5p/8/3P4/8/PPP1PPPP/RN1QKBNR b KQkq - 0 3");

    key1 = zobristKey(&board);
    key2 = zobristKey(&board2);
    CHECK_FALSE(key1 == key2);
}

TEST(MovesGenerator, PerfT)
{
    ChessBoard board = standardBoard;
    LONGS_EQUAL(197281, perft(&board, 4));

    board = boardFromFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    LONGS_EQUAL(2039, perft(&board, 2));
    LONGS_EQUAL(97862, perft(&board, 3));
    LONGS_EQUAL(4085603, perft(&board, 4));
    LONGS_EQUAL(193690690, perft(&board, 5));

    board = boardFromFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
    LONGS_EQUAL(43238, perft(&board, 4));

    board = boardFromFEN("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    LONGS_EQUAL(264, perft(&board, 2));
    LONGS_EQUAL(9467, perft(&board, 3));
    LONGS_EQUAL(422333, perft(&board, 4));
    LONGS_EQUAL(15833292, perft(&board, 5));

    board = boardFromFEN("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1");
    LONGS_EQUAL(422333, perft(&board, 4));

    board = boardFromFEN("rnbqkb1r/pp1p1ppp/2p5/4P3/2B5/8/PPP1NnPP/RNBQK2R w KQkq - 0 6");
    LONGS_EQUAL(53392, perft(&board, 3));

    board = boardFromFEN("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
    LONGS_EQUAL(164075551, perft(&board, 5));
}

