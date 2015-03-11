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

std::string Move::toString() const {
    std::stringstream move;

    move << BitBoard::fieldNotation(sourceIndex);
    if(isCapture)
        move << "x";

    move << BitBoard::fieldNotation(targetIndex);

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
    if(up > 0)  b <<= up * 8;
    if(up < 0)  b >>= (-up) * 8;
    for(int i=0; i < right; i++) b = BitBoard::oneEast(b);
    for(int i=0; i < -right; i++) b = BitBoard::oneWest(b);
    return b;
}

inline bitmask MoveGenerator::attacks(const ChessBoard &board, const Color color, const ChessBoardStats &stats)
{
    return
            generatorPawn.generateAttacks(board, color)             |
            generatorKnight.generateAttacks(board, color)           |
            generatorKing.generateAttacks(board, color)             |
            generatorRook.generateAttacks(board, color, stats)      |
            generatorBishop.generateAttacks(board, color, stats)
    ;
}

void MoveGenerator::moves(const ChessBoard &board, const ChessBoardStats &stats, MoveArray &moves)
{
    generatorPawn.generateMoves(board, stats, moves);
    generatorKnight.generateMoves(board, stats, moves);
    generatorKing.generateMoves(board, stats, moves);
    generatorRook.generateMoves(board, stats, moves);
    generatorBishop.generateMoves(board, stats, moves);
}



bool  MoveGenerator::isBitMaskUnderAttack(const ChessBoard &board, const Color color, const ChessBoardStats &stats, bitmask fields)
{
    //this is used only for castling, not much to bother about
    bitmask attacks = generatorRook.generateAttacks(board, color, stats);
    if(attacks & fields) return true;
    attacks  =  generatorBishop.generateAttacks(board, color, stats);
    if(attacks & fields) return true;
    attacks  =  generatorKnight.generateAttacks(board, color);
    if(attacks & fields) return true;
    attacks  =  generatorPawn.generateAttacks(board, color);
    if(attacks & fields) return true;
    attacks  =  generatorKing.generateAttacks(board, color);
    if(attacks & fields) return true;

    return false;
}

bool MoveGenerator::isOpponentsKingNotUnderCheck(const ChessBoard &board, const ChessBoardStats &stats)
{
    //reverse check if KING piece is not attacked by any other
    const Color opponentColor = board.nextMove == Black ? White : Black;

    //check if my king is not under check by opponent pieces
    const bitmask king = board.pieces[opponentColor][King];

    if(!king) return false;
    int kingIndex = BitBoard::bitScan(king);

    const bitmask *pieces = board.pieces[board.nextMove];

    if (pieces[Pawn]   & generatorPawn.PAWN_ATTACKS[opponentColor][kingIndex]) return false;
    if (pieces[Knight] & generatorKnight.KNIGHT_MOVES[kingIndex])              return false;
    if (pieces[King]   & generatorKing.KING_MOVES[kingIndex])                  return false;

    const bitmask rooks = pieces[Queen] | pieces[Rook];
    if (generatorRook.MOVE_RANK_ATTACKS[kingIndex][(int) (((stats.allPieces & generatorRook.MOVE_RANK_MASK[kingIndex]) >> generatorRook.MOVE_RANK_SHIFT[kingIndex]))] & rooks)
        return false;
    if (generatorRook.MOVE_FILE_ATTACKS[kingIndex][(int) (((stats.allPieces & generatorRook.MOVE_FILE_MASK[kingIndex]) * generatorRook.MOVE_FILE_MAGIC[kingIndex]) >> 57)] & rooks)
        return false;

    const bitmask bishops = pieces[Queen] | pieces[Bishop];
    if (generatorBishop.MOVE_A8H1_ATTACKS[kingIndex][(int) (((stats.allPieces & generatorBishop.MOVE_A8H1_MASK[kingIndex]) * generatorBishop.MOVE_A8H1_MAGIC[kingIndex]) >> 57)] & bishops)
        return false;
    if (generatorBishop.MOVE_A1H8_ATTACKS[kingIndex][(int) (((stats.allPieces & generatorBishop.MOVE_A1H8_MASK[kingIndex]) * generatorBishop.MOVE_A1H8_MAGIC[kingIndex]) >> 57)] & bishops)
        return false;

    return true;
}
