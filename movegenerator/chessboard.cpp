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
#include <iostream>
#include "chessboard.h"

const Zobrist ChessBoard::zobrist;

ChessBoard::ChessBoard():
    nextMove(White),
    castling{},
    pieces{},
    halfMoveClock(0),
    fullMoveNumber(1),
    enPassantTargetIndex(0),
    zobristKey(0)
{
    //TODO: Do we need reseting the object in constructor?
}

ChessBoard::ChessBoard(const std::string &fen)
: ChessBoard()
{
    setupFEN(fen);
}

void ChessBoard::setupStandardBoard() {
    setupFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

bool ChessBoard::operator==(const ChessBoard &other)
{
    return this->zobristKey == other.zobristKey;
}

void ChessBoard::clearBoard() {
    nextMove = White;
    castling[White] = None;
    castling[Black] = None;
    halfMoveClock = 0;
    fullMoveNumber = 1;
    enPassantTargetIndex = 0;
    zobristKey = 0;

    std::fill( &pieces[0][0], &pieces[0][0] + sizeof(pieces) / sizeof(pieces[0][0]), 0 );
}

//char *move2str(const Move *m, char *buffer, const int bufferSize) {
//    //reinitialize buffer to empty string
//    if(bufferSize < 1) return buffer;
//    buffer[0] = 0;
//
//    char notation[3];
//
//    fieldNotation(m->sourceIndex, notation, sizeof(notation) / sizeof(char));
//    appendString(buffer, bufferSize, notation);
//
//    fieldNotation(m->targetIndex, notation, sizeof(notation) / sizeof(char));
//    appendString(buffer, bufferSize, notation);
//
//    if(m->promotionPiece) {
//        switch(m->promotionPiece) {
//        case QUEEN:     notation[0] = 'q'; break;
//        case KING:      notation[0] = 'k'; break;
//        case ROOK:      notation[0] = 'r'; break;
//        case BISHOP:    notation[0] = 'b'; break;
//        case KNIGHT:    notation[0] = 'n'; break;
//        case PAWN:      notation[0] = 'p'; break;
//        default:        ;
//        }
//
//        notation[1] = '\0';
//        appendString(buffer, bufferSize, notation);
//    }
//
//    return buffer;
//}
