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
#include "uci.h"
#include "utils.h"
#include "perft.h"

void commandPerfT(std::vector<std::string> args) {
    int depth = 6;
    if(args.size() > 1) {
        depth = atoi(args[1].c_str());
    }

    println("info perft running standard layout perft for depth %d", depth);
    fflush(stdout);

    struct timeval start, end;

    gettimeofday(&start, NULL);

    ChessBoard board = standardBoard();
    unsigned long long result = 0;

    result = perft(&board, depth);

    gettimeofday(&end, NULL);
    double t = (timediff(&start, &end) +1 )/ 1000.0;

    println("info perft total nodes at depth %d: %llu; time: %fs; %llu nodes/seconds.",
             depth,
             result,
             ((double) t / 1000.0),
             (unsigned long long) ((double) result / ((double) t / 1000.0))
    );
}
