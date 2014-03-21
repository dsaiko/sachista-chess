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

#ifndef SACHISTA_CHESS_UCI_H
#define SACHISTA_CHESS_UCI_H

#include <vector>
#include <string>

typedef void (*CommandFce)(std::vector<std::string> args);

typedef struct UCICommand {
    std::string command;
    CommandFce fce;
} UCICommand;


void commandUci(std::vector<std::string> args);
void commandUciNewGame(std::vector<std::string> args);
void commandIsReady(std::vector<std::string> args);
void commandPerfT(std::vector<std::string> args);

std::string readLine();
std::vector<std::string> split(const std::string &txt);

#endif
