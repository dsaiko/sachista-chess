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
#include "chessboard.h"






void        generateMovesKing       (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);
void        generateMovesPawn       (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);
void        generateMovesRook       (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);
void        generateMovesBishop     (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);
void        generateMovesKnight     (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);


void GENERATE_MOVE(Move **moves, Piece piece, Piece promotionPiece, int sourceIndex, int targetIndex, int isEnPassant) {
    *((*moves)++) = (Move){(piece), (promotionPiece), (sourceIndex), (targetIndex), (isEnPassant)};
}
