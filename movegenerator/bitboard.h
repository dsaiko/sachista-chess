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

#include <stdint.h>
#include <string>

typedef unsigned __int64 bitmask;

enum class BitMask : bitmask {
    A1  =   1ULL,           B1  =   (1ULL << 1),    C1  =   (1ULL << 2),    D1  =   (1ULL << 3),    E1  =   (1ULL << 4),    F1  =   (1ULL << 5),    G1  =   (1ULL << 6),    H1  =   (1ULL << 7),
    A2  =   (1ULL << 8),    B2  =   (1ULL << 9),    C2  =   (1ULL << 10),   D2  =   (1ULL << 11),   E2  =   (1ULL << 12),   F2  =   (1ULL << 13),   G2  =   (1ULL << 14),   H2  =   (1ULL << 15),
    A3  =   (1ULL << 16),   B3  =   (1ULL << 17),   C3  =   (1ULL << 18),   D3  =   (1ULL << 19),   E3  =   (1ULL << 20),   F3  =   (1ULL << 21),   G3  =   (1ULL << 22),   H3  =   (1ULL << 23),
    A4  =   (1ULL << 24),   B4  =   (1ULL << 25),   C4  =   (1ULL << 26),   D4  =   (1ULL << 27),   E4  =   (1ULL << 28),   F4  =   (1ULL << 29),   G4  =   (1ULL << 30),   H4  =   (1ULL << 31),
    A5  =   (1ULL << 32),   B5  =   (1ULL << 33),   C5  =   (1ULL << 34),   D5  =   (1ULL << 35),   E5  =   (1ULL << 36),   F5  =   (1ULL << 37),   G5  =   (1ULL << 38),   H5  =   (1ULL << 39),
    A6  =   (1ULL << 40),   B6  =   (1ULL << 41),   C6  =   (1ULL << 42),   D6  =   (1ULL << 43),   E6  =   (1ULL << 44),   F6  =   (1ULL << 45),   G6  =   (1ULL << 46),   H6  =   (1ULL << 47),
    A7  =   (1ULL << 48),   B7  =   (1ULL << 49),   C7  =   (1ULL << 50),   D7  =   (1ULL << 51),   E7  =   (1ULL << 52),   F7  =   (1ULL << 53),   G7  =   (1ULL << 54),   H7  =   (1ULL << 55),
    A8  =   (1ULL << 56),   B8  =   (1ULL << 57),   C8  =   (1ULL << 58),   D8  =   (1ULL << 59),   E8  =   (1ULL << 60),   F8  =   (1ULL << 61),   G8  =   (1ULL << 62),   H8  =   (1ULL << 63),

    FILE_A      = A1 | A2 | A3 | A4 | A5 | A6 | A7 | A8,
    FILE_H      = H1 | H2 | H3 | H4 | H5 | H6 | H7 | H8,
    NOT_FILE_A  = (~FILE_A),
    NOT_FILE_H  = (~FILE_H),

    RANK_1      = A1 | B1 | C1 | D1 | E1 | F1 | G1 | H1,
    RANK_8      = A8 | B8 | C8 | D8 | E8 | F8 | G8 | H8,

    FRAME       = RANK_1 | RANK_8 | FILE_A | FILE_H,
    UNIVERSE    = (~0ULL),
};

enum class BoardIndex : int {
    A1  = 0,    B1  = 1,    C1  = 2,    D1  = 3,    E1  = 4,    F1  = 5,    G1  = 6,    H1  = 7,
    A2  = 8,    B2  = 9,    C2  = 10,   D2  = 11,   E2  = 12,   F2  = 13,   G2  = 14,   H2  = 15,
    A3  = 16,   B3  = 17,   C3  = 18,   D3  = 19,   E3  = 20,   F3  = 21,   G3  = 22,   H3  = 23,
    A4  = 24,   B4  = 25,   C4  = 26,   D4  = 27,   E4  = 28,   F4  = 29,   G4  = 30,   H4  = 31,
    A5  = 32,   B5  = 33,   C5  = 34,   D5  = 35,   E5  = 36,   F5  = 37,   G5  = 38,   H5  = 39,
    A6  = 40,   B6  = 41,   C6  = 42,   D6  = 43,   E6  = 44,   F6  = 45,   G6  = 46,   H6  = 47,
    A7  = 48,   B7  = 49,   C7  = 50,   D7  = 51,   E7  = 52,   F7  = 53,   G7  = 54,   H7  = 55,
    A8  = 56,   B8  = 57,   C8  = 58,   D8  = 59,   E8  = 60,   F8  = 61,   G8  = 62,   H8  = 63
};

namespace BitBoard {
    inline bitmask  oneEast             (const bitmask b)                   { return ((b << 1) & (bitmask) BitMask::NOT_FILE_A); }
    inline bitmask  oneNorthEast        (const bitmask b)                   { return ((b << 9) & (bitmask) BitMask::NOT_FILE_A); }
    inline bitmask  oneSouthEast        (const bitmask b)                   { return ((b >> 7) & (bitmask) BitMask::NOT_FILE_A); }

    inline bitmask  oneWest             (const bitmask b)                   { return ((b >> 1) & (bitmask) BitMask::NOT_FILE_H); }
    inline bitmask  oneSouthWest        (const bitmask b)                   { return ((b >> 9) & (bitmask) BitMask::NOT_FILE_H); }
    inline bitmask  oneNorthWest        (const bitmask b)                   { return ((b << 7) & (bitmask) BitMask::NOT_FILE_H); }

    inline bitmask  oneNorth            (const bitmask b)                   { return (b << 8); }
    inline bitmask  oneSouth            (const bitmask b)                   { return (b >> 8); }

    inline int      fileIndex           (const BoardIndex index)            { return (int) index % 8; }
    inline int      rankIndex           (const BoardIndex index)            { return (int) index / 8; }
    inline bitmask  squareBitmask       (const BoardIndex index)            { return (1ULL << (int) index); }

    bitmask  reverseRanks               (const bitmask b);
    bitmask  flipDiagA1H8               (const bitmask b);
    bitmask  mirrorHorizontal           (const bitmask b);

    bitmask  fromNotation               (const std::string &notation);
    std::string fieldNotation           (const BoardIndex index);
    std::string toString                (const bitmask b);

    //pregenerated constants
    const bitmask RANK[8]               = {255ULL, 65280ULL, 16711680ULL, 4278190080ULL, 1095216660480ULL, 280375465082880ULL, 71776119061217280ULL, 18374686479671623680ULL};
    const bitmask FILE[8]               = {72340172838076673ULL, 144680345676153346ULL, 289360691352306692ULL, 578721382704613384ULL, 1157442765409226768ULL, 2314885530818453536ULL, 4629771061636907072ULL, 9259542123273814144ULL};
    const bitmask A1H8[15]              = {72057594037927936ULL, 144396663052566528ULL, 288794425616760832ULL, 577588855528488960ULL, 1155177711073755136ULL, 2310355422147575808ULL, 4620710844295151872ULL, 9241421688590303745ULL, 36099303471055874ULL, 141012904183812ULL, 550831656968ULL, 2151686160ULL, 8405024ULL, 32832ULL, 128ULL};
    const bitmask A8H1[15]              = {1ULL, 258ULL, 66052ULL, 16909320ULL, 4328785936ULL, 1108169199648ULL, 283691315109952ULL, 72624976668147840ULL, 145249953336295424ULL, 290499906672525312ULL, 580999813328273408ULL, 1161999622361579520ULL, 2323998145211531264ULL, 4647714815446351872ULL, 9223372036854775808ULL};
};
