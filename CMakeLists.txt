#  sachista-chess copyright (C) 2014,2015 dusan.saiko@gmail.com

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


cmake_minimum_required      (VERSION 2.8.7)
project                     (SACHISTA_CHESS)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

enable_language             (C)
enable_language		        (CXX)

add_subdirectory            (movegenerator)
add_subdirectory            (movegenerator-test)

#add_subdirectory	        (engine-uci)
#add_subdirectory            (movegenerator-perft)


