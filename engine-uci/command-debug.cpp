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
#include <atomic>

#include "chessboard.h"
#include "uci.h"
#include "utils.h"
#include "perft.h"


extern std::atomic<int>  isDebugMode;

void commandDebug(std::vector<std::string> args) {

    if(args.size() > 1) {
        std::string flag = args[1];
        if("on" == flag) {
            isDebugMode = 1;
        } else {
            isDebugMode = 0;
        }
    }

    println("info debug %s", isDebugMode.load() ? "on" : "off");
}
