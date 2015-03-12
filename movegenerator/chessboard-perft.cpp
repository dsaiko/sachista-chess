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
#include <iostream>

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

    //maybepins - that include king itself
    bitmask attacks = MoveGenerator::attacks(board, stats.opponentColor, stats);

    for(int i=0; i < moves.size(); i++) {
        Move &move = moves.data[i];
        bitmask piece = BitBoard::squareBitmask(move.sourceIndex);

        if(depth == 1) {
            //we only need to validate the board in following cases
            if((piece & stats.king) || (attacks & stats.king) || (piece & attacks) || move.isEnPassant) {
                ChessBoard nextBoard = board;
                move.applyTo(nextBoard);

                ChessBoardStats nextStats(nextBoard);
                if(MoveGenerator::isOpponentsKingNotUnderCheck(nextBoard, nextStats)) {
                    count += 1;
                }
            } else {
                count += 1;
            }
        } else {
            ChessBoard nextBoard = board;
            move.applyTo(nextBoard);

            ChessBoardStats nextStats(nextBoard);
            if((piece & stats.king) || (attacks & stats.king) || (piece & attacks) || move.isEnPassant) {
                if(MoveGenerator::isOpponentsKingNotUnderCheck(nextBoard, nextStats)) {
                    count += minimax(nextBoard, depth -1, nextStats);
                }
            } else {
                count += minimax(nextBoard, depth -1, nextStats);
            }
        }
    }
    return count;
}

uint64_t ChessBoard::perft(int depth) const
{
    if(depth < 1) return 0;
    return minimax(*this, depth, ChessBoardStats(*this));
}

