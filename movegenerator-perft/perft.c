/*
  sachista-chess copyright (C) 2014 Dusan Saiko

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


unsigned long long timeval_diff(struct timeval *start_time,  struct timeval *end_time)
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

   printf("Running perft for standard board layout for 7 plies.\n");
   printf("Test should run aroun 5 minute.\n");
   printf("See: http://chessprogramming.wikispaces.com/Perft\n\n");

   initMovesGenerator();

   struct timeval start, end;

   int i;
   for (i = 1; i <= 7; i++) {

        ChessBoard board = standardBoard;

        gettimeofday(&start, NULL);

        unsigned long long n =  perft(&board, i);

        gettimeofday(&end, NULL);

        double t = (timeval_diff(&start, &end) +1 )/ 1000.0;

        printf("Generated %d plies. Performance: %fs, %llu nodes / seconds. Total combinations: %llu\n",
                i,
                ((double) t / 1000.0),
                (unsigned long long) ((double) n / ((double) t / 1000.0)),
                n
        );

        fflush(stdout);
   }

    return 0;
}
