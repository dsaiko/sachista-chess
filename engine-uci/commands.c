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
#include "commands.h"

volatile int running = 1;

typedef void (*CommandFce)(char *args);

typedef struct UCICommand {
    char *command;
    CommandFce fce;
} UCICommand;


void processCommands() {
    UCICommand commands[] = {
        { "isready", &commandIsReady },
        { "ucinewgame", &commandUciNewGame },
        { "uci", &commandUci },
        { "perft", &commandPerfT }
    };

    #pragma omp parallel
    {
        #pragma omp single
        {

            while(running) {
                char *line = readLine();

                //get first word
                char *args = line;
                readArg(&args);

                UCICommand *command = NULL;
                for(int i=0; i < sizeof(commands) / sizeof(UCICommand); i++) {
                    if(strcmp(commands[i].command, line) == 0) {
                        command = &commands[i];
                        break;
                    }
                }
                if(command) {
                            #pragma omp task
                            {
                                command->fce(args);
                                free(line);
                            }
                } else {
                    if(strcmp("quit", line) == 0) {
                        running = 0;
                        #pragma omp flush(running)
                    } else {
                        if(strlen(line) > 0) {
                            #pragma omp critical (print)
                            printf("Unknown command: %s\n", line);
                        }
                    }
                    free(line);
                }
            }
        }
    }

}
