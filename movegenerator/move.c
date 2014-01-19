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

#include "bitboard.h"
#include "move.h"

void outputstr(char *buffer, const int bufferSize, int *position, const char *str);
void outputchar(char *buffer, const int bufferSize, int *position, const char c);

char *move2str(struct move *m, char *buffer, int bufferSize) {
    int position = 0;

    char notation[3];

    fieldNotation(m->sourceIndex, notation, sizeof(notation) / sizeof(char));
    outputstr(buffer, bufferSize, &position, notation);

    fieldNotation(m->targetIndex, notation, sizeof(notation) / sizeof(char));
    outputstr(buffer, bufferSize, &position, notation);

    if(m->promotionPiece != NO_PIECE) {
        notation[0] = m->promotionPiece;
        notation[1] = '\0';
        outputstr(buffer, bufferSize, &position, notation);
    }

    if(position < bufferSize)
        buffer[position] = 0;
    return buffer;
}

