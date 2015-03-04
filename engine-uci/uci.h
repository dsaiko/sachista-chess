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

#ifndef SACHISTA_CHESS_UCI_H
#define SACHISTA_CHESS_UCI_H

#include <vector>
#include <string>
#include <thread>
#include <mutex>

/**
 *Command handler function
 */
typedef void (*CommandFce)(std::vector<std::string> args);

/**
  * Command definition structure
  */
struct UCICommand {
    std::string command;
    CommandFce fce;
};

extern std::mutex mutex_print;

#define println(...) {                              \
    std::lock_guard<std::mutex> guard(mutex_print); \
    printf(__VA_ARGS__);                            \
    printf("\n");                                   \
    fflush(stdout);                                 \
}

/** UCI COMMAND HANDLERS **/
void commandUci         (std::vector<std::string> args);
void commandUciNewGame  (std::vector<std::string> args);
void commandIsReady     (std::vector<std::string> args);
void commandPerfT       (std::vector<std::string> args);
void commandQuit        (std::vector<std::string> args);
void commandHelp        (std::vector<std::string> args);
void commandDebug        (std::vector<std::string> args);

/**
 * @brief readLine
 * @return trimmed line from stdin
 */
std::string             readLine();

/**
 * @brief split
 * @param txt
 * @return vector of string tokens
 */
std::vector<std::string> split(const std::string &txt);

#endif
