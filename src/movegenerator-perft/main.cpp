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
#include <sstream>
#include <array>

#include "chessboard.h"
#include "utility.h"
#include "move.h"


struct DecimalSeparators : std::numpunct<char> {
    /* use space as separator */
    char do_thousands_sep() const { return ','; }

    /* digits are grouped by 3 digits each */
    std::string do_grouping() const { return "\3"; }
};


int main(int argc, char** args) {

    std::cout
            << "Welcome to "
            << ARCHITECTURE
            << " sachista-chess "
            << ARCHITECTURE << " "
            << IMPLEMENTATION_VERSION
            << " (" << IMPLEMENTATION_DATE << ") PERF TEST!"
            << std::endl
    ;

    std::cout << "See: http://chessprogramming.wikispaces.com/Perft" << std::endl << std::endl;

    int depth = 7;
    std::string fen = ChessBoard::STANDARD_BOARD_FEN;
    bool standardBoard = true;

    std::cout << "usage:               - running standard layout perft to the default depth of " << depth << std::endl;
    std::cout << "usage: [DEPTH]       - running standard layout perft to the given depth." << std::endl;
    std::cout << "usage: [DEPTH] [FEN] - running custom layout perft to the given depth." << std::endl;
    std::cout << std::endl;

    if(argc > 1) {
        //depth
        std::stringstream stream(args[1]);
        stream >> depth;
    }

    if(argc > 2) {
        fen = std::string(args[2]);
        standardBoard = false;
    }

    if(standardBoard) {
        std::cout << "Running PERFT for standard board for the depth " << depth << "..." << std::endl;
    } else {
        std::cout << "Running PERFT for custom board for the depth " << depth << ": " << fen << "..." << std::endl;
    }

    ChessBoard board(fen);

    if(board.zobristKey == 0) {
        std::cerr << "ERROR: Invalid FEN String - can not create ChessBoard!" << std::endl;
        return -1;
    }

    StopWatch stopWatch;
    uint64_t count = board.perft(depth);
    uint64_t speed = stopWatch.speedInSeconds(count);
    uint64_t duration = stopWatch.elapsedTimeInMilliseconds();

    std::cout.imbue(std::locale(std::locale(), new DecimalSeparators()));

    std::cout
            << "PERFT finished:" << std::endl
            << "   FEN  : " << fen << std::endl
            << "   depth: " << depth << std::endl
            << "   count: " << count << std::endl
            << "   time : " << (duration/1000) << " [seconds]" << std::endl
            << "   speed: " << speed << " [/second]" << std::endl
    ;

    return 0;
}
