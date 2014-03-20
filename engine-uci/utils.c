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

void trim(char * s) {
    char * p = s;
    int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
}

void compressSpaces(char *str)
{
    char *dst = str;
    for (; *str; ++str) {
        *dst++ = *str;

        if (isspace(*str)) {
            do ++str;

            while (isspace(*str));

            --str;
        }
    }

    *dst = 0;
}

/**
 * @brief readLine
 * @return line with terminating \n
 */
char *readLine() {
    int  bufferSize = 2;
    char *line = malloc(bufferSize);
    char *p = line;

    int c;

    if(!line) return NULL;

    while(1) {
        c = fgetc(stdin);
        if(c == EOF) break;

        if((p - line) + 1 >= bufferSize) {
            char *line2 = realloc(line, bufferSize *= 2);

            if(!line2) {
                free(line);
                return NULL;
            }

            p = line2 + (p - line);
            line = line2;
        }

        if((*p++ = c) == '\n') break;
    }
    *p = '\0';

    trim(line);
    compressSpaces(line);

    return line;
}

char *readArg(char **args) {
    if(**args == 0) return 0;

    char *head = *args;

    while(**args) {
        if(isspace(**args)) {
            **args=0;
        } else {
            (*args)++;
        }
    }
    (*args)++;

    return head;
}

