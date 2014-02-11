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

#include <stdio.h>
#include "bitboard.h"
#include "utils.h"

/*
 * These constants were pregenerated
 */
const bitboard BITMASK_RANK[8]      =   {255ULL, 65280ULL, 16711680ULL, 4278190080ULL, 1095216660480ULL, 280375465082880ULL, 71776119061217280ULL, 18374686479671623680ULL};
const bitboard BITMASK_FILE[8]      =   {72340172838076673ULL, 144680345676153346ULL, 289360691352306692ULL, 578721382704613384ULL, 1157442765409226768ULL, 2314885530818453536ULL, 4629771061636907072ULL, 9259542123273814144ULL};
const bitboard BITMASK_A1H8[15]     =   {72057594037927936ULL, 144396663052566528ULL, 288794425616760832ULL, 577588855528488960ULL, 1155177711073755136ULL, 2310355422147575808ULL, 4620710844295151872ULL, 9241421688590303745ULL, 36099303471055874ULL, 141012904183812ULL, 550831656968ULL, 2151686160ULL, 8405024ULL, 32832ULL, 128ULL};
const bitboard BITMASK_A8H1[15]     =   {1ULL, 258ULL, 66052ULL, 16909320ULL, 4328785936ULL, 1108169199648ULL, 283691315109952ULL, 72624976668147840ULL, 145249953336295424ULL, 290499906672525312ULL, 580999813328273408ULL, 1161999622361579520ULL, 2323998145211531264ULL, 4647714815446351872ULL, 9223372036854775808ULL};

char *bitboard2str(const bitboard b, char *buffer, const int bufferSize)
{
    //reinitialize buffer to empty string
    if(bufferSize < 1) return buffer;
    buffer[0] = 0;

    static const char header[] = "  a b c d e f g h\n";

    //we need this for printing
    bitboard reversedBoard = reverseRanks(b);

    //header
    appendString(buffer, bufferSize, header);

    for (int i = 0; i < 64; i++) {
        if ((i % 8) == 0) {
            if (i > 0) {
                //print right column digit
                appendChars(buffer, bufferSize, 2, '0' + 9 - (i / 8), '\n');
            }
            //print left column digit
            appendChars(buffer, bufferSize, 2, '0' + 8 - (i / 8), ' ');
        }
        if(reversedBoard & (1ULL << i)) {
            appendString(buffer, bufferSize, "x ");
        } else {
            appendString(buffer, bufferSize, "- ");
        }
    }

    //last right column digit
    appendString(buffer, bufferSize, "1\n");

    //footer
    appendString(buffer, bufferSize, header);

    return buffer;
}

char *fieldNotation(const int index, char *buffer, const int bufferSize) {
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


