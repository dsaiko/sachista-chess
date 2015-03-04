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
#include <omp.h>
#include <string.h>

#include "chessboard.h"
#include "utils.h"
#include "zobrist.h"

#define CACHESIZE     (16*1024*1024)

typedef struct {
    uint64_t hashCode;
    uint64_t nodeCount;
    int      depth;
} CacheEntry;

/**
 * @brief This is a perft worker
 * @param board
 * @param depth
 * @param cache Shared cache, needs OMP synchronization
 * @return number of legal moves
 */
uint64_t minimax(const ChessBoard *board, const int depth, CacheEntry *cache)
{
    //compute directly
    if(depth < 1) return 1;

    const uint64_t hashCode = board->zobristKey;

    CacheEntry *cacheEntry = (cache + ((CACHESIZE - 1) & hashCode));

    uint64_t count = 0;

    //retrieve info from cache
    #pragma omp critical (cacheupdate)
    {
        if(cacheEntry->hashCode == hashCode && cacheEntry->depth == depth) {
            count = cacheEntry->nodeCount;
        }
    }

    //return cached value
    if(count) return count;

    Move moves[MAX_MOVES_ARR_SIZE];
    Move *pointer = moves;

    ChessBoardComputedInfo boardInfo = computeInfo(board);
    generateMoves(board, &boardInfo, &pointer);

    Move *i = moves;

    ChessBoard nextBoard = *board;

    while(i < pointer) {
        //make move
        makeMove(&nextBoard, boardInfo.allPieces, i ++);

        //is move legal?
        if(isNotUnderCheck(&nextBoard, nextBoard.nextMove)) {
            count += minimax(&nextBoard, depth -1, cache);
        }

        //undo move - reset the move back
        if(i < pointer)
            nextBoard = *board;
    }

    #pragma omp critical (cacheupdate)
    {
        cacheEntry->hashCode = hashCode;
        cacheEntry->nodeCount = count;
        cacheEntry->depth = depth;
    }

    return count;
}

/**
 * @brief Method divides first moves into parallel tasks
 * @param board
 * @param depth
 * @return legal move count
 */
uint64_t perft(const ChessBoard *board, const int depth)
{
    if(depth < 1) return 1;

    uint64_t count = 0;

    Move moves[MAX_MOVES_ARR_SIZE];
    Move *pointer = moves;

    ChessBoardComputedInfo boardInfo = computeInfo(board);
    generateMoves(board, &boardInfo, &pointer);

    const int nMoves = pointer - moves;

    //create global shared cache - needs OMP synchronization
    CacheEntry    *cache = malloc(CACHESIZE * sizeof(CacheEntry));

    #pragma omp parallel for
    for(int i=0; i < nMoves; i++)
    {
        ChessBoard nextBoard = *board;
        makeMove(&nextBoard, boardInfo.allPieces, moves + i);
        if(isNotUnderCheck(&nextBoard, nextBoard.nextMove)) {
            uint64_t n = minimax(&nextBoard, depth -1, cache);

            #pragma omp atomic
            count += n;
        }
    }
    free(cache);


    return count;
}

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

/*
 * This is optimized multithreaded perftest
 */
int main(int argc, char **argv) {

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
   printf("See: http://chessprogramming.wikispaces.com/Perft\n\n");

   if(argc < 2 || argc > 3) {
       printf("usage: [DEPTH]       - running standard layout perft to the given depth.\n");
       printf("usage: [FEN] [DEPTH] - running custom layout perft to the given depth.\n\n");
       return 1;
   }

   printf("\n");

   int depth = atoi(argv[argc - 1]);
   if(depth == 0) return 1;

   initMovesGenerator();

   ChessBoard board = standardBoard();

   if(argc == 3) {
        board = boardFromFEN(argv[1]);
        char buffer[256];
        printf("Running perft for custom board layout '%s' for %d plies ...\n\n", board2fen(&board,buffer, 255), depth);
   } else {
       printf("Running perft for standard board layout for %d plies ...\n\n", depth);
   }

   //flush stdout so we see the initial messages immediately
   fflush(stdout);

   struct timeval start, end;

   gettimeofday(&start, NULL);
   unsigned long long result = 0;

   result = perft(&board, depth);

   gettimeofday(&end, NULL);
   double t = (timediff(&start, &end) +1 )/ 1000.0;

   printf("Generated %d plies. Performance: %fs, %llu nodes / seconds. Total combinations: %llu\n",
            depth,
            ((double) t / 1000.0),
            (unsigned long long) ((double) result / ((double) t / 1000.0)),
            result
   );

   return 0;
}
