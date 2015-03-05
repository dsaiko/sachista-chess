#pragma once
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

#include <string>

#include "bitboard.h"
#include "version.h"
#include "zobrist.h"

enum Castling {
    None        = 0,
    KingSide    = 0b01,
    QueenSide   = 0b10,
    BothSides   = 0b11
};

enum Piece {
    NoPiece     = 0,
    King        = 1,
    Queen       = 2,
    Bishop      = 3,
    Knight      = 4,
    Rook        = 5,
    Pawn        = 6
};

enum Color {
    White       = 0,
    Black       = 1
};

class ChessBoard {

public:
    ChessBoard();

    Color       nextMove;
    Castling    castling[2];
    bitmask     pieces[2][7];
    int         halfMoveClock;
    int         fullMoveNumber;
    int         enPassantTargetIndex;

    //zobrist key is a hashcode of the beard (without halfMoveClock and fullMoveNumber info)
    uint64_t        zobristKey;

    void        clear();
    bool operator==(const ChessBoard &other);

    inline bitmask whitePieces() { return pieces[White][Queen] | pieces[White][King] | pieces[White][Rook] | pieces[White][Bishop] | pieces[White][Knight] | pieces[White][Pawn]; }
    inline bitmask blackPieces() { return pieces[Black][Queen] | pieces[Black][King] | pieces[Black][Rook] | pieces[Black][Bishop] | pieces[Black][Knight] | pieces[Black][Pawn]; }
    inline bitmask allPieces()   { return whitePieces() | blackPieces(); }


    std::string toString();
private:
    static const Zobrist zobrist;
};


//
//
//typedef struct ChessBoardComputedInfo {
//    bitboard        allPieces;
//    bitboard        opponentPieces;
//    bitboard        boardAvailable; //empty or opponent
//} ChessBoardComputedInfo;
//
//typedef struct Move {
//    Piece piece           ;
//    Piece promotionPiece  ;
//
//    unsigned int    sourceIndex     ;
//    unsigned int    targetIndex     ;
//
//    int             isEnPassant     ;
//} Move;
//
//#define MAX_MOVES_ARR_SIZE    220
//
//char*       board2str(const ChessBoard *board, const int decorated, char *buffer, const int bufferSize);
//ChessBoard  boardFromString(const char *buffer);
//char*       board2fen(const ChessBoard *board, char *buffer, const int bufferSize);
//ChessBoard  boardFromFEN(const char *fen);
//
//
//void        initMovesGenerator();
//INLINE void generateMoves(const ChessBoard *board, const ChessBoardComputedInfo *boardInfo, Move **moves);
//char *      move2str(const Move *m, char *buffer, const int bufferSize);
//void        makeMove(ChessBoard *board0, const bitboard allPieces, const Move *m);
//
//int         isNotUnderCheck(const ChessBoard *board, const Color nextMove);
//

//INLINE ChessBoardComputedInfo computeInfo(const ChessBoard *board) {
//    ChessBoardComputedInfo info;
//
//    info.allPieces = ALL_PIECES(board);
//
//    if(board->nextMove == WHITE) {
//        info.opponentPieces =  BLACK_PIECES(board) ;
//        info.boardAvailable =  ~WHITE_PIECES(board);
//    } else {
//        info.opponentPieces = WHITE_PIECES(board);
//        info.boardAvailable = ~BLACK_PIECES(board);
//    }
//
//    return info;
//}
//

//
//INLINE ChessBoard standardBoard() {
//    return boardFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
//}
