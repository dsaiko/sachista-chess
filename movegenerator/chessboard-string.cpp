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

std::string ChessBoard::toString() {
    static const std::string header = "  a b c d e f g h\n";
    std::string buffer;

    buffer += header;

    bitmask  whiteKingReversed      = BitBoard::reverseRanks(pieces[White][King]);
    bitmask  whiteQueenReversed     = BitBoard::reverseRanks(pieces[White][Queen]);
    bitmask  whiteRookReversed      = BitBoard::reverseRanks(pieces[White][Rook]);
    bitmask  whiteKnightReversed    = BitBoard::reverseRanks(pieces[White][Knight]);
    bitmask  whiteBishopReversed    = BitBoard::reverseRanks(pieces[White][Bishop]);
    bitmask  whitePawnReversed      = BitBoard::reverseRanks(pieces[White][Pawn]);
    bitmask  blackKingReversed      = BitBoard::reverseRanks(pieces[Black][King]);
    bitmask  blackQueenReversed     = BitBoard::reverseRanks(pieces[Black][Queen]);
    bitmask  blackRookReversed      = BitBoard::reverseRanks(pieces[Black][Rook]);
    bitmask  blackKnightReversed    = BitBoard::reverseRanks(pieces[Black][Knight]);
    bitmask  blackBishopReversed    = BitBoard::reverseRanks(pieces[Black][Bishop]);
    bitmask  blackPawnReversed      = BitBoard::reverseRanks(pieces[Black][Pawn]);

    // print all 64 pieces
    for (int i = 0; i < 64; i++) {
        if ((i % 8) == 0) {
            if (i > 0) {
                buffer += '0' + 9 - (i / 8);
                buffer += '\n';
            }

            buffer += '0' + 8 - (i / 8);
            buffer += ' ';
        }

        char c = '-';
        bitmask test = (1ULL << i);

        if      (whiteKingReversed & test)      c = 'K';
        else if (whiteQueenReversed & test)     c = 'Q';
        else if (whiteRookReversed & test)      c = 'R';
        else if (whiteKnightReversed & test)    c = 'N';
        else if (whiteBishopReversed & test)    c = 'B';
        else if (whitePawnReversed & test)      c = 'P';
        else if (blackKingReversed & test)      c = 'k';
        else if (blackQueenReversed & test)     c = 'q';
        else if (blackRookReversed & test)      c = 'r';
        else if (blackKnightReversed & test)    c = 'n';
        else if (blackBishopReversed & test)    c = 'b';
        else if (blackPawnReversed & test)      c = 'p';

        buffer += c;
        buffer += ' ';
    }

    buffer += "1\n";
    buffer += header;
    return buffer;
}
