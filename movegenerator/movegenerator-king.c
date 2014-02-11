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

const bitboard WHITE_CASTLE_OO_EMPTY = BITMASK_F1 | BITMASK_G1;
const bitboard WHITE_CASTLE_OO_ATTACKS = BITMASK_E1 | BITMASK_F1 | BITMASK_G1;
const bitboard WHITE_CASTLE_OOO_EMPTY = BITMASK_B1 | BITMASK_C1 | BITMASK_D1;
const bitboard WHITE_CASTLE_OOO_ATTACKS = BITMASK_C1 | BITMASK_D1 | BITMASK_E1;

const bitboard BLACK_CASTLE_OO_EMPTY = BITMASK_F8 | BITMASK_G8;
const bitboard BLACK_CASTLE_OO_ATTACKS = BITMASK_E8 | BITMASK_F8 | BITMASK_G8;
const bitboard BLACK_CASTLE_OOO_EMPTY = BITMASK_B8 | BITMASK_C8 | BITMASK_D8;
const bitboard BLACK_CASTLE_OOO_ATTACKS = BITMASK_C8 | BITMASK_D8 | BITMASK_E8;


void initMovesGeneratorKing() {
   //for all fields
   for (int i = 0; i < 64; i++) {
       //put the piece on the board
       bitboard piece = BITMASK_SQUARE(i);

       //move all directions
       KING_MOVES[i] =
                       moveBitBoard0(piece,  1,  0) |
                       moveBitBoard0(piece,  1,  1) |
                       moveBitBoard0(piece,  0,  1) |
                       moveBitBoard0(piece, -1,  1) |
                       moveBitBoard0(piece, -1,  0) |
                       moveBitBoard0(piece, -1, -1) |
                       moveBitBoard0(piece,  0, -1) |
                       moveBitBoard0(piece,  1, -1)
       ;

   }
}

INLINE bitboard generateAttacksKing(const ChessBoard *board, const PieceColor color)
{
    bitboard piece = (color == WHITE) ? board->whiteKing : board->blackKing;
    if(piece == 0) return 0;
    return KING_MOVES[bitScan(piece)];
}


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
    //set up color
        if (board->nextMove == WHITE) {
            const bitboard king = board->whiteKing;
            if (!king) return;

            const int sourceIndex = bitScan(king);

            bitboard movesBoard = KING_MOVES[sourceIndex] & boardInfo->boardAvailable;

            //for all moves
            while (movesBoard) GENERATE_MOVE(moves, WHITE_KING, NO_PIECE, sourceIndex, bitPop(&movesBoard), 0);

            if (!board->castlingWhite) return;

            //if castling available
            if ((board->castlingWhite & KING_SIDE) && ((boardInfo->allPieces & WHITE_CASTLE_OO_EMPTY) == 0)) {
                //generate oponent attacks for castling on demand only
                if(isUnderAttack(board, BLACK, boardInfo->allPieces, WHITE_CASTLE_OO_ATTACKS) == 0) {
                    //add short castling move
                    GENERATE_MOVE(moves, WHITE_KING, NO_PIECE, sourceIndex, INDEX_G1, 0);
                }
            }
            if ((board->castlingWhite & QUEEN_SIDE) && ((boardInfo->allPieces & WHITE_CASTLE_OOO_EMPTY) == 0)) {
                if(isUnderAttack(board, BLACK, boardInfo->allPieces, WHITE_CASTLE_OOO_ATTACKS) == 0) {
                    //add long castling move
                    GENERATE_MOVE(moves, WHITE_KING, NO_PIECE, sourceIndex, INDEX_C1, 0);
                }
            }

        } else {
            const bitboard king = board->blackKing;
            if (!king) return;

            const int sourceIndex = bitScan(king);

            bitboard movesBoard = KING_MOVES[sourceIndex] & boardInfo->boardAvailable;

            //for all moves
            while (movesBoard) GENERATE_MOVE(moves, BLACK_KING, NO_PIECE, sourceIndex, bitPop(&movesBoard), 0);

            if (!board->castlingBlack) return;

            //if castling available
            if ((board->castlingBlack & KING_SIDE) && ((boardInfo->allPieces & BLACK_CASTLE_OO_EMPTY) == 0)) {
                //generate oponent attacks for castling on demand only
                if(isUnderAttack(board, WHITE, boardInfo->allPieces, BLACK_CASTLE_OO_ATTACKS) == 0) {
                //add short castling move
                    GENERATE_MOVE(moves, BLACK_KING, NO_PIECE, sourceIndex, INDEX_G8, 0);
                }
            }
            if ((board->castlingBlack & QUEEN_SIDE) && ((boardInfo->allPieces & BLACK_CASTLE_OOO_EMPTY) == 0)) {
                if(isUnderAttack(board, WHITE, boardInfo->allPieces, BLACK_CASTLE_OOO_ATTACKS) == 0) {
                    //add long castling move
                    GENERATE_MOVE(moves, BLACK_KING, NO_PIECE, sourceIndex, INDEX_C8, 0);
                }
            }
        }
}


