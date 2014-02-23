/*
  sachista-chess copyright (C) 2014 dusan.saiko@gmail.com

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

#ifndef SACHISTA_CHESS_BITBOARD_H
#define SACHISTA_CHESS_BITBOARD_H


#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

#ifdef _MSC_VER
#include <intrin.h>
#endif

#ifdef __cplusplus
extern "C"{
#endif

typedef uint64_t bitboard;

#define BITMASK_A1 1ULL
#define BITMASK_B1 (1ULL << 1)
#define BITMASK_C1 (1ULL << 2)
#define BITMASK_D1 (1ULL << 3)
#define BITMASK_E1 (1ULL << 4)
#define BITMASK_F1 (1ULL << 5)
#define BITMASK_G1 (1ULL << 6)
#define BITMASK_H1 (1ULL << 7)
#define BITMASK_A2 (1ULL << 8)
#define BITMASK_B2 (1ULL << 9)
#define BITMASK_C2 (1ULL << 10)
#define BITMASK_D2 (1ULL << 11)
#define BITMASK_E2 (1ULL << 12)
#define BITMASK_F2 (1ULL << 13)
#define BITMASK_G2 (1ULL << 14)
#define BITMASK_H2 (1ULL << 15)
#define BITMASK_A3 (1ULL << 16)
#define BITMASK_B3 (1ULL << 17)
#define BITMASK_C3 (1ULL << 18)
#define BITMASK_D3 (1ULL << 19)
#define BITMASK_E3 (1ULL << 20)
#define BITMASK_F3 (1ULL << 21)
#define BITMASK_G3 (1ULL << 22)
#define BITMASK_H3 (1ULL << 23)
#define BITMASK_A4 (1ULL << 24)
#define BITMASK_B4 (1ULL << 25)
#define BITMASK_C4 (1ULL << 26)
#define BITMASK_D4 (1ULL << 27)
#define BITMASK_E4 (1ULL << 28)
#define BITMASK_F4 (1ULL << 29)
#define BITMASK_G4 (1ULL << 30)
#define BITMASK_H4 (1ULL << 31)
#define BITMASK_A5 (1ULL << 32)
#define BITMASK_B5 (1ULL << 33)
#define BITMASK_C5 (1ULL << 34)
#define BITMASK_D5 (1ULL << 35)
#define BITMASK_E5 (1ULL << 36)
#define BITMASK_F5 (1ULL << 37)
#define BITMASK_G5 (1ULL << 38)
#define BITMASK_H5 (1ULL << 39)
#define BITMASK_A6 (1ULL << 40)
#define BITMASK_B6 (1ULL << 41)
#define BITMASK_C6 (1ULL << 42)
#define BITMASK_D6 (1ULL << 43)
#define BITMASK_E6 (1ULL << 44)
#define BITMASK_F6 (1ULL << 45)
#define BITMASK_G6 (1ULL << 46)
#define BITMASK_H6 (1ULL << 47)
#define BITMASK_A7 (1ULL << 48)
#define BITMASK_B7 (1ULL << 49)
#define BITMASK_C7 (1ULL << 50)
#define BITMASK_D7 (1ULL << 51)
#define BITMASK_E7 (1ULL << 52)
#define BITMASK_F7 (1ULL << 53)
#define BITMASK_G7 (1ULL << 54)
#define BITMASK_H7 (1ULL << 55)
#define BITMASK_A8 (1ULL << 56)
#define BITMASK_B8 (1ULL << 57)
#define BITMASK_C8 (1ULL << 58)
#define BITMASK_D8 (1ULL << 59)
#define BITMASK_E8 (1ULL << 60)
#define BITMASK_F8 (1ULL << 61)
#define BITMASK_G8 (1ULL << 62)
#define BITMASK_H8 (1ULL << 63)

#define INDEX_A1 0
#define INDEX_B1 1
#define INDEX_C1 2
#define INDEX_D1 3
#define INDEX_E1 4
#define INDEX_F1 5
#define INDEX_G1 6
#define INDEX_H1 7
#define INDEX_A2 8
#define INDEX_B2 9
#define INDEX_C2 10
#define INDEX_D2 11
#define INDEX_E2 12
#define INDEX_F2 13
#define INDEX_G2 14
#define INDEX_H2 15
#define INDEX_A3 16
#define INDEX_B3 17
#define INDEX_C3 18
#define INDEX_D3 19
#define INDEX_E3 20
#define INDEX_F3 21
#define INDEX_G3 22
#define INDEX_H3 23
#define INDEX_A4 24
#define INDEX_B4 25
#define INDEX_C4 26
#define INDEX_D4 27
#define INDEX_E4 28
#define INDEX_F4 29
#define INDEX_G4 30
#define INDEX_H4 31
#define INDEX_A5 32
#define INDEX_B5 33
#define INDEX_C5 34
#define INDEX_D5 35
#define INDEX_E5 36
#define INDEX_F5 37
#define INDEX_G5 38
#define INDEX_H5 39
#define INDEX_A6 40
#define INDEX_B6 41
#define INDEX_C6 42
#define INDEX_D6 43
#define INDEX_E6 44
#define INDEX_F6 45
#define INDEX_G6 46
#define INDEX_H6 47
#define INDEX_A7 48
#define INDEX_B7 49
#define INDEX_C7 50
#define INDEX_D7 51
#define INDEX_E7 52
#define INDEX_F7 53
#define INDEX_G7 54
#define INDEX_H7 55
#define INDEX_A8 56
#define INDEX_B8 57
#define INDEX_C8 58
#define INDEX_D8 59
#define INDEX_E8 60
#define INDEX_F8 61
#define INDEX_G8 62
#define INDEX_H8 63

#define  BITMASK_FILE_A             \
                (   BITMASK_A1 |    \
                    BITMASK_A2 |    \
                    BITMASK_A3 |    \
                    BITMASK_A4 |    \
                    BITMASK_A5 |    \
                    BITMASK_A6 |    \
                    BITMASK_A7 |    \
                    BITMASK_A8      \
                )

#define BITMASK_FILE_H              \
                (   BITMASK_H1 |    \
                    BITMASK_H2 |    \
                    BITMASK_H3 |    \
                    BITMASK_H4 |    \
                    BITMASK_H5 |    \
                    BITMASK_H6 |    \
                    BITMASK_H7 |    \
                    BITMASK_H8      \
                )


#define BITMASK_RANK_1              \
                (   BITMASK_A1 |    \
                    BITMASK_B1 |    \
                    BITMASK_C1 |    \
                    BITMASK_D1 |    \
                    BITMASK_E1 |    \
                    BITMASK_F1 |    \
                    BITMASK_G1 |    \
                    BITMASK_H1      \
                )

#define BITMASK_RANK_8              \
                (   BITMASK_A8 |    \
                    BITMASK_B8 |    \
                    BITMASK_C8 |    \
                    BITMASK_D8 |    \
                    BITMASK_E8 |    \
                    BITMASK_F8 |    \
                    BITMASK_G8 |    \
                    BITMASK_H8      \
                )

#define BITMASK_FRAME                   \
                (   BITMASK_RANK_1 |    \
                    BITMASK_RANK_8 |    \
                    BITMASK_FILE_A |    \
                    BITMASK_FILE_H      \
                )

#define BITMASK_UNIVERSE    (~0ULL)
#define BITMASK_NOT_FILE_A  (~BITMASK_FILE_A)
#define BITMASK_NOT_FILE_H  (~BITMASK_FILE_H)

#define ONE_EAST(b)          (((b) << 1) & BITMASK_NOT_FILE_A)
#define ONE_NORTH_EAST(b)    (((b) << 9) & BITMASK_NOT_FILE_A)
#define ONE_SOUTH_EAST(b)    (((b) >> 7) & BITMASK_NOT_FILE_A)
#define ONE_WEST(b)          (((b) >> 1) & BITMASK_NOT_FILE_H)
#define ONE_SOUTH_WEST(b)    (((b) >> 9) & BITMASK_NOT_FILE_H)
#define ONE_NORTH_WEST(b)    (((b) << 7) & BITMASK_NOT_FILE_H)
#define ONE_NORTH(b)         (((b) << 8))
#define ONE_SOUTH(b)         (((b) >> 8))

#define FILE_INDEX(i)        ((i) % 8)
#define RANK_INDEX(i)        ((i) / 8)

#define BITMASK_SQUARE(i)    (1ULL << (i))


/**
 * @brief Returns bitboard with ranks (rows) in reverse order
 * @param b
 * @return Transformed bitboard
 */
INLINE bitboard  reverseRanks    (const bitboard b) {
    //return board with ranks (rows) in reverse order
    return  ((b >> 56ULL) & (BITMASK_RANK_1))               |
            (((b >> 48ULL) & BITMASK_RANK_1) << 8ULL)       |
            (((b >> 40ULL) & BITMASK_RANK_1) << 16ULL)      |
            (((b >> 32ULL) & BITMASK_RANK_1) << 24ULL)      |
            (((b >> 24ULL) & BITMASK_RANK_1) << 32ULL)      |
            (((b >> 16ULL) & BITMASK_RANK_1) << 40ULL)      |
            (((b >> 8ULL) & BITMASK_RANK_1) << 48ULL)       |
            ((b & BITMASK_RANK_1) << 56ULL);
}

/**
 * @brief Flips around A1H8 diagonal
 * @param b
 * @return Transformed bitboard
 */
INLINE bitboard  flipDiagA1H8 (const bitboard b0) {
    //Flips around A1H8 diagonal
    static const bitboard k1 = 0x5500550055005500ULL;
    static const bitboard k2 = 0x3333000033330000ULL;
    static const bitboard k4 = 0x0f0f0f0f00000000ULL;

    bitboard b = b0;

    bitboard t = k4 & (b ^ (b << 28));
    b ^= t ^ (t >> 28);
    t = k2 & (b ^ (b << 14));
    b ^= t ^ (t >> 14);
    t = k1 & (b ^ (b << 7));
    b ^= t ^ (t >> 7);
    return b;
}

/**
 * @brief Mirrors the bitboard horizontally
 * @param b
 * @return Transformed bitboard
 */
INLINE bitboard  mirrorHorizontal(bitboard b0) {
    //mirrors the bitboard horizontally
    static const bitboard k1 = 0x5555555555555555ULL;
    static const bitboard k2 = 0x3333333333333333ULL;
    static const bitboard k4 = 0x0f0f0f0f0f0f0f0fULL;

    bitboard b = b0;

    b = ((b >> 1) & k1) | ((b & k1) << 1);
    b = ((b >> 2) & k2) | ((b & k2) << 2);
    b = ((b >> 4) & k4) | ((b & k4) << 4);
    return b;
}

bitboard bitmaskFromNotation(const char *notation);

extern const bitboard   BITMASK_RANK[8];
extern const bitboard   BITMASK_FILE[8];
extern const bitboard   BITMASK_A1H8[15];
extern const bitboard   BITMASK_A8H1[15];

/**
 * @brief bitboard2String
 * @param b
 * @param buffer
 * @param bufferSize
 * @return Buffer with stored string representation of the bitboard
 */
char *bitboard2str(const bitboard b, char *buffer, const int bufferSize);

/**
 * @brief getFieldNotation
 * @param index
 * @param buffer
 * @param bufferSize
 * @return Notation of a chessboard field
 */
char *fieldNotation(const int index, char *buffer, const int bufferSize);

#ifdef __cplusplus
}
#endif

#endif //SACHISTA_CHESS_BITBOARD_H

