/*
  sachista-chess copyright (C) 2014 Dusan Saiko

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

#ifndef SACHISTA_CHESS_BITSCAN_H
#define SACHISTA_CHESS_BITSCAN_H


#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "bitboard.h"

#ifdef _MSC_VER
#include <intrin.h>
#endif

#ifdef __cplusplus
extern "C"{
#endif

#define INLINE  inline __attribute__((always_inline))

#ifdef _MSC_VER
INLINE int bitScan(bitboard b) {
    int r = 0;
    _BitScanForward64(&r, b);
    return r;
}
#elif defined(__x86_64__)
INLINE int bitScan(bitboard b) {
    __asm__("bsfq %1, %0" : "=r" (b) : "rm" (b));
    return (int) b;
}
#else

static const int lsb_64_table[64] =
{
   63, 30,  3, 32, 59, 14, 11, 33,
   60, 24, 50,  9, 55, 19, 21, 34,
   61, 29,  2, 53, 51, 23, 41, 18,
   56, 28,  1, 43, 46, 27,  0, 35,
   62, 31, 58,  4,  5, 49, 54,  6,
   15, 52, 12, 40,  7, 42, 45, 16,
   25, 57, 48, 13, 10, 39,  8, 44,
   20, 47, 38, 22, 17, 37, 36, 26
};

/**
 * bitScanForward
 * @author Matt Taylor (2003)
 * @param bb bitboard to scan
 * @precondition bb != 0
 * @return index (0..63) of least significant one bit
 */
INLINE int bitScan(bitboard b) {
   unsigned int folded;
   b ^= b - 1;
   folded = (int) b ^ (b >> 32);
   return lsb_64_table[folded * 0x78291ACF >> 26];
}
#endif

#define bitScanPop(b)                                   \
({                                                      \
    const int i = bitScan(b);                           \
    b &= b - 1;                                         \
    i;                                                  \
})


#ifdef __cplusplus
}
#endif


#endif //SACHISTA_CHESS_BITSCAN_H
