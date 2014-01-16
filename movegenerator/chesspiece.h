/*
  sachista-chess copyright (C) 2014 Dusan Saiko

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

#ifndef SACHISTA_CHESS_PIECE_H
#define SACHISTA_CHESS_PIECE_H

enum chessPiece {
    NO_PIECE        = '-',
    WHITE_KING      = 'K',
    WHITE_QUEEN     = 'Q',
    WHITE_BISHOP    = 'B',
    WHITE_KNIGHT    = 'N',
    WHITE_PAWN      = 'P',
    WHITE_ROOK      = 'R',
    BLACK_KING      = 'k',
    BLACK_QUEEN     = 'q',
    BLACK_BISHOP    = 'b',
    BLACK_KNIGHT    = 'n',
    BLACK_PAWN      = 'p',
    BLACK_ROOK      = 'r'
};

enum pieceColor {
    WHITE           = 'w',
    BLACK           = 'b'
};


#endif //SACHISTA_CHESS_PIECE_H

