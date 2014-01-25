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

#ifdef __cplusplus
extern "C"{
#endif

enum castling {
    KING_SIDE   = 1,
    QUEEN_SIDE  = 2,
    BOTH_SIDES  = KING_SIDE | QUEEN_SIDE
};

struct chessBoard {
    enum pieceColor nextMove;
    enum castling   castlingWhite;
    enum castling   castlingBlack;

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

    bitboard        enPassant;

};

#define MAX_MOVES_ARR_LENGTH    220

extern struct chessBoard emptyBoard;
extern struct chessBoard standardBoard;

#define WHITE_PIECES(b)     ((b)->whiteKing | (b)->whiteQueen | (b)->whiteRook | (b)->whiteKnight | (b)->whiteBishop | (b)->whitePawn)
#define BLACK_PIECES(b)     ((b)->blackKing | (b)->blackQueen | (b)->blackRook | (b)->blackKnight | (b)->blackBishop | (b)->blackPawn)
#define ALL_PIECES(b)       (WHITE_PIECES(b) | BLACK_PIECES(b))

extern int               boardCmp(const struct chessBoard *board1, const struct chessBoard *board2);

extern char*             board2str(const struct chessBoard *board, const int decorated, char *buffer, const int bufferSize);
extern struct chessBoard boardFromString(const char *buffer);
extern char*             board2fen(const struct chessBoard *board, char *buffer, const int bufferSize);
extern struct chessBoard boardFromFEN(const char *fen);


extern void initMovesGenerator();
extern void generateMoves(const struct chessBoard *board, struct move **m);


extern void makeMove(struct chessBoard *board0, const struct move *m);
extern int isLegal(const struct chessBoard *board);

extern unsigned long long perft(const struct chessBoard *board, const int depth);

#ifdef __cplusplus
}
#endif

#endif //SACHISTA_CHESS_BOARD_H

