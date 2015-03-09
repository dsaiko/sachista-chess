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
    //compute directly
    if(depth < 1) return 1;

    uint64_t count = 0;

    std::vector<Move> moves = MoveGenerator::moves(board, stats);

    ChessBoard nextBoard = board;

    for(Move move : moves) {
        move.applyTo(nextBoard);

        ChessBoardStats nextStats(nextBoard);

        if(MoveGenerator::isKingNotUnderCheck(nextBoard, nextBoard.nextMove, nextStats)) {
            count += minimax(nextBoard, depth -1, nextStats);
        } else {
            count += 1;
        }

        //TODO: not for the last one
        nextBoard = board;
    }

    return count;
}

uint64_t ChessBoard::perft(int depth) const
{
    if(depth < 1) return 1;
    return minimax(*this, depth, ChessBoardStats(*this));
}

