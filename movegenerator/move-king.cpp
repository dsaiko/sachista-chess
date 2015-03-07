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

const bitmask WHITE_CASTLE_OO_EMPTY     = BitMask::F1 | BitMask::G1;
const bitmask WHITE_CASTLE_OO_ATTACKS   = BitMask::E1 | BitMask::F1 | BitMask::G1;
const bitmask WHITE_CASTLE_OOO_EMPTY    = BitMask::B1 | BitMask::C1 | BitMask::D1;
const bitmask WHITE_CASTLE_OOO_ATTACKS  = BitMask::C1 | BitMask::D1 | BitMask::E1;

const bitmask BLACK_CASTLE_OO_EMPTY     = BitMask::F8 | BitMask::G8;
const bitmask BLACK_CASTLE_OO_ATTACKS   = BitMask::E8 | BitMask::F8 | BitMask::G8;
const bitmask BLACK_CASTLE_OOO_EMPTY    = BitMask::B8 | BitMask::C8 | BitMask::D8;
const bitmask BLACK_CASTLE_OOO_ATTACKS  = BitMask::C8 | BitMask::D8 | BitMask::E8;

MoveGeneratorKing::MoveGeneratorKing() {
    //for all fields
    for (int i = 0; i < 64; i++) {
        //put the piece on the board
        bitmask piece = BitBoard::squareBitmask(i);

        //move all directions
        KING_MOVES[i] =
                shiftBitMask(piece,  1,  0) |
                shiftBitMask(piece,  1,  1) |
                shiftBitMask(piece,  0,  1) |
                shiftBitMask(piece, -1,  1) |
                shiftBitMask(piece, -1,  0) |
                shiftBitMask(piece, -1, -1) |
                shiftBitMask(piece,  0, -1) |
                shiftBitMask(piece,  1, -1)
        ;
    }
}

bitmask MoveGeneratorKing::generateAttacks(const ChessBoard &board, const Color color) {
    const bitmask piece = board.pieces[color][King];
    if(piece == 0) return 0;
    return KING_MOVES[BitBoard::bitScan(piece)];
}