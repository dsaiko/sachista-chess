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
#include "chessboard.h"

#include "omp.h"


unsigned long long timediff(const struct timeval *start_time,  const struct timeval *end_time)
{
  struct timeval difference;

  difference.tv_sec = (end_time->tv_sec)  - (start_time->tv_sec);
  difference.tv_usec= (end_time->tv_usec) - (start_time->tv_usec);

  /* Using while instead of if below makes the code slightly more robust. */

  while(difference.tv_usec < 0)
  {
    difference.tv_usec+=1000000;
    difference.tv_sec -=1;
  }

  return 1000000ULL * difference.tv_sec + difference.tv_usec;
}


int main() {
#if defined(__i386__)
    char architecture[] = "x86";
#elif defined(__x86_64__)
    char architecture[] = "x64";
#else
    char architecture[] = "UnknownArchitecture";
#endif

   printf("Welcome to %s sachista-chess %s (%s) perft!\n\n",
          architecture,
          IMPLEMENTATION_VERSION,
          IMPLEMENTATION_DATE
   );

   printf("Running perft for standard board layout for 6 plies.\n");
   printf("See: http://chessprogramming.wikispaces.com/Perft\n\n");

   initMovesGenerator();

   struct timeval start, end;

   int depth = 6;

   ChessBoard board = standardBoard;


   gettimeofday(&start, NULL);

   Move moves[MAX_MOVES_ARR_SIZE];
   Move *pointer = moves;
   ChessBoardComputedInfo boardInfo = computeInfo(&board);
   generateMoves(&board, &boardInfo, &pointer);

   const int  count = pointer - moves;
   unsigned long long results[count];

   #pragma omp parallel for
   for(int i = 0; i < count; i++) {
       ChessBoard nextBoard = board;
       Move *move = moves + i;
       makeMove(&nextBoard, boardInfo.allPieces, move);
       if(isNotUnderCheck(&nextBoard, nextBoard.nextMove)) {
           results[i] = perft(&nextBoard, depth -1);
       } else {
           results[i] = 0;
       }
   }

   unsigned long long n =  0;
   for(int i=0; i< count; i++) {
       n += results[i];
   }

   gettimeofday(&end, NULL);

   double t = (timediff(&start, &end) +1 )/ 1000.0;

   printf("Generated %d plies. Performance: %fs, %llu nodes / seconds. Total combinations: %llu\n",
            depth,
            ((double) t / 1000.0),
            (unsigned long long) ((double) n / ((double) t / 1000.0)),
            n
   );

   return 0;
}
