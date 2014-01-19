#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"

TEST_GROUP(ChessBoardTest)
{
};

TEST(ChessBoardTest, TestAssignments)
{
    chessBoard board1 = emptyBoard;
    chessBoard board2 = emptyBoard;

    board1.nextMove = BLACK;
    board1.halfMoveClock = 2;
    board1.castlingBlack = (castling) (BOTH_SIDES & ~QUEEN_SIDE);

    board2.nextMove = WHITE;
    board2.halfMoveClock = 15;
    board2.castlingBlack = castling (BOTH_SIDES & ~KING_SIDE);

    CHECK_EQUAL(BLACK, board1.nextMove);
    CHECK_EQUAL(2, board1.halfMoveClock);
    CHECK_EQUAL(KING_SIDE, board1.castlingBlack);

    CHECK_EQUAL(WHITE, board2.nextMove);
    CHECK_EQUAL(15, board2.halfMoveClock);
    CHECK_EQUAL(QUEEN_SIDE, board2.castlingBlack);
}

TEST(ChessBoardTest, TestStandardLayout)
{
    chessBoard board = standardBoard;

    LONGS_EQUAL(1, popCount(board.whiteKing));
    LONGS_EQUAL(1, popCount(board.whiteQueen));
    LONGS_EQUAL(2, popCount(board.whiteBishop));
    LONGS_EQUAL(2, popCount(board.whiteRook));
    LONGS_EQUAL(2, popCount(board.whiteKnight));
    LONGS_EQUAL(8, popCount(board.whitePawn));

    LONGS_EQUAL(1, popCount(board.blackKing));
    LONGS_EQUAL(1, popCount(board.blackQueen));
    LONGS_EQUAL(2, popCount(board.blackBishop));
    LONGS_EQUAL(2, popCount(board.blackRook));
    LONGS_EQUAL(2, popCount(board.blackKnight));
    LONGS_EQUAL(8, popCount(board.blackPawn));

    LONGS_EQUAL(16, popCount(WHITE_PIECES(&board)));
    LONGS_EQUAL(16, popCount(BLACK_PIECES(&board)));
    LONGS_EQUAL(32, popCount(ALL_PIECES(&board)));

}



TEST(ChessBoardTest, TestFromFEN)
{
    //incomplete FEN
    chessBoard board = boardFromFEN("8/1K6/1Q6/8/5r2/4rk2/8/8 w - -");
    LONGS_EQUAL(5, popCount(ALL_PIECES(&board)));
    LONGS_EQUAL(WHITE, board.nextMove);
    LONGS_EQUAL(0, board.castlingWhite);
    LONGS_EQUAL(0, board.castlingBlack);
    LONGS_EQUAL(0, board.enPassant);
    LONGS_EQUAL(0, board.halfMoveClock);
    LONGS_EQUAL(1, board.fullMoveNumber);


    board = boardFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQq a2 14 33");
    LONGS_EQUAL(32, popCount(ALL_PIECES(&board)));
    LONGS_EQUAL(BLACK, board.nextMove);
    LONGS_EQUAL(BOTH_SIDES, board.castlingWhite);
    LONGS_EQUAL(QUEEN_SIDE, board.castlingBlack);
    LONGS_EQUAL(BITMASK_A2, board.enPassant);
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
    chessBoard board = boardFromFEN("8/1K6/1Q6/8/5r2/4rk2/8/8 w - a2");
    board2FEN(&board, buffer, sizeof(buffer) / sizeof(char));
    chessBoard board2 = boardFromFEN(buffer);
    LONGS_EQUAL(0, boardCmp(&board, &board2));

    board2String(&board, 1, buffer, sizeof(buffer) / sizeof(char));
    board2 = boardFromString(buffer);
    board2.enPassant = BITMASK_A2;
    LONGS_EQUAL(0, boardCmp(&board, &board2));

    board2String(&board, 0, buffer, sizeof(buffer) / sizeof(char));
    board2 = boardFromString(buffer);
    board2.enPassant = BITMASK_A2;
    LONGS_EQUAL(0, boardCmp(&board, &board2));


    board = standardBoard;
    board2FEN(&board, buffer, sizeof(buffer) / sizeof(char));
    board2 = boardFromFEN(buffer);
    LONGS_EQUAL(0, boardCmp(&board, &board2));

    board2String(&board, 1, buffer, sizeof(buffer) / sizeof(char));
    board2 = boardFromString(buffer);
    LONGS_EQUAL(0, boardCmp(&board, &board2));

    board2String(&board, 0, buffer, sizeof(buffer) / sizeof(char));
    board2 = boardFromString(buffer);
    LONGS_EQUAL(0, boardCmp(&board, &board2));
}
