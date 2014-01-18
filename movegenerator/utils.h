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

#ifndef SACHISTA_CHESS_UTILS_H
#define SACHISTA_CHESS_UTILS_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>


/**
 * @brief Copies str into given possition of buffer
 * @param buffer
 * @param bufferSize
 * @param position
 * @param str
 */
extern void outputstr(char *buffer, const int bufferSize, int *position, const char *str);
extern void outputchar(char *buffer, const int bufferSize, int *position, const char c);


#endif
