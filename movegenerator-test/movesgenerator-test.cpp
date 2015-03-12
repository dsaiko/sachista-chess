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

#include <vector>
#include <CppUTest/CommandLineTestRunner.h>
#include <iostream>
#include "chessboard.h"
#include "move.h"
#include "movesgenerator-test.h"
#include "movearray.h"


void testMoves(const int expectedCount,  const ChessBoard &board)
{
    MoveArray moves;
    MoveGenerator::moves(board, ChessBoardStats(board), moves);
    LONGS_EQUAL(expectedCount, moves.size());
}

void testMovesFromString(const int expectedCount, std::string board)
{
    ChessBoard b;
    b.setupString(board);
    testMoves(expectedCount, b);
}

void testLegalMoves(const int expectedCount, const ChessBoard &board)
{
    uint64_t count = board.perft(1);
    if((int)count != expectedCount) {
        std::cout << "---------- BOARD:" << std::endl << board.toString() << std::endl;

        MoveArray moves;
        MoveGenerator::moves(board, ChessBoardStats(board), moves);
        for(int i=0; i<moves.size(); i++) {
            Move &m = moves.data[i];

            ChessBoard b = board;
            m.applyTo(b);
            if(MoveGenerator::isOpponentsKingNotUnderCheck(b, ChessBoardStats(b))) {
                std::cout << "---------- VALID MOVE:" << std::endl << b.toString() << std::endl;
            }
        }

        LONGS_EQUAL(expectedCount, count);
    }
}

void testLegalMovesFromString(const int expectedCount, std::string board)
{
    ChessBoard b;
    b.setupString(board);
    testLegalMoves(expectedCount, b);
}


TEST_GROUP(MovesGenerator)
{
};

TEST(MovesGenerator, BasicTest)
{
    ChessBoard b;
    b.setupStandardBoard();

    testMoves(20, b);
    testLegalMoves(20, b);
}

TEST(MovesGenerator, TestPiecePromotion) {
    MoveArray m;
    m.setNext(Pawn, BoardIndex::A1, BoardIndex::H8, false, false, King);

    CHECK("a1h8k" == m.first().toString());
    CHECK(m.size() == 1);
}

TEST(MovesGenerator, PerfT)
{
    ChessBoard board;
    board.setupStandardBoard();

    LONGS_EQUAL(197281, board.perft(4));

    board.setupFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    LONGS_EQUAL(2039,       board.perft(2));
    LONGS_EQUAL(97862,      board.perft(3));
    LONGS_EQUAL(4085603,    board.perft(4));
    LONGS_EQUAL(193690690,  board.perft(5));

    board.setupFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
    LONGS_EQUAL(43238,      board.perft(4));

    board.setupFEN("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    LONGS_EQUAL(264,        board.perft(2));
    LONGS_EQUAL(9467,       board.perft(3));
    LONGS_EQUAL(422333,     board.perft(4));
    LONGS_EQUAL(15833292,   board.perft(5));

    board.setupFEN("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1");
    LONGS_EQUAL(422333,     board.perft(4));

    board.setupFEN("rnbqkb1r/pp1p1ppp/2p5/4P3/2B5/8/PPP1NnPP/RNBQK2R w KQkq - 0 6");
    LONGS_EQUAL(53392,      board.perft(3));

    board.setupFEN("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
    LONGS_EQUAL(164075551,  board.perft(5));
}

