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

void initMovesGeneratorPawn() {
    //for all fields
    for (int i = 0; i < 64; i++) {
     //put the piece on the board
     bitboard piece = BITMASK_SQUARE(i);

     //generate move
     WHITE_PAWN_MOVES[i]         = moveBitBoard0(piece, 1, 0);

     //generate move
     WHITE_PAWN_DOUBLE_MOVES[i]  = moveBitBoard0(piece, 2, 0);

     //generate attacks
     WHITE_PAWN_ATTACKS[i]       = moveBitBoard0(piece, 1, 1) | moveBitBoard0(piece, 1, -1);

     //generate move
     BLACK_PAWN_MOVES[i]         = moveBitBoard0(piece, -1, 0);

     //generate move
     BLACK_PAWN_DOUBLE_MOVES[i]  = moveBitBoard0(piece, -2, 0);

     //generate attacks
     BLACK_PAWN_ATTACKS[i]       = moveBitBoard0(piece, -1, 1) | moveBitBoard0(piece, -1, -1);

    }

}


INLINE bitboard generateAttacksPawn(const ChessBoard *board, const PieceColor color)
{
    if(color == WHITE) {
        return ONE_NORTH_EAST(board->whitePawn) | ONE_NORTH_WEST(board->whitePawn);
    } else {
        return ONE_SOUTH_EAST(board->blackPawn) | ONE_SOUTH_WEST(board->blackPawn);
    }
}


void generateMovesPawn(const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo)
{
    const bitboard emptyBoard = ~boardInfo->allPieces;

    if(board->nextMove == WHITE)
    {
        bitboard pieces = board->whitePawn;

        //while there are pieces
        while (pieces) {
            //get next piece
            const int sourceIndex = bitPop(&pieces);

            //get possible moves - moves minus my onw color
            //one step forward
            bitboard movesBoard = WHITE_PAWN_MOVES[sourceIndex] & emptyBoard;

            //if one step forward was sucessful and we are on base rank, try double move
            if ((movesBoard) && (sourceIndex < 16)) {
                movesBoard |=  ONE_NORTH(movesBoard) & emptyBoard;
            }

            //get attacks, only against oponent pieces
            const bitboard attacks = WHITE_PAWN_ATTACKS[sourceIndex];
            movesBoard |=  attacks & boardInfo->opponentPieces;

            //for all moves
            while (movesBoard) {
                //get next move
                const int targetIndex = bitPop(&movesBoard);

                //white promotion?
                if (targetIndex > 55) {
                    GENERATE_MOVE(moves, WHITE_PAWN, WHITE_BISHOP, sourceIndex, targetIndex, 0);
                    GENERATE_MOVE(moves, WHITE_PAWN, WHITE_KNIGHT, sourceIndex,  targetIndex, 0);
                    GENERATE_MOVE(moves, WHITE_PAWN, WHITE_QUEEN, sourceIndex, targetIndex, 0);
                    GENERATE_MOVE(moves, WHITE_PAWN, WHITE_ROOK,  sourceIndex, targetIndex, 0);
                } else {
                    //normal move/capture
                    GENERATE_MOVE(moves, WHITE_PAWN, NO_PIECE, sourceIndex, targetIndex, 0);
                }

            }

            //check enpassant capture
            if(board->enPassantIndex) {
                movesBoard = attacks & BITMASK_SQUARE(board->enPassantIndex);
                if (movesBoard) GENERATE_MOVE(moves, WHITE_PAWN, NO_PIECE, sourceIndex, bitScan(movesBoard), 1);
            }

        }
    } else {
        bitboard pieces = board->blackPawn;

        //while there are pieces
        while (pieces) {
            //get next piece
            const int sourceIndex = bitPop(&pieces);

            //get possible moves - moves minus my onw color
            //one step forward
            bitboard movesBoard = BLACK_PAWN_MOVES[sourceIndex] & emptyBoard;

            //if one step forward was sucessful and we are on base rank, try double move
            if ((movesBoard) && (sourceIndex > 47)) {
                movesBoard |=  ONE_SOUTH(movesBoard) & emptyBoard;
            }

            //get attacks, only against oponent pieces
            const bitboard attacks = BLACK_PAWN_ATTACKS[sourceIndex];
            movesBoard |=  attacks & boardInfo->opponentPieces;

            //for all moves
            while (movesBoard) {
                //get next move
                const int targetIndex = bitPop(&movesBoard);

                //white promotion?
                if (targetIndex < 8) {
                    GENERATE_MOVE(moves, BLACK_PAWN, BLACK_BISHOP, sourceIndex, targetIndex, 0);
                    GENERATE_MOVE(moves, BLACK_PAWN, BLACK_KNIGHT, sourceIndex, targetIndex, 0);
                    GENERATE_MOVE(moves, BLACK_PAWN, BLACK_QUEEN, sourceIndex, targetIndex, 0);
                    GENERATE_MOVE(moves, BLACK_PAWN, BLACK_ROOK, sourceIndex, targetIndex, 0);
                } else {
                    //normal move/capture
                    GENERATE_MOVE(moves, BLACK_PAWN, NO_PIECE,  sourceIndex, targetIndex, 0);
                }
            }

            //check enpassant capture
            if(board->enPassantIndex) {
                movesBoard = attacks & BITMASK_SQUARE(board->enPassantIndex);
                if (movesBoard) GENERATE_MOVE(moves, BLACK_PAWN, NO_PIECE, sourceIndex, bitScan(movesBoard), 1);
            }
        }
    }
}
