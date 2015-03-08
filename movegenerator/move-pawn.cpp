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

#include "move.h"

MoveGeneratorPawn::MoveGeneratorPawn() {
    //for all fields
    for (int i = 0; i < 64; i++) {
        //put the piece on the board
        bitmask piece = BitBoard::squareBitmask(i);

        PAWN_MOVES[White][i]         = shiftBitMask(piece, 1, 0);
        PAWN_DOUBLE_MOVES[White][i]  = shiftBitMask(piece, 2, 0);
        PAWN_ATTACKS[White][i]       = shiftBitMask(piece, 1, 1) | shiftBitMask(piece, 1, -1);
        PAWN_MOVES[Black][i]         = shiftBitMask(piece, -1, 0);
        PAWN_DOUBLE_MOVES[Black][i]  = shiftBitMask(piece, -2, 0);
        PAWN_ATTACKS[Black][i]       = shiftBitMask(piece, -1, 1) | shiftBitMask(piece, -1, -1);
    }
}

bitmask MoveGeneratorPawn::generateAttacks(const ChessBoard &board, const Color color, const ChessBoardStats &stats) {
    if(color == White) {
        return BitBoard::oneNorthEast(board.pieces[color][Pawn]) | BitBoard::oneNorthWest(board.pieces[color][Pawn]);
    } else {
        return BitBoard::oneSouthEast(board.pieces[color][Pawn]) | BitBoard::oneSouthWest(board.pieces[color][Pawn]);
    }
}