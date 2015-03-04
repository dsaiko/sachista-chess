#  sachista-chess copyright (C) 2014 dusan.saiko@gmail.com

#  sachista-chess is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.

#  sachista-chess is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

include_directories     (${SACHISTA_CHESS_SOURCE_DIR}/movegenerator)
link_directories        (${SACHISTA_CHESS_SOURCE_DIR}/movegenerator)


add_executable (
    sachista-chess
    main
    uci
    utils
    command-perft
    command-uci
    command-ucinewgame
    command-isready
    command-quit
    command-help
    command-debug
)

target_link_libraries(sachista-chess sachista-movegenerator)

