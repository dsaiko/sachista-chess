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

#include <stdio.h>
#include "bitboard.h"

/*
 * These constants were pregenerated
 */
const bitboard BITMASK_SQUARE[64]   =   {1LLU, 2LLU, 4LLU, 8LLU, 16LLU, 32LLU, 64LLU, 128LLU, 256LLU, 512LLU, 1024LLU, 2048LLU, 4096LLU, 8192LLU, 16384LLU, 32768LLU, 65536LLU, 131072LLU, 262144LLU, 524288LLU, 1048576LLU, 2097152LLU, 4194304LLU, 8388608LLU, 16777216LLU, 33554432LLU, 67108864LLU, 134217728LLU, 268435456LLU, 536870912LLU, 1073741824LLU, 2147483648LLU, 4294967296LLU, 8589934592LLU, 17179869184LLU, 34359738368LLU, 68719476736LLU, 137438953472LLU, 274877906944LLU, 549755813888LLU, 1099511627776LLU, 2199023255552LLU, 4398046511104LLU, 8796093022208LLU, 17592186044416LLU, 35184372088832LLU, 70368744177664LLU, 140737488355328LLU, 281474976710656LLU, 562949953421312LLU, 1125899906842624LLU, 2251799813685248LLU, 4503599627370496LLU, 9007199254740992LLU, 18014398509481984LLU, 36028797018963968LLU, 72057594037927936LLU, 144115188075855872LLU, 288230376151711744LLU, 576460752303423488LLU, 1152921504606846976LLU, 2305843009213693952LLU, 4611686018427387904LLU, 9223372036854775808LLU};
const bitboard BITMASK_RANK[8]      =   {255LLU, 65280LLU, 16711680LLU, 4278190080LLU, 1095216660480LLU, 280375465082880LLU, 71776119061217280LLU, 18374686479671623680LLU};
const bitboard BITMASK_FILE[8]      =   {72340172838076673LLU, 144680345676153346LLU, 289360691352306692LLU, 578721382704613384LLU, 1157442765409226768LLU, 2314885530818453536LLU, 4629771061636907072LLU, 9259542123273814144LLU};
const bitboard BITMASK_A1H8[15]     =   {72057594037927936LLU, 144396663052566528LLU, 288794425616760832LLU, 577588855528488960LLU, 1155177711073755136LLU, 2310355422147575808LLU, 4620710844295151872LLU, 9241421688590303745LLU, 36099303471055874LLU, 141012904183812LLU, 550831656968LLU, 2151686160LLU, 8405024LLU, 32832LLU, 128LLU};
const bitboard BITMASK_A8H1[15]     =   {1LLU, 258LLU, 66052LLU, 16909320LLU, 4328785936LLU, 1108169199648LLU, 283691315109952LLU, 72624976668147840LLU, 145249953336295424LLU, 290499906672525312LLU, 580999813328273408LLU, 1161999622361579520LLU, 2323998145211531264LLU, 4647714815446351872LLU, 9223372036854775808LLU};

bitboard reverseRanks(bitboard b) {
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


bitboard flipDiagA1H8(bitboard b) {
    //Flips around A1H8 diagonal
    static const bitboard k1 = 0x5500550055005500ULL;
    static const bitboard k2 = 0x3333000033330000ULL;
    static const bitboard k4 = 0x0f0f0f0f00000000ULL;

    long t = k4 & (b ^ (b << 28));
    b ^= t ^ (t >> 28);
    t = k2 & (b ^ (b << 14));
    b ^= t ^ (t >> 14);
    t = k1 & (b ^ (b << 7));
    b ^= t ^ (t >> 7);
    return b;
}


bitboard mirrorHorizontal(bitboard b) {
    //mirrors the bitboard horizontally
    static const bitboard k1 = 0x5555555555555555L;
    static const bitboard k2 = 0x3333333333333333L;
    static const bitboard k4 = 0x0f0f0f0f0f0f0f0fL;

    b = ((b >> 1) & k1) | ((b & k1) << 1);
    b = ((b >> 2) & k2) | ((b & k2) << 2);
    b = ((b >> 4) & k4) | ((b & k4) << 4);
    return b;
}

int getPopCount (bitboard b) {
#if defined(_MSC_VER) && defined(__INTEL_COMPILER)
  return _mm_popcnt_u64(b);
#elif defined(_MSC_VER)
  return (int)__popcnt64(b);
#else
  __asm__("popcnt %1, %0" : "=r" (b) : "r" (b));
  return b;
#endif
}

int bitScan(bitboard b) {
    asm ("bsfq %0, %0" : "=r" (b) : "0" (b)); return (int) b;
}

char *bitboard2String(bitboard b, char *buffer, int bufferSize)
{
    char header[] = "  a b c d e f g h\n";
    int position = 0;

    //we need this for printing
    b = reverseRanks(b);

    //header
    outputstr(buffer, bufferSize, &position, header);

    int i;
    char c[] = "\0\0";

    for (i = 0; i < 64; i++) {
        if ((i % 8) == 0) {
            if (i > 0) {
                //print right column digit
                c[0] = '0' + 9 - (i / 8);
                outputstr(buffer, bufferSize, &position, c);
                outputstr(buffer, bufferSize, &position, "\n");
            }
            //print left column digit
            c[0] = '0' + 8 - (i / 8);
            outputstr(buffer, bufferSize, &position, c);
            outputstr(buffer, bufferSize, &position, " ");
        }
        if((b & (1L << i)) != 0) {
            outputstr(buffer, bufferSize, &position, "x ");
        } else {
            outputstr(buffer, bufferSize, &position, "- ");
        }
    }

    //last right column digit
    outputstr(buffer, bufferSize, &position, "1\n");

    //footer
    outputstr(buffer, bufferSize, &position, header);

    //end string
    buffer[position] = '\0';
    return buffer;
}

char *getFieldNotation(int index, char *buffer, int bufferSize) {
    char notation[3];
    int position = 0;

    notation[0] = 'a' + (index % 8);
    notation[1] = '1' + (index / 8);
    notation[2] = '\0';

    outputstr(buffer, bufferSize, &position, notation);
    buffer[position] = '\0';

    return buffer;
}

