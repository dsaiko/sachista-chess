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
#include "movegenerator.h"

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


void generateMovesKing(const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo)
{
    const bitboard king = board->pieces[board->nextMove][KING];
    if (!king) return;

    const int sourceIndex = bitScan(king);
    bitboard movesBoard = KING_MOVES[sourceIndex] & boardInfo->boardAvailable;

    //for all moves
    while (movesBoard) GENERATE_MOVE(moves, KING, NO_PIECE, sourceIndex, bitPop(&movesBoard), 0);

    if (unlikely(board->castling[WHITE]) && board->nextMove == WHITE) {
        //if castling available
        if ((board->castling[WHITE] & KING_SIDE) && ((boardInfo->allPieces & WHITE_CASTLE_OO_EMPTY) == 0)) {
            //generate oponent attacks for castling on demand only
            if(isUnderAttack(board, BLACK, boardInfo->allPieces, WHITE_CASTLE_OO_ATTACKS) == 0) {
                //add short castling move
                GENERATE_MOVE(moves, KING, NO_PIECE, sourceIndex, INDEX_G1, 0);
            }
        }
        if ((board->castling[WHITE] & QUEEN_SIDE) && ((boardInfo->allPieces & WHITE_CASTLE_OOO_EMPTY) == 0)) {
            if(isUnderAttack(board, BLACK, boardInfo->allPieces, WHITE_CASTLE_OOO_ATTACKS) == 0) {
                //add long castling move
                GENERATE_MOVE(moves, KING, NO_PIECE, sourceIndex, INDEX_C1, 0);
            }
        }

    } else if(unlikely(board->castling[BLACK]) && board->nextMove == BLACK) {
        //if castling available
        if ((board->castling[BLACK] & KING_SIDE) && ((boardInfo->allPieces & BLACK_CASTLE_OO_EMPTY) == 0)) {
            //generate oponent attacks for castling on demand only
            if(isUnderAttack(board, WHITE, boardInfo->allPieces, BLACK_CASTLE_OO_ATTACKS) == 0) {
            //add short castling move
                GENERATE_MOVE(moves, KING, NO_PIECE, sourceIndex, INDEX_G8, 0);
            }
        }
        if ((board->castling[BLACK] & QUEEN_SIDE) && ((boardInfo->allPieces & BLACK_CASTLE_OOO_EMPTY) == 0)) {
            if(isUnderAttack(board, WHITE, boardInfo->allPieces, BLACK_CASTLE_OOO_ATTACKS) == 0) {
                //add long castling move
                GENERATE_MOVE(moves, KING, NO_PIECE, sourceIndex, INDEX_C8, 0);
            }
        }
    }
}


