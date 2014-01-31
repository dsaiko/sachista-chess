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

#ifndef SACHISTA_CHESS_PIECE_H
#define SACHISTA_CHESS_PIECE_H

#include "bitscan.h"

typedef enum Piece {
    NO_PIECE        = 0,
    WHITE_KING      = 1,
    WHITE_QUEEN     = 2,
    WHITE_BISHOP    = 3,
    WHITE_KNIGHT    = 4,
    WHITE_PAWN      = 5,
    WHITE_ROOK      = 6,
    BLACK_KING      = 7,
    BLACK_QUEEN     = 8,
    BLACK_BISHOP    = 9,
    BLACK_KNIGHT    = 10,
    BLACK_PAWN      = 11,
    BLACK_ROOK      = 12
} Piece;

typedef enum PieceColor {
    WHITE           = 0,
    BLACK           = 1
} PieceColor;

INLINE char PIECE2CHAR(Piece piece) {
    if(piece == WHITE_PAWN)      return  'P';
    if(piece == BLACK_PAWN)      return  'p';
    if(piece == WHITE_BISHOP)    return  'B';
    if(piece == WHITE_KNIGHT)    return  'N';
    if(piece == WHITE_ROOK)      return  'R';
    if(piece == BLACK_BISHOP)    return  'b';
    if(piece == BLACK_KNIGHT)    return  'n';
    if(piece == BLACK_ROOK)      return  'r';
    if(piece == WHITE_KING)      return  'K';
    if(piece == WHITE_QUEEN)     return  'Q';
    if(piece == BLACK_KING)      return  'k';
    if(piece == BLACK_QUEEN)     return  'q';
    return '-';
}

INLINE Piece CHAR2PIECE(char piece) {
    if(piece == 'P') return WHITE_PAWN;
    if(piece == 'p') return BLACK_PAWN;
    if(piece == 'B') return WHITE_BISHOP;
    if(piece == 'N') return WHITE_KNIGHT;
    if(piece == 'R') return WHITE_ROOK;
    if(piece == 'b') return BLACK_BISHOP;
    if(piece == 'n') return BLACK_KNIGHT;
    if(piece == 'r') return BLACK_ROOK;
    if(piece == 'K') return WHITE_KING;
    if(piece == 'Q') return WHITE_QUEEN;
    if(piece == 'k') return BLACK_KING;
    if(piece == 'q') return BLACK_QUEEN;
    return NO_PIECE;
}

#endif //SACHISTA_CHESS_PIECE_H

