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

#include <string.h>
#include <vector>

#include "chessboard.h"
#include "zobrist.h"
#include "chessboard-stats.h"
#include "utility.h"
#include "move.h"
#include "movearray.h"


/**
 * @brief This is a perft worker
 * @param board
 * @param depth
 * @param cache Shared cache, needs OMP synchronization
 * @return number of legal moves
 */
uint64_t minimax(const ChessBoard &board, const int depth, const ChessBoardStats &stats)
{
    //TODO: multi thread
    //TODO: cache

    uint64_t count = 0;

    MoveArray moves;
    MoveGenerator::moves(board, stats, moves);

    for(int i=0; i < moves.size(); i++) {
        ChessBoard nextBoard = board;
        moves.data[i].applyTo(nextBoard);

        ChessBoardStats nextStats(nextBoard);
        if(MoveGenerator::isOpponentsKingNotUnderCheck(nextBoard, nextStats)) {
            count += (depth == 1) ? 1 : minimax(nextBoard, depth -1, nextStats);
        }
    }
    return count;
}

uint64_t ChessBoard::perft(int depth) const
{
    if(depth < 1) return 0;
    return minimax(*this, depth, ChessBoardStats(*this));
}

