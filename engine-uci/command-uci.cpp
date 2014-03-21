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
#include <sys/time.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "chessboard.h"
#include "utils.h"
#include "uci.h"

void commandUci(std::vector<std::string> args) {
    printf("id name ");
    printf("id name sachista-chess v. %s (%s) %s\n", IMPLEMENTATION_VERSION, IMPLEMENTATION_DATE, PLATFORM);
    printf("id author Dusan Saiko\n");
    printf("\n");
    printf("uciok\n");
}
