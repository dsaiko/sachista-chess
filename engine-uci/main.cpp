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

#include <iostream>
#include <thread>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <atomic>

#include "chessboard.h"
#include "uci.h"

std::mutex mutex_print;

std::atomic<int>  isAppRunning(1);
std::atomic<int>  isDebugMode(0);

std::vector<UCICommand> commands = {
    { "debug", commandDebug},
    { "help", commandHelp},
    { "isready", commandIsReady},
    { "perft", commandPerfT},
    { "quit", commandQuit},
    { "uci", commandUci},
    { "ucinewgame", commandUciNewGame},
};


#define info_command_message(msg) {                     \
 if(isDebugMode.load()) {                                \
      std::lock_guard<std::mutex> guard(mutex_print);   \
      printf("info debug command %s %s [", (msg), args[0].c_str());\
      for(int i=1; i<args.size(); i++) {\
          printf("%s", args[i].c_str());\
          if(i < args.size() - 1)\
              printf(",");\
      }\
      printf("]\n");\
      fflush(stdout);\
 }\
}

int main()
{
    println("Welcome to sachista-chess v. %s (%s) %s", IMPLEMENTATION_VERSION, IMPLEMENTATION_DATE, PLATFORM);

    initMovesGenerator();

    while(isAppRunning.load()) {

        std::string line = readLine();
        std::vector<std::string> args = split(line);

        if(args.size() > 0) {
            bool unknown = true;

            for(auto& command : commands){
                if(command.command == args[0]) {
                    unknown = false;
                    if(command.fce == commandQuit) {
                        command.fce(args);
                    } else {
                        std::thread([command, args](){

                            info_command_message("begin");

                            command.fce(args);

                            info_command_message("end");
                        }).detach();
                    }
                    break;
                }
            }

            if(unknown) {
                println("info unknown command: %s", line.c_str());
            }
        }
    }

    return 0;
}
