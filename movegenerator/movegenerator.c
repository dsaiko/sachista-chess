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

#include "chessboard.h"
#include "movegenerator.h"
#include "zobrist.h"

extern void initZobrist();

void initMovesGenerator() {
    initZobrist();

    initMovesGeneratorKnight();
    initMovesGeneratorPawn();
    initMovesGeneratorKing();
    initMovesGeneratorBishop();
    initMovesGeneratorRook();
}

INLINE void generateMoves(const ChessBoard *board, const ChessBoardComputedInfo *boardInfo, Move **moves)
{  
    generateMovesKnight (board, moves, boardInfo);
    generateMovesPawn   (board, moves, boardInfo);
    generateMovesKing   (board, moves, boardInfo);
    generateMovesRook   (board, moves, boardInfo);
    generateMovesBishop (board, moves, boardInfo);
}

bitboard moveBitBoard0(bitboard b, const int up, const int right) {
    //move the piece up or down
    if (up > 0) {
        for(int i=0; i < up; i++)
            b = ONE_NORTH(b);
    } else if(up < 0) {
        for(int i=0; i < -up; i++)
            b = ONE_SOUTH(b);
    }

    //move the piece right or left
    if (right > 0) {
        for(int i=0; i < right; i++)
            b = ONE_EAST(b);
    } else if( right < 0){
        for(int i=0; i < -right; i++)
            b = ONE_WEST(b);
    }
    return b;
}


/**
  * Checks if bitmask is not under attack from pieces on board
  **/
INLINE int isUnderAttack(const ChessBoard *board, const char color, const bitboard allPieces, const bitboard bitmask) {

    bitboard attacks = generateAttacksRook(board, color, allPieces);
    if(attacks & bitmask) return 1;
    attacks  =  generateAttacksBishop(board, color, allPieces);
    if(attacks & bitmask) return 1;
    attacks  =  generateAttacksKnight(board, color);
    if(attacks & bitmask) return 1;
    attacks  =  generateAttacksPawn(board, color);
    if(attacks & bitmask) return 1;
    attacks  =  generateAttacksKing(board, color);
    if(attacks & bitmask) return 1;

    return 0;
}


int isNotUnderCheck(const ChessBoard *board, const Color nextMove) {

   const bitboard allPieces = ALL_PIECES(board);

   const Color opponentColor = nextMove == BLACK ? WHITE : BLACK;

   //check if my king is not under check by opponent pieces
   const bitboard king = board->pieces[opponentColor][KING];
   if(!king) return 0;
   int kingIndex = bitScan(king);

   const bitboard *pieces = (bitboard *) board->pieces[nextMove];

   if (pieces[PAWN]   & PAWN_ATTACKS[opponentColor][kingIndex]) return 0;
   if (pieces[KNIGHT] & KNIGHT_MOVES[kingIndex])                return 0;
   if (pieces[KING]   & KING_MOVES[kingIndex])                  return 0;

   const bitboard rooks   = pieces[QUEEN] | pieces[ROOK];
   if(rooks) {

       if (MOVE_RANK_ATTACKS[kingIndex][(int) (((allPieces & MOVE_RANK_MASK[kingIndex]) >> MOVE_RANK_SHIFT[kingIndex]))] & rooks)
           return 0;
       if (MOVE_FILE_ATTACKS[kingIndex][(int) (((allPieces & MOVE_FILE_MASK[kingIndex]) * MOVE_FILE_MAGIC[kingIndex]) >> 57)] & rooks)
           return 0;
   }

   const bitboard bishops = pieces[QUEEN] | pieces[BISHOP];
   if(bishops) {

       if (MOVE_A8H1_ATTACKS[kingIndex][(int) (((allPieces & MOVE_A8H1_MASK[kingIndex]) * MOVE_A8H1_MAGIC[kingIndex]) >> 57)] & bishops)
           return 0;
       if (MOVE_A1H8_ATTACKS[kingIndex][(int) (((allPieces & MOVE_A1H8_MASK[kingIndex]) * MOVE_A1H8_MAGIC[kingIndex]) >> 57)] & bishops)
           return 0;
   }

   return 1;
}
