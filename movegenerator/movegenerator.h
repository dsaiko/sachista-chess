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

#ifndef SACHISTA_CHESS_MOVEGENERATOR_H
#define SACHISTA_CHESS_MOVEGENERATOR_H

#include "chessboard.h"

#ifdef __cplusplus
extern "C"{
#endif

bitboard moveBitBoard0(bitboard b, const int up, const int right);


int MOVE_RANK_SHIFT[64];
bitboard MOVE_RANK_MASK[64];
bitboard MOVE_RANK_ATTACKS[64][64];
bitboard MOVE_FILE_MASK[64];
bitboard MOVE_FILE_MAGIC[64];
bitboard MOVE_FILE_ATTACKS[64][64];

bitboard MOVE_A1H8_MASK[64];
bitboard MOVE_A1H8_MAGIC[64];
bitboard MOVE_A8H1_MASK[64];
bitboard MOVE_A8H1_MAGIC[64];

bitboard MOVE_A1H8_ATTACKS[64][64];
bitboard MOVE_A8H1_ATTACKS[64][64];

bitboard KING_MOVES[64];
bitboard PAWN_MOVES[2][64];
bitboard PAWN_DOUBLE_MOVES[2][64];
bitboard PAWN_ATTACKS[2][64];
bitboard KNIGHT_MOVES[64];

void        initMovesGeneratorKing();
void        initMovesGeneratorRook();
void        initMovesGeneratorKnight();
void        initMovesGeneratorBishop();
void        initMovesGeneratorPawn();

bitboard    generateAttacksKing     (const ChessBoard *board, const Color color);
bitboard    generateAttacksPawn     (const ChessBoard *board, const Color color);
bitboard    generateAttacksKnight   (const ChessBoard *board, const Color color);
bitboard    generateAttacksRook     (const ChessBoard *board, const Color color, const bitboard allPieces);
bitboard    generateAttacksBishop   (const ChessBoard *board, const Color color, const bitboard allPieces);

void        generateMovesKing       (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);
void        generateMovesPawn       (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);
void        generateMovesRook       (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);
void        generateMovesBishop     (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);
void        generateMovesKnight     (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);


INLINE void GENERATE_MOVE(Move **moves, Piece piece, Piece promotionPiece, int sourceIndex, int targetIndex, int isEnPassant) {
    *((*moves)++) = (Move){(piece), (promotionPiece), (sourceIndex), (targetIndex), (isEnPassant)};
}

#ifdef __cplusplus
}
#endif

#endif //SACHISTA_CHESS_MOVEGENERATOR_H
