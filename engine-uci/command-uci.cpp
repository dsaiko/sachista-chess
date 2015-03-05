/*
  sachista-chess copyright (C) 2014,2015 dusan.saiko@gmail.com

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
#include "chessboard.h"
#include "uci.h"

void commandUci(std::vector<std::string> args) {
    std::lock_guard<std::mutex> guard(mutex_print);
    printf("id name sachista-chess v. %s (%s) %s\n", IMPLEMENTATION_VERSION, IMPLEMENTATION_DATE, PLATFORM);
    printf("id author Dusan Saiko\n");
    printf("\nuciok\n");
    fflush(stdout);
}
