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


#include <iostream>
#include <stdio.h>
#include <thread>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "utils.h"
#include "chessboard.h"
#include "uci.h"

volatile int running = 1;

UCICommand commands[] = {
    { "isready", commandIsReady},
    { "ucinewgame", commandUciNewGame},
    { "uci", commandUci},
    { "perft", commandPerfT}
};

void hello(char *args){
    printf("%s\n",args);
    std::cout << "Hello from thread: " << args << "!" << std::endl;
}


int main()
{
    printf("Welcome to sachista-chess v. %s (%s) %s\n", IMPLEMENTATION_VERSION, IMPLEMENTATION_DATE, PLATFORM);

    initMovesGenerator();

    while(running) {

        std::string line = readLine();
        std::vector<std::string> args = split(line);

        if(args.size() > 0) {
            UCICommand *command = NULL;
            for(uint i=0; i < sizeof(commands) / sizeof(UCICommand); i++) {
                if(commands[i].command == args[0]) {
                    command = &commands[i];
                    std::thread(command->fce, args).detach();
                    break;
                }
            }

            if(!command) {
                if(args[0] == "quit" || args[0] == "exit") {
                    running = 0;
                } else {
                    if(line.length() > 0) {
                        printf("Unknown command: %s\n", line.c_str());
                    }
                }
            }
        }
    }

    return 0;
}
