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

class Move {
public:

    Piece   piece;
    Piece   promotionPiece;

    int     sourceIndex;
    int     targetIndex;

    bool    isCapture;
    bool    isEnPassant;

    [[nodiscard]] ChessBoard      applyToBoard(ChessBoard board) const;
    [[nodiscard]] std::string     toString() const;
};


class MoveArray;

class MoveGeneratorPawn {
public:
    MoveGeneratorPawn();

    [[nodiscard]] bitmask  generateAttacks(const ChessBoard &board, Color color) const;
    void generateMoves(const ChessBoard &board, MoveArray &moves) const;

    bitmask PAWN_MOVES[2][64];
    bitmask PAWN_ATTACKS[2][64];
};


class MoveGeneratorKnight {
public:
    MoveGeneratorKnight();

    [[nodiscard]] bitmask  generateAttacks(const ChessBoard &board, Color color) const;
    void generateMoves(const ChessBoard &board, MoveArray &moves) const;

    bitmask KNIGHT_MOVES[64];
};


class MoveGeneratorKing {
public:
    MoveGeneratorKing();

    [[nodiscard]] bitmask  generateAttacks(const ChessBoard &board, Color color) const;
    void generateMoves(const ChessBoard &board, MoveArray &moves) const;

    bitmask KING_MOVES[64];
};

class MoveGeneratorBishop {
public:
    MoveGeneratorBishop();

    [[nodiscard]] bitmask  generateAttacks(const ChessBoard &board, Color color) const;
    void generateMoves(const ChessBoard &board, MoveArray &moves) const;


    int A1H8_INDEX[64];
    int A8H1_INDEX[64];

    bitmask MOVE_A1H8_MASK[64];
    bitmask MOVE_A1H8_MAGIC[64];
    bitmask MOVE_A8H1_MASK[64];
    bitmask MOVE_A8H1_MAGIC[64];

    bitmask MOVE_A1H8_ATTACKS[64][64];
    bitmask MOVE_A8H1_ATTACKS[64][64];

    [[nodiscard]] bitmask onePieceAttacks(int sourceIndex, bitmask allPieces)const ;

};

class MoveGeneratorRook {
public:
    MoveGeneratorRook();

    [[nodiscard]] virtual    bitmask  generateAttacks(const ChessBoard &board, Color color) const;
    virtual    void generateMoves(const ChessBoard &board, MoveArray &moves) const;

    [[nodiscard]] bitmask onePieceAttacks(int sourceIndex, bitmask allPieces) const;

    int     MOVE_RANK_SHIFT[64];
    bitmask MOVE_RANK_MASK[64];
    bitmask MOVE_RANK_ATTACKS[64][64];
    bitmask MOVE_FILE_MASK[64];
    bitmask MOVE_FILE_MAGIC[64];
    bitmask MOVE_FILE_ATTACKS[64][64];
};

class MoveGenerator {
public:
    static bitmask  attacks(const ChessBoard &board, Color color);
    static void     moves(const ChessBoard &board, MoveArray &moves);

    static bitmask shiftBitMask(bitmask b, int up, int right);

    static const MoveGeneratorPawn      generatorPawn;
    static const MoveGeneratorKnight    generatorKnight;
    static const MoveGeneratorKing      generatorKing;
    static const MoveGeneratorRook      generatorRook;
    static const MoveGeneratorBishop    generatorBishop;


    static bool    isBitMaskUnderAttack(const ChessBoard &board, Color color, bitmask fields);
    static bool    isOpponentsKingNotUnderCheck(const ChessBoard &board);
};
