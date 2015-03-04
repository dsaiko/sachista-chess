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

#ifndef SACHISTA_CHESS_POPCOUNT_H
#define SACHISTA_CHESS_POPCOUNT_H


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

#if defined(_MSC_VER) && defined(__INTEL_COMPILER)
    #define popCount(b) _mm_popcnt_u64(b)
#elif defined(_MSC_VER)
    #define popCount(b) __popcnt64(b)
#elif defined(__x86_64__)

INLINE int popCount(bitboard b) {
    __asm__("popcnt %1, %0" : "=r" (b) : "r" (b));
    return (int) b;
}

#else

INLINE int popCount(bitboard b) {
    static const uint64_t k1 = 0x5555555555555555ULL; /*  -1/3   */
    static const uint64_t k2 = 0x3333333333333333ULL; /*  -1/5   */
    static const uint64_t k4 = 0x0f0f0f0f0f0f0f0fULL; /*  -1/17  */

    b =  b       - ((b >> 1)  & k1); /* put count of each 2 bits into those 2 bits */
    b = (b & k2) + ((b >> 2)  & k2); /* put count of each 4 bits into those 4 bits */
    b = (b       +  (b >> 4)) & k4 ; /* put count of each 8 bits into those 8 bits */
    b += b >>  8;  /* put count of each 16 bits into their lowest 8 bits */
    b += b >> 16;  /* put count of each 32 bits into their lowest 8 bits */
    b += b >> 32;  /* put count of the final 64 bits into the lowest 8 bits */
    return (int) b & 255;
}

#endif


#ifdef __cplusplus
}
#endif

#endif //SACHISTA_CHESS_POPCOUNT_H

