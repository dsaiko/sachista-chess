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

void generateMovesBishop(const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo)
{
    bitboard bishop = board->pieces[board->nextMove][BISHOP];

    Piece movingPiece = BISHOP;
    int sourceIndex;

    for(int i=0; i<2; i++) {
        //for all bishops
        while (bishop) {
            sourceIndex = bitPop(&bishop);
            //get all moves using precomputed values
            bitboard movesBoard = BISHOP_ATTACKS(sourceIndex, boardInfo->allPieces) & boardInfo->boardAvailable;

            //for all moves
            while (movesBoard) GENERATE_MOVE(moves, movingPiece, NO_PIECE, sourceIndex, bitPop(&movesBoard), 0);
        }

        //switch to queen
        bishop = board->pieces[board->nextMove][QUEEN];
        movingPiece = QUEEN;
    }
}
