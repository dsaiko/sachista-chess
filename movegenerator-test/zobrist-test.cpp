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

#include "chessboard.h"
#include "zobrist.h"
#include "move.h"

TEST_GROUP(ZobristTest)
{
};

TEST(ZobristTest, TestZobrist)
{
  ChessBoard board;

  Zobrist zobrist;
  CHECK(zobrist.getKey(board) == 0);

  board.setupStandardBoard();
  uint64_t keyStandard = zobrist.getKey(board);
  CHECK(keyStandard != 0);
  CHECK(keyStandard == board.zobristKey);

  //no halfmove counters are relevant
  board.halfMoveClock = 99;
  board.fullMoveNumber = 99;
  board.updateZobrist();
  CHECK(keyStandard == board.zobristKey);

  //next move color is relevant
  board.nextMove = Color::Black;
  board.updateZobrist();
  CHECK(board.zobristKey != 0);
  CHECK(board.zobristKey !=  keyStandard);
}

TEST(ZobristTest, HashCode)
{
    ChessBoard board("rnbqkb1r/pp1ppppp/7n/2p5/5P2/N1P5/PP1PP1PP/R1BQKBNR b KQkq - 0 3");
    ChessBoard board2("rnbqkb1r/pp1ppppp/2p4n/8/5P2/N1P5/PP1PP1PP/R1BQKBNR b KQkq - 0 3");

    CHECK(board.zobristKey != board2.zobristKey);

    board.setupFEN("rnbqkbnr/p1ppppp1/1p5B/8/3P4/8/PPP1PPPP/RN1QKBNR b KQkq - 0 3");
    board2.setupFEN("rnbqkbnr/p1ppBpp1/1p5p/8/3P4/8/PPP1PPPP/RN1QKBNR b KQkq - 0 3");
    CHECK(board.zobristKey != board2.zobristKey);

    //do 30 legal moves on the board
    board.setupStandardBoard();
    for(int n=0; n<100; n++) {
        auto moves = MoveGenerator::moves(board, ChessBoardStats(board));
        moves[0].applyTo(board);
    }

    //check the keys are the same as computed
    CHECK(board.zobristKey == ChessBoard::zobrist.getKey(board));
}



//TODO: test moves generation - zobrist uniquness - perft to some level
