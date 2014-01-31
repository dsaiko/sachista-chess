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

#ifndef SACHISTA_CHESS_MOVE_H
#define SACHISTA_CHESS_MOVE_H

#include "chesspiece.h"
#include "bitboard.h"

typedef struct Move {
    Piece piece           ;
    Piece promotionPiece  ;

    unsigned int    sourceIndex     ;
    unsigned int    targetIndex     ;

    int             isEnPassant     ;
} Move;

#ifdef __cplusplus
extern "C"{
#endif

extern char *move2str(Move *m, char *buffer, int bufferSize);

#ifdef __cplusplus
}
#endif

#endif //SACHISTA_CHESS_MOVE_H

