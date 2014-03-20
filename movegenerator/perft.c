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


#include <omp.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "chessboard.h"
#include "utils.h"
#include "zobrist.h"

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
uint64_t minimax(const int cacheSize, const ChessBoard *board, const int depth, CacheEntry *cache)
{
    //compute directly
    if(depth < 1) return 1;

    const uint64_t hashCode = board->zobristKey;

    CacheEntry *cacheEntry = (cache + ((cacheSize - 1) & hashCode));

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
            count += minimax(cacheSize, &nextBoard, depth -1, cache);
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
    int cacheSize = 16*1024*1024;
    long memSize = getMemorySize();

    if(cacheSize * sizeof(CacheEntry) > (memSize / 3)) cacheSize = (memSize / 3) / sizeof(CacheEntry);

    CacheEntry    *cache = malloc(cacheSize * sizeof(CacheEntry));

    #pragma omp parallel
    {
#pragma omp single
        {
            for(int i=0; i < nMoves; i++)
            {
                #pragma omp task untied
                {
                    ChessBoard nextBoard = *board;
                    makeMove(&nextBoard, boardInfo.allPieces, moves + i);
                    if(isNotUnderCheck(&nextBoard, nextBoard.nextMove)) {
                        uint64_t n = minimax(cacheSize, &nextBoard, depth -1, cache);

                        #pragma omp atomic
                        count += n;
                    }
                }
            }
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
