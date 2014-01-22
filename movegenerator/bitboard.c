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

void outputstr(char *buffer, const int bufferSize, int *position, const char *str);
void outputchar(char *buffer, const int bufferSize, int *position, const char c);

/*
 * These constants were pregenerated
 */
const bitboard BITMASK_RANK[8]      =   {255ULL, 65280ULL, 16711680ULL, 4278190080ULL, 1095216660480ULL, 280375465082880ULL, 71776119061217280ULL, 18374686479671623680ULL};
const bitboard BITMASK_FILE[8]      =   {72340172838076673ULL, 144680345676153346ULL, 289360691352306692ULL, 578721382704613384ULL, 1157442765409226768ULL, 2314885530818453536ULL, 4629771061636907072ULL, 9259542123273814144ULL};
const bitboard BITMASK_A1H8[15]     =   {72057594037927936ULL, 144396663052566528ULL, 288794425616760832ULL, 577588855528488960ULL, 1155177711073755136ULL, 2310355422147575808ULL, 4620710844295151872ULL, 9241421688590303745ULL, 36099303471055874ULL, 141012904183812ULL, 550831656968ULL, 2151686160ULL, 8405024ULL, 32832ULL, 128ULL};
const bitboard BITMASK_A8H1[15]     =   {1ULL, 258ULL, 66052ULL, 16909320ULL, 4328785936ULL, 1108169199648ULL, 283691315109952ULL, 72624976668147840ULL, 145249953336295424ULL, 290499906672525312ULL, 580999813328273408ULL, 1161999622361579520ULL, 2323998145211531264ULL, 4647714815446351872ULL, 9223372036854775808ULL};

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

    bitboard t = k4 & (b ^ (b << 28));
    b ^= t ^ (t >> 28);
    t = k2 & (b ^ (b << 14));
    b ^= t ^ (t >> 14);
    t = k1 & (b ^ (b << 7));
    b ^= t ^ (t >> 7);
    return b;
}


bitboard mirrorHorizontal(bitboard b) {
    //mirrors the bitboard horizontally
    static const bitboard k1 = 0x5555555555555555ULL;
    static const bitboard k2 = 0x3333333333333333ULL;
    static const bitboard k4 = 0x0f0f0f0f0f0f0f0fULL;

    b = ((b >> 1) & k1) | ((b & k1) << 1);
    b = ((b >> 2) & k2) | ((b & k2) << 2);
    b = ((b >> 4) & k4) | ((b & k4) << 4);
    return b;
}


char *bitboard2str(bitboard b, char *buffer, int bufferSize)
{
    char header[] = "  a b c d e f g h\n";
    int position = 0;

    //we need this for printing
    b = reverseRanks(b);

    //header
    outputstr(buffer, bufferSize, &position, header);

    char c[] = "\0\0";

    for (int i = 0; i < 64; i++) {
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
        if(b & (1ULL << i)) {
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
    if(position < bufferSize)
        buffer[position] = '\0';
    return buffer;
}

char *fieldNotation(int index, char *buffer, int bufferSize) {
    if(bufferSize < 3) return buffer;

    buffer[0] = 'a' + (index % 8);
    buffer[1] = '1' + (index / 8);
    buffer[2] = '\0';

    return buffer;
}

bitboard bitmaskFromNotation(const char *notation) {
    if(strlen(notation) != 2) return 0;
    return BITMASK_SQUARE((notation[0] - 'a') + ((notation[1] - '1') << 3));
}


#ifdef __EXTERN_BITSCAN__

const int lsb_64_table[64] =
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
int bitScan(bitboard b) {
   unsigned int folded;
   b ^= b - 1;
   folded = (int) b ^ (b >> 32);
   return lsb_64_table[folded * 0x78291ACF >> 26];
}
#endif

#ifdef __EXTERN_POPCOUNT__

const unsigned long long k1 = 0x5555555555555555ULL; /*  -1/3   */
const unsigned long long k2 = 0x3333333333333333ULL; /*  -1/5   */
const unsigned long long k4 = 0x0f0f0f0f0f0f0f0fULL; /*  -1/17  */
const unsigned long long kf = 0x0101010101010101ULL; /*  -1/255 */

int popCount(bitboard b)
{
    b =  b       - ((b >> 1)  & k1); /* put count of each 2 bits into those 2 bits */
    b = (b & k2) + ((b >> 2)  & k2); /* put count of each 4 bits into those 4 bits */
    b = (b       +  (b >> 4)) & k4 ; /* put count of each 8 bits into those 8 bits */
    b += b >>  8;  /* put count of each 16 bits into their lowest 8 bits */
    b += b >> 16;  /* put count of each 32 bits into their lowest 8 bits */
    b += b >> 32;  /* put count of the final 64 bits into the lowest 8 bits */
    return (int) b & 255;
}

#endif

