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
#include <string.h>

void outputstr(char *buffer, const int bufferSize, int *position, const char *str)
{
    int len = strlen(str);
    if(*position + len < bufferSize) {
        strncpy(buffer + *position, str, len);
        *position += len;
    }
}

void outputchar(char *buffer, const int bufferSize, int *position, const char c)
{
      if(*position + 1 < bufferSize) {
          buffer[*position] = c;
          *position += 1;
      }
}

