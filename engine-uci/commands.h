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

#ifndef SACHISTA_CHESS_COMMANDS_H
#define SACHISTA_CHESS_COMMANDS_H


#ifdef __cplusplus
extern "C"{
#endif

void processCommands();

void trim(char * s);
void compressSpaces(char *str);
char *readLine();
char *readArg(char **args);

void commandUci(char *args);
void commandIsReady(char *args);
void commandUciNewGame(char *args);
void commandPerfT(char *args);

#ifdef __cplusplus
}
#endif

#endif
