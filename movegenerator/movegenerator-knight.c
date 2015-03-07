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

void generateMovesKnight(const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo)
{
    bitboard knight = board->pieces[board->nextMove][KNIGHT];

    // while there are knight pieces
    while (knight) {
         int sourceIndex = bitPop(&knight);
         // get possible moves - moves minus my onw color
         bitboard movesBoard = KNIGHT_MOVES[sourceIndex] & boardInfo->boardAvailable;
         // for all moves
         while (movesBoard) GENERATE_MOVE(moves, KNIGHT, NO_PIECE, sourceIndex, bitPop(&movesBoard), 0);
    }
}
