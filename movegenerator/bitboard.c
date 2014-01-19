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
const bitboard BITMASK_SQUARE[64]   =   {1ULL, 2ULL, 4ULL, 8ULL, 16ULL, 32ULL, 64ULL, 128ULL, 256ULL, 512ULL, 1024ULL, 2048ULL, 4096ULL, 8192ULL, 16384ULL, 32768ULL, 65536ULL, 131072ULL, 262144ULL, 524288ULL, 1048576ULL, 2097152ULL, 4194304ULL, 8388608ULL, 16777216ULL, 33554432ULL, 67108864ULL, 134217728ULL, 268435456ULL, 536870912ULL, 1073741824ULL, 2147483648ULL, 4294967296ULL, 8589934592ULL, 17179869184ULL, 34359738368ULL, 68719476736ULL, 137438953472ULL, 274877906944ULL, 549755813888ULL, 1099511627776ULL, 2199023255552ULL, 4398046511104ULL, 8796093022208ULL, 17592186044416ULL, 35184372088832ULL, 70368744177664ULL, 140737488355328ULL, 281474976710656ULL, 562949953421312ULL, 1125899906842624ULL, 2251799813685248ULL, 4503599627370496ULL, 9007199254740992ULL, 18014398509481984ULL, 36028797018963968ULL, 72057594037927936ULL, 144115188075855872ULL, 288230376151711744ULL, 576460752303423488ULL, 1152921504606846976ULL, 2305843009213693952ULL, 4611686018427387904ULL, 9223372036854775808ULL};
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
    return BITMASK_SQUARE[(notation[0] - 'a') + ((notation[1] - '1') << 3)];
}

