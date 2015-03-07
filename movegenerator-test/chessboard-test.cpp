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

TEST_GROUP(ChessBoardTest)
{
};

TEST(ChessBoardTest, TestAssignments)
{
    ChessBoard board1;
    ChessBoard board2;

    CHECK(board1 == board2);

    board1.nextMove = Black;
    board1.halfMoveClock = 2;
    board1.castling[Black] = (Castling) (BothSides & ~QueenSide);
    board1.updateZobrist();

    CHECK(board1 != board2);
}

TEST(ChessBoardTest, TestStandardLayout)
{
    ChessBoard board;
    board.setupStandardBoard();

    CHECK(1 == BitBoard::popCount(board.pieces[White][King]));
    CHECK(1 == BitBoard::popCount(board.pieces[White][Queen]));
    CHECK(2 == BitBoard::popCount(board.pieces[White][Bishop]));
    CHECK(2 == BitBoard::popCount(board.pieces[White][Rook]));
    CHECK(2 == BitBoard::popCount(board.pieces[White][Knight]));
    CHECK(8 == BitBoard::popCount(board.pieces[White][Pawn]));

    CHECK(1 == BitBoard::popCount(board.pieces[Black][King]));
    CHECK(1 == BitBoard::popCount(board.pieces[Black][Queen]));
    CHECK(2 == BitBoard::popCount(board.pieces[Black][Bishop]));
    CHECK(2 == BitBoard::popCount(board.pieces[Black][Rook]));
    CHECK(2 == BitBoard::popCount(board.pieces[Black][Knight]));
    CHECK(8 == BitBoard::popCount(board.pieces[Black][Pawn]));

    CHECK(16 == BitBoard::popCount(board.whitePieces()));
    CHECK(16 == BitBoard::popCount(board.blackPieces()));
    CHECK(32 == BitBoard::popCount(board.allPieces()));
}

TEST(ChessBoardTest, TestFromFEN)
{
    ChessBoard defaultBoard;
    defaultBoard.setupStandardBoard();

    //incomplete FEN
    ChessBoard board("8/1K6/1Q6/8/5r2/4rk2/8/8 w - -");

    CHECK(board != defaultBoard);
    CHECK(5 == BitBoard::popCount(board.allPieces()));
    CHECK(White == board.nextMove);
    CHECK(0 == board.castling[White]);
    CHECK(0 == board.castling[Black]);
    CHECK(0 == board.enPassantTargetIndex);
    CHECK(0 == board.halfMoveClock);
    CHECK(1 == board.fullMoveNumber);

    board.setupFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQq a2 14 33");
    CHECK(32 == BitBoard::popCount(board.allPieces()));
    CHECK(Black == board.nextMove);
    CHECK(BothSides == board.castling[White]);
    CHECK(QueenSide == board.castling[Black]);
    CHECK(BoardIndex::A2 == board.enPassantTargetIndex);
    CHECK(14 == board.halfMoveClock);
    CHECK(33 == board.fullMoveNumber);

    board.setupFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    CHECK(board == defaultBoard);

    board.setupFEN("7B/6B1/5B2/4B3/3B4/2B5/1B6/B7 w - - 0 1");
    CHECK(BitMask::A1H8[7] == board.allPieces());

    board.setupFEN("XXXXX");
    CHECK(board.zobristKey == 0);

    board.setupStandardBoard();
    board.setupFEN("");
    CHECK(board.zobristKey == 0);

    board.setupStandardBoard();
    board.setupFEN("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaadasdasdasdasdasdasddddddddddddddddddd");
    CHECK(board.zobristKey == 0);

}

TEST(ChessBoardTest, TestToString)
{
    ChessBoard board("8/1K6/1Q6/8/5r2/4rk2/8/8 w - a2");
    CHECK(board.enPassantTargetIndex == BoardIndex::A2);

    std::cout << board.toFEN();

//    ChessBoard board2(board.toFEN());
//    CHECK(board == board2);
//
//    board2.setupString(board.toString());
//    CHECK(board != board2);
//
//    board2.enPassantTargetIndex = BoardIndex::A2;
//    board2.updateZobrist();
//    CHECK(board == board2);
//
//    board.setupStandardBoard();
//    board2.setupString(board.toString());
//    board.setupString(board.toString());
//
//    CHECK(board == board2);
//
//    board2.clearBoard();
//    board2.setupFEN(board.toFEN());
//    board.setupFEN(board.toFEN());
}
