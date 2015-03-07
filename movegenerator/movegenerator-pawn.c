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

void generateMovesPawn(const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo)
{
    const bitboard emptyBoard = ~boardInfo->allPieces;

    int whiteBaseRank;
    int blackBaseRank;

    int whitePromotionRank;
    int blackPromotionRank;

    if(board->nextMove == WHITE) {
        whiteBaseRank = 16;
        blackBaseRank = 999;

        whitePromotionRank = 55;
        blackPromotionRank = 0;
    } else {
        whiteBaseRank = 0;
        blackBaseRank = 47;

        whitePromotionRank = 999;
        blackPromotionRank = 8;
    }

    bitboard pawns = board->pieces[board->nextMove][PAWN];

    //while there are pieces
    while (pawns) {
        //get next piece
        const int sourceIndex = bitPop(&pawns);

        //get possible moves - moves minus my onw color
        //one step forward
        bitboard movesBoard = PAWN_MOVES[board->nextMove][sourceIndex] & emptyBoard;

        //if one step forward was sucessful and we are on base rank, try double move
        if(unlikely(sourceIndex < whiteBaseRank) && movesBoard) {
            movesBoard |=  ONE_NORTH(movesBoard) & emptyBoard;
        } else if(unlikely(sourceIndex > blackBaseRank) && movesBoard) {
            movesBoard |=  ONE_SOUTH(movesBoard) & emptyBoard;
        }

        //get attacks, only against oponent pieces
        const bitboard attacks = PAWN_ATTACKS[board->nextMove][sourceIndex];
        movesBoard |=  attacks & boardInfo->opponentPieces;

        //for all moves
        while (movesBoard) {
            //get next move
            const int targetIndex = bitPop(&movesBoard);

            //promotion?
            if (unlikely(targetIndex > whitePromotionRank || targetIndex < blackPromotionRank)) {
                GENERATE_MOVE(moves, PAWN, BISHOP, sourceIndex, targetIndex, 0);
                GENERATE_MOVE(moves, PAWN, KNIGHT, sourceIndex,  targetIndex, 0);
                GENERATE_MOVE(moves, PAWN, QUEEN, sourceIndex, targetIndex, 0);
                GENERATE_MOVE(moves, PAWN, ROOK,  sourceIndex, targetIndex, 0);
            } else {
                //normal move/capture
                GENERATE_MOVE(moves, PAWN, NO_PIECE, sourceIndex, targetIndex, 0);
            }

        }

        //check enpassant capture
        if(unlikely(board->enPassantTargetIndex)) {
            movesBoard = attacks & BITMASK_SQUARE(board->enPassantTargetIndex);
            if (movesBoard) GENERATE_MOVE(moves, PAWN, NO_PIECE, sourceIndex, bitScan(movesBoard), 1);
        }

    }
}
