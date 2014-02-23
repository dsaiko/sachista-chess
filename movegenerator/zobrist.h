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
#include <string.h>
#include <stdarg.h>
#include "utils.h"

#ifndef SACHISTA_CHESS_ZOBRIST_H
#define SACHISTA_CHESS_ZOBRIST_H

uint64_t Z_PIECES[2][7][64];
uint64_t Z_CASTLING[2][4];
uint64_t Z_ENPASSANT[64];
uint64_t Z_SIDE[2];

#endif
