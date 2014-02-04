/*
  sachista-chess copyright (C) 2014 Dusan Saiko

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

#ifndef SACHISTA_CHESS_BOARD_H
#define SACHISTA_CHESS_BOARD_H

#include "bitboard.h"
#include "chesspiece.h"
#include "move.h"
#include "version.h"
#include "bitscan.h"
#include "popcount.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum CastlingState {
    KING_SIDE   = 1,
    QUEEN_SIDE  = 2,
    BOTH_SIDES  = KING_SIDE | QUEEN_SIDE
} CastlingState;

typedef struct ChessBoard {
    PieceColor nextMove;
    CastlingState   castlingWhite;
    CastlingState   castlingBlack;

    int             halfMoveClock;
    int             fullMoveNumber;

    bitboard        whiteKing,
                    whiteQueen,
                    whiteRook,
                    whiteKnight,
                    whiteBishop,
                    whitePawn;

    bitboard        blackKing,
                    blackQueen,
                    blackRook,
                    blackKnight,
                    blackBishop,
                    blackPawn;

    int             enPassantIndex;

} ChessBoard;

typedef struct ChessBoardComputedInfo {
    bitboard        allPieces;
    bitboard        opponentPieces;
    bitboard        boardAvailable; //empty or opponent
} ChessBoardComputedInfo;

#define MAX_MOVES_ARR_LENGTH    220

extern const ChessBoard emptyBoard;
extern const ChessBoard standardBoard;

#define WHITE_PIECES(b)     ((b)->whiteKing | (b)->whiteQueen | (b)->whiteRook | (b)->whiteKnight | (b)->whiteBishop | (b)->whitePawn)
#define BLACK_PIECES(b)     ((b)->blackKing | (b)->blackQueen | (b)->blackRook | (b)->blackKnight | (b)->blackBishop | (b)->blackPawn)
#define ALL_PIECES(b)       (WHITE_PIECES(b) | BLACK_PIECES(b))

int         boardCmp(const ChessBoard *board1, const ChessBoard *board2);

char*       board2str(const ChessBoard *board, const int decorated, char *buffer, const int bufferSize);
ChessBoard  boardFromString(const char *buffer);
char*       board2fen(const ChessBoard *board, char *buffer, const int bufferSize);
ChessBoard  boardFromFEN(const char *fen);


void            initMovesGenerator();
int generateMoves(const ChessBoard *board, const ChessBoardComputedInfo *boardInfo, Move **moves);

void makeMove(ChessBoard *board0, const bitboard allPieces, const Move *m);

unsigned long long perft(const ChessBoard *board, const int depth);

INLINE ChessBoardComputedInfo computeInfo(const ChessBoard *board) {
    ChessBoardComputedInfo info;
    info.allPieces = ALL_PIECES(board);

    if(board->nextMove == WHITE) {
        info.opponentPieces =  BLACK_PIECES(board) ;
        info.boardAvailable =  ~WHITE_PIECES(board);
    } else {
        info.opponentPieces = WHITE_PIECES(board);
        info.boardAvailable = ~BLACK_PIECES(board);
    }

    return info;
}

#ifdef __cplusplus
}
#endif

#endif //SACHISTA_CHESS_BOARD_H

