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

#include <string>
#include <sstream>
#include <iostream>
#include "chessboard.h"
#include "move.h"


const MoveGeneratorPawn      MoveGenerator::generatorPawn;
const MoveGeneratorKnight    MoveGenerator::generatorKnight;
const MoveGeneratorKing      MoveGenerator::generatorKing;
const MoveGeneratorRook      MoveGenerator::generatorRook;
const MoveGeneratorBishop    MoveGenerator::generatorBishop;


std::string Move::toString() {
    std::stringstream move;

    move
            << BitBoard::fieldNotation(sourceIndex)
            << BitBoard::fieldNotation(targetIndex);

    switch(promotionPiece) {
        case Queen:     move <<  'q'; break;
        case King:      move <<  'k'; break;
        case Rook:      move <<  'r'; break;
        case Bishop:    move <<  'b'; break;
        case Knight:    move <<  'n'; break;
        case Pawn:      move <<  'p'; break;
        default:        ;
    }

    return move.str();
}


bitmask MoveGenerator::shiftBitMask(bitmask b, int up, int right) {
    //move the piece up or down
    if (up > 0) {
        for(int i=0; i < up; i++)
            b = BitBoard::oneNorth(b);
    } else if(up < 0) {
        for(int i=0; i < -up; i++)
            b = BitBoard::oneSouth(b);
    }

    //move the piece right or left
    if (right > 0) {
        for(int i=0; i < right; i++)
            b = BitBoard::oneEast(b);
    } else if( right < 0){
        for(int i=0; i < -right; i++)
            b = BitBoard::oneWest(b);
    }
    return b;
}

inline bitmask MoveGenerator::attacks(const ChessBoard &board, const Color color, const ChessBoardStats &stats)
{
    return
            generatorPawn.generateAttacks(board, color, stats)      |
            generatorKnight.generateAttacks(board, color, stats)    |
            generatorKing.generateAttacks(board, color, stats)      |
            generatorRook.generateAttacks(board, color, stats)      |
            generatorBishop.generateAttacks(board, color, stats)
    ;
}
