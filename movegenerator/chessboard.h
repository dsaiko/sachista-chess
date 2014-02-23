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

#ifndef SACHISTA_CHESS_BOARD_H
#define SACHISTA_CHESS_BOARD_H

#include "bitboard.h"
#include "version.h"
#include "bitscan.h"
#include "popcount.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum {
    NONE        = 0,
    KING_SIDE   = 0b01,
    QUEEN_SIDE  = 0b10,
    BOTH_SIDES  = 0b11
} CastlingState;

typedef enum {
    NO_PIECE        = 0,
    KING            = 1,
    QUEEN           = 2,
    BISHOP          = 3,
    KNIGHT          = 4,
    ROOK            = 5,
    PAWN            = 6
} Piece;

typedef enum {
    WHITE           = 0,
    BLACK           = 1
} Color;

typedef struct ChessBoard {
    Color           nextMove;

    CastlingState   castling[2];
    bitboard        pieces[2][7];

    int             halfMoveClock;
    int             fullMoveNumber;
    int             enPassantTargetIndex;

    //zobrist key is a hashcode of the beard (without halfMoveClock and fullMoveNumber info)
    uint64_t        zobristKey;
} ChessBoard;


typedef struct ChessBoardComputedInfo {
    bitboard        allPieces;
    bitboard        opponentPieces;
    bitboard        boardAvailable; //empty or opponent
} ChessBoardComputedInfo;

typedef struct Move {
    Piece piece           ;
    Piece promotionPiece  ;

    unsigned int    sourceIndex     ;
    unsigned int    targetIndex     ;

    int             isEnPassant     ;
} Move;

#define MAX_MOVES_ARR_SIZE    220

extern const ChessBoard emptyBoard;
extern ChessBoard       standardBoard;

int         boardCmp(const ChessBoard *board1, const ChessBoard *board2);

char*       board2str(const ChessBoard *board, const int decorated, char *buffer, const int bufferSize);
ChessBoard  boardFromString(const char *buffer);
char*       board2fen(const ChessBoard *board, char *buffer, const int bufferSize);
ChessBoard  boardFromFEN(const char *fen);


void        initMovesGenerator();
void        generateMoves(const ChessBoard *board, const ChessBoardComputedInfo *boardInfo, Move **moves);
char *      move2str(const Move *m, char *buffer, const int bufferSize);
void        makeMove(ChessBoard *board0, const bitboard allPieces, const Move *m);

uint64_t    perft(const ChessBoard *board, const int depth);
int         isNotUnderCheck(const ChessBoard *board, const Color nextMove);

INLINE bitboard WHITE_PIECES(const ChessBoard *board) {
    //no for loop for performance reasons
    return
            board->pieces[WHITE][QUEEN]     |
            board->pieces[WHITE][KING]      |
            board->pieces[WHITE][ROOK]      |
            board->pieces[WHITE][BISHOP]    |
            board->pieces[WHITE][KNIGHT]    |
            board->pieces[WHITE][PAWN]
    ;
}

INLINE bitboard BLACK_PIECES(const ChessBoard *board) {
    return
            board->pieces[BLACK][QUEEN]     |
            board->pieces[BLACK][KING]      |
            board->pieces[BLACK][ROOK]      |
            board->pieces[BLACK][BISHOP]    |
            board->pieces[BLACK][KNIGHT]    |
            board->pieces[BLACK][PAWN]
    ;
}

INLINE bitboard ALL_PIECES(const ChessBoard *board) {
    return WHITE_PIECES(board) | BLACK_PIECES(board);
}


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

uint64_t zobristKey(const ChessBoard *board);

#ifdef __cplusplus
}
#endif

#endif //SACHISTA_CHESS_BOARD_H

