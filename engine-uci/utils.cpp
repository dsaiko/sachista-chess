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
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstring>

#include "utils.h"
#include "chessboard.h"
#include "uci.h"

/**
 * @brief Trims the string from both sides
 * @param s
 */
void trim(char * s) {
    if(!s) return;

    char * p = s;
    int l = strlen(p);
    if(l == 0) return;

    while(l > 0 && isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
}

/**
 * @brief Removes double spaces from string
 * @param str
 */
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
 * @brief Read input line, trims it, removes double spaces
 * @return line with terminating
 */
std::string readLine() {

    std::string input;
    std::getline (std::cin, input);


    char line[input.length()+1];
    std::strcpy (line, input.c_str());

    trim(line);
    compressSpaces(line);

    return std::string(line);
}


/**
 * @brief split
 * @param txt
 * @return vector of string tokens
 */
std::vector<std::string> split(const std::string &txt)
{
    using namespace std;
    istringstream iss(txt);
    vector<string> tokens;
    copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter<vector<string> >(tokens));

    return tokens;
}
