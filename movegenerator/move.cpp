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


Move::Move()
:   piece(Piece::NoPiece),
    promotionPiece(Piece::NoPiece),
    sourceIndex(-1),
    targetIndex(-1),
    isCapture(false),
    isEnPassant(false),
    isShortCastling(false),
    isLongCastling(false)
{
}

Move::Move (const Move& other)
:   piece(other.piece),
    promotionPiece(other.promotionPiece),
    sourceIndex(other.sourceIndex),
    targetIndex(other.targetIndex),
    isCapture(other.isCapture),
    isEnPassant(other.isEnPassant),
    isShortCastling(other.isShortCastling),
    isLongCastling(other.isLongCastling)
{

}


Move::Move (Move&& other) NOEXCEPT
:   piece(other.piece),
    promotionPiece(other.promotionPiece),
    sourceIndex(other.sourceIndex),
    targetIndex(other.targetIndex),
    isCapture(other.isCapture),
    isEnPassant(other.isEnPassant),
    isShortCastling(other.isShortCastling),
    isLongCastling(other.isLongCastling)
{

}


Move& Move::operator= (const Move& other)
{
    //TODO: try *this = other only
    Move tmp(other);
    *this = std::move(tmp);
    return *this;
}

Move& Move::operator= (Move&& other) NOEXCEPT
{
    return *this;
}

Move::~Move() NOEXCEPT
{

}

Move::Move(Piece piece, int fromIndex, int toIndex, bool isCapture)
:   piece(piece),
    promotionPiece(Piece::NoPiece),
    sourceIndex(fromIndex),
    targetIndex(toIndex),
    isCapture(isCapture),
    isEnPassant(false),
    isShortCastling(false),
    isLongCastling(false)
{

}

Move::Move(Piece piece, int fromIndex, int toIndex, bool isCapture, bool isEnPassant, bool isShortCastling, bool isLongCastling, Piece promotionPiece)
:   piece(piece),
    promotionPiece(promotionPiece),
    sourceIndex(fromIndex),
    targetIndex(toIndex),
    isCapture(isCapture),
    isEnPassant(isEnPassant),
    isShortCastling(isShortCastling),
    isLongCastling(isLongCastling)
{

}


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

std::vector<Move> MoveGenerator::moves(const ChessBoard &board, const ChessBoardStats &stats)
{
    //TODO: change std::vector to something better
    //TODO: first test vector, then vector + rule of 5, then list, array, no constants
    std::vector<Move> result;

    std::vector<Move> moves = generatorPawn.generateMoves(board, stats);
    result.insert(result.end(), moves.begin(), moves.end());

    moves = generatorKnight.generateMoves(board, stats);
    result.insert(result.end(), moves.begin(), moves.end());

    moves = generatorKing.generateMoves(board, stats);
    result.insert(result.end(), moves.begin(), moves.end());

    moves = generatorRook.generateMoves(board, stats);
    result.insert(result.end(), moves.begin(), moves.end());

    moves = generatorBishop.generateMoves(board, stats);
    result.insert(result.end(), moves.begin(), moves.end());

    return result;
}



bool  MoveGenerator::isBitMaskUnderAttack(const ChessBoard &board, const Color color, const ChessBoardStats &stats, const bitmask fields)
{
    //TODO: measure the reverse check algorithm
    bitmask attacks = generatorRook.generateAttacks(board, color, stats);
    if(attacks & fields) return true;
    attacks  =  generatorBishop.generateAttacks(board, color, stats);
    if(attacks & fields) return true;
    attacks  =  generatorKnight.generateAttacks(board, color, stats);
    if(attacks & fields) return true;
    attacks  =  generatorPawn.generateAttacks(board, color, stats);
    if(attacks & fields) return true;
    attacks  =  generatorKing.generateAttacks(board, color, stats);
    if(attacks & fields) return true;

    return false;
}

bool MoveGenerator::isOpponentsKingNotUnderCheck(const ChessBoard &board, const ChessBoardStats &stats)
{
    //TODO: measure the isBitmaskUnderAttack algorithm

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

    const bitmask rooks   = pieces[Queen] | pieces[Rook];
    if(rooks) {

        if (generatorRook.MOVE_RANK_ATTACKS[kingIndex][(int) (((stats.allPieces & generatorRook.MOVE_RANK_MASK[kingIndex]) >> generatorRook.MOVE_RANK_SHIFT[kingIndex]))] & rooks)
            return false;
        if (generatorRook.MOVE_FILE_ATTACKS[kingIndex][(int) (((stats.allPieces & generatorRook.MOVE_FILE_MASK[kingIndex]) * generatorRook.MOVE_FILE_MAGIC[kingIndex]) >> 57)] & rooks)
            return false;
    }

    const bitmask bishops = pieces[Queen] | pieces[Bishop];
    if(bishops) {

        if (generatorBishop.MOVE_A8H1_ATTACKS[kingIndex][(int) (((stats.allPieces & generatorBishop.MOVE_A8H1_MASK[kingIndex]) * generatorBishop.MOVE_A8H1_MAGIC[kingIndex]) >> 57)] & bishops)
            return false;
        if (generatorBishop.MOVE_A1H8_ATTACKS[kingIndex][(int) (((stats.allPieces & generatorBishop.MOVE_A1H8_MASK[kingIndex]) * generatorBishop.MOVE_A1H8_MAGIC[kingIndex]) >> 57)] & bishops)
            return false;
    }

    return true;
}
