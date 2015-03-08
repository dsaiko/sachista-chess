#pragma once
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
#include "chessboard.h"

class ChessBoardStats;

class Move {
public:

    Move();

    Piece   piece;
    Piece   promotionPiece;

    int     sourceIndex;
    int     targetIndex;

    Bool    isEnPassant;
    Bool    isLegal;
    Bool    isCapture;

    std::string toString();
};

class MoveGeneratorPawn;
class MoveGeneratorKnight;
class MoveGeneratorKing;
class MoveGeneratorRook;
class MoveGeneratorBishop;

class MoveGenerator {
public:
    virtual    bitmask  generateAttacks(const ChessBoard &board, const Color color, const ChessBoardStats &stats) const = 0;

protected:
    static bitmask shiftBitMask(bitmask b, int up, int right);

    static const MoveGeneratorPawn      generatorPawn;
    static const MoveGeneratorKnight    generatorKnight;
    static const MoveGeneratorKing      generatorKing;
    static const MoveGeneratorRook      generatorRook;
    static const MoveGeneratorBishop    generatorBishop;


    static bitmask attacks(const ChessBoard &board, const Color color, const ChessBoardStats &stats);
};

class MoveGeneratorPawn: MoveGenerator {
public:
    MoveGeneratorPawn();

    virtual    bitmask  generateAttacks(const ChessBoard &board, const Color color, const ChessBoardStats &stats) const;

private:
    bitmask PAWN_MOVES[2][64];
    bitmask PAWN_DOUBLE_MOVES[2][64];
    bitmask PAWN_ATTACKS[2][64];
};


class MoveGeneratorKnight: MoveGenerator {
public:
    MoveGeneratorKnight();

    virtual    bitmask  generateAttacks(const ChessBoard &board, const Color color, const ChessBoardStats &stats) const;

private:
    bitmask KNIGHT_MOVES[64];
};


class MoveGeneratorKing: MoveGenerator {
public:
    MoveGeneratorKing();

    virtual    bitmask  generateAttacks(const ChessBoard &board, const Color color, const ChessBoardStats &stats) const;

private:
    bitmask KING_MOVES[64];
};

class MoveGeneratorBishop: MoveGenerator {
public:
    MoveGeneratorBishop();

    virtual    bitmask  generateAttacks(const ChessBoard &board, const Color color, const ChessBoardStats &stats) const;
private:
    int A1H8_INDEX[64];
    int A8H1_INDEX[64];

    bitmask MOVE_A1H8_MASK[64];
    bitmask MOVE_A1H8_MAGIC[64];
    bitmask MOVE_A8H1_MASK[64];
    bitmask MOVE_A8H1_MAGIC[64];

    bitmask MOVE_A1H8_ATTACKS[64][64];
    bitmask MOVE_A8H1_ATTACKS[64][64];

    bitmask onePieceAttacks(const int sourceIndex, const bitmask allPieces)const ;

};

class MoveGeneratorRook: MoveGenerator {
public:
    MoveGeneratorRook();

    virtual    bitmask  generateAttacks(const ChessBoard &board, const Color color, const ChessBoardStats &stats) const;
private:

    bitmask onePieceAttacks(const int sourceIndex, const bitmask allPieces) const;

    int     MOVE_RANK_SHIFT[64];
    bitmask MOVE_RANK_MASK[64];
    bitmask MOVE_RANK_ATTACKS[64][64];
    bitmask MOVE_FILE_MASK[64];
    bitmask MOVE_FILE_MAGIC[64];
    bitmask MOVE_FILE_ATTACKS[64][64];
};




//#define MAX_MOVES_ARR_SIZE    220
//INLINE void generateMoves(const ChessBoard *board, const ChessBoardComputedInfo *boardInfo, Move **moves);
//void        makeMove(ChessBoard *board0, const bitboard allPieces, const Move *m);
//int         isNotUnderCheck(const ChessBoard *board, const Color nextMove);
