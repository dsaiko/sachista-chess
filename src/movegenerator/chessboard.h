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

#include "bitboard.h"
#include "version.h"
#include "zobrist.h"

enum Castling {
    None        = 0,
    KingSide    = 1,
    QueenSide   = 2,
};

enum Piece {
    NoPiece     = -1,
    King        = 0,
    Queen       = 1,
    Bishop      = 2,
    Knight      = 3,
    Rook        = 4,
    Pawn        = 5
};

enum Color {
    White       = 0,
    Black       = 1
};

class ChessBoard {

public:
    ChessBoard();
    explicit ChessBoard(const std::string &fen);

    Color       nextMove;
    Castling    castling[2];
    bitmask     pieces[2][6];
    int         halfMoveClock;
    int         fullMoveNumber;
    int         enPassantTargetIndex;

    //zobrist key is a hashcode of the beard (without halfMoveClock and fullMoveNumber info)
    uint64_t        zobristKey;

    bool operator==(const ChessBoard &other) const;
    inline bool operator!=(const ChessBoard &other) const {return !(*this==other); }

    [[nodiscard]] inline  bitmask         whitePieces() const { return pieces[White][Queen] | pieces[White][King] | pieces[White][Rook] | pieces[White][Bishop] | pieces[White][Knight] | pieces[White][Pawn]; }
    [[nodiscard]] inline  bitmask         blackPieces() const { return pieces[Black][Queen] | pieces[Black][King] | pieces[Black][Rook] | pieces[Black][Bishop] | pieces[Black][Knight] | pieces[Black][Pawn]; }
    [[nodiscard]] inline  bitmask         allPieces()   const { return whitePieces() | blackPieces(); }
    [[nodiscard]] inline  bitmask         opponentPieces()   const { return nextMove == White ? blackPieces() : whitePieces(); }
    [[nodiscard]] inline  bitmask         boardAvaliable()   const { return nextMove == White ? ~whitePieces() : ~blackPieces(); }
    [[nodiscard]] inline  Color           opponentColor()   const { return nextMove == White ? Black : White; }
    [[nodiscard]] inline  bitmask         king()   const { return pieces[nextMove][King]; }
    [[nodiscard]] inline  int             kingIndex()   const { return BitBoard::bitScan(king()); }

    inline  void            removeCastling(Color color, Castling remove) { castling[color] = (Castling) (castling[color] & ~remove); }


            void            clearBoard();
            [[nodiscard]] std::string     toString() const;
            void            setupString(const std::string &str);
            std::string     toFEN();
            void            setupFEN(const std::string &fen);

            void            setupStandardBoard();
    inline  void            updateZobrist() { zobristKey = zobrist.getKey(*this); }
            [[nodiscard]] uint64_t        perft(int depth) const;

    static const Zobrist zobrist;
    static const std::string STANDARD_BOARD_FEN;

};



