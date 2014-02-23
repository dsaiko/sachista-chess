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

TEST_GROUP(ChessBoardTest)
{
};

TEST(ChessBoardTest, TestAssignments)
{
    ChessBoard board1 = emptyBoard;
    ChessBoard board2 = emptyBoard;

    board1.nextMove = BLACK;
    board1.halfMoveClock = 2;
    board1.castling[BLACK] = (CastlingState) (BOTH_SIDES & ~QUEEN_SIDE);

    board2.nextMove = WHITE;
    board2.halfMoveClock = 15;
    board2.castling[BLACK] = (CastlingState) (BOTH_SIDES & ~KING_SIDE);

    CHECK_EQUAL(BLACK, board1.nextMove);
    CHECK_EQUAL(2, board1.halfMoveClock);
    CHECK_EQUAL(KING_SIDE, board1.castling[BLACK]);

    CHECK_EQUAL(WHITE, board2.nextMove);
    CHECK_EQUAL(15, board2.halfMoveClock);
    CHECK_EQUAL(QUEEN_SIDE, board2.castling[BLACK]);
}

TEST(ChessBoardTest, TestStandardLayout)
{
    ChessBoard board = standardBoard;

    LONGS_EQUAL(1, popCount(board.pieces[WHITE][KING]));
    LONGS_EQUAL(1, popCount(board.pieces[WHITE][QUEEN]));
    LONGS_EQUAL(2, popCount(board.pieces[WHITE][BISHOP]));
    LONGS_EQUAL(2, popCount(board.pieces[WHITE][ROOK]));
    LONGS_EQUAL(2, popCount(board.pieces[WHITE][KNIGHT]));
    LONGS_EQUAL(8, popCount(board.pieces[WHITE][PAWN]));

    LONGS_EQUAL(1, popCount(board.pieces[BLACK][KING]));
    LONGS_EQUAL(1, popCount(board.pieces[BLACK][QUEEN]));
    LONGS_EQUAL(2, popCount(board.pieces[BLACK][BISHOP]));
    LONGS_EQUAL(2, popCount(board.pieces[BLACK][ROOK]));
    LONGS_EQUAL(2, popCount(board.pieces[BLACK][KNIGHT]));
    LONGS_EQUAL(8, popCount(board.pieces[BLACK][PAWN]));

    LONGS_EQUAL(16, popCount(WHITE_PIECES(&board)));
    LONGS_EQUAL(16, popCount(BLACK_PIECES(&board)));
    LONGS_EQUAL(32, popCount(ALL_PIECES(&board)));

}



TEST(ChessBoardTest, TestFromFEN)
{
    //incomplete FEN
    ChessBoard board = boardFromFEN("8/1K6/1Q6/8/5r2/4rk2/8/8 w - -");
    LONGS_EQUAL(5, popCount(ALL_PIECES(&board)));
    LONGS_EQUAL(WHITE, board.nextMove);
    LONGS_EQUAL(0, board.castling[WHITE]);
    LONGS_EQUAL(0, board.castling[BLACK]);
    LONGS_EQUAL(0, board.enPassantTargetIndex);
    LONGS_EQUAL(0, board.halfMoveClock);
    LONGS_EQUAL(1, board.fullMoveNumber);

    board = boardFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQq a2 14 33");
    LONGS_EQUAL(32, popCount(ALL_PIECES(&board)));
    LONGS_EQUAL(BLACK, board.nextMove);
    LONGS_EQUAL(BOTH_SIDES, board.castling[WHITE]);
    LONGS_EQUAL(QUEEN_SIDE, board.castling[BLACK]);
    LONGS_EQUAL(INDEX_A2, board.enPassantTargetIndex);
    LONGS_EQUAL(14, board.halfMoveClock);
    LONGS_EQUAL(33, board.fullMoveNumber);

    board = boardFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    LONGS_EQUAL(0, boardCmp(&board, &standardBoard));

    board = boardFromFEN("7B/6B1/5B2/4B3/3B4/2B5/1B6/B7 w - - 0 1");
    LONGS_EQUAL(BITMASK_A1H8[7], ALL_PIECES(&board));

    board = boardFromFEN("INVALID");
    board = boardFromFEN("");
    board = boardFromFEN("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaadasdasdasdasdasdasddddddddddddddddddd");
}


TEST(ChessBoardTest, TestToString)
{
    char buffer[256];
    ChessBoard board = boardFromFEN("8/1K6/1Q6/8/5r2/4rk2/8/8 w - a2");
    board2fen(&board, buffer, sizeof(buffer) / sizeof(char));
    ChessBoard board2 = boardFromFEN(buffer);

    LONGS_EQUAL(0, boardCmp(&board, &board2));

    board2str(&board, 1, buffer, sizeof(buffer) / sizeof(char));
    board2 = boardFromString(buffer);
    board2.enPassantTargetIndex = INDEX_A2;
    LONGS_EQUAL(0, boardCmp(&board, &board2));

    board2str(&board, 0, buffer, sizeof(buffer) / sizeof(char));
    board2 = boardFromString(buffer);
    board2.enPassantTargetIndex = INDEX_A2;
    LONGS_EQUAL(0, boardCmp(&board, &board2));


    board = standardBoard;
    board2fen(&board, buffer, sizeof(buffer) / sizeof(char));
    board2 = boardFromFEN(buffer);
    LONGS_EQUAL(0, boardCmp(&board, &board2));

    board2str(&board, 1, buffer, sizeof(buffer) / sizeof(char));
    board2 = boardFromString(buffer);
    LONGS_EQUAL(0, boardCmp(&board, &board2));

    board2str(&board, 0, buffer, sizeof(buffer) / sizeof(char));
    board2 = boardFromString(buffer);
    LONGS_EQUAL(0, boardCmp(&board, &board2));
}
