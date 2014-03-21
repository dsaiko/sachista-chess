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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <string>
#include <vector>
#include <mutex>
#include <atomic>


#include "chessboard.h"
#include "utils.h"
#include "zobrist.h"

struct CacheEntry {
    uint64_t              hash;
    uint64_t              count;
    int                   depth;

    CacheEntry(): hash(0), count(0), depth(0) {}
};


struct Cache {
    const int                       cacheSize;
    CacheEntry                      *data;
    std::mutex                      mutex;

    Cache(int size): cacheSize(size) {
        data = new CacheEntry[cacheSize];
    }

    ~Cache() {
        delete[] data;
    }

    uint64_t get(const uint64_t &hash, int depth) {
        CacheEntry *entry = (data + ((cacheSize - 1) & hash));

       // std::lock_guard<std::mutex> lock(mutex);

        if(entry->hash == hash && entry->depth == depth) {
            return entry->count;
        }
        return 0;
    }

    void set(uint64_t hash, int depth, uint64_t count) {
        CacheEntry *entry = (data + ((cacheSize - 1) & hash));

        if(entry->hash == 0) {
            std::lock_guard<std::mutex> lock(mutex);
            entry->hash = hash;
            entry->depth = depth;
            entry->count = count;
        }
    }
};

/**
 * @brief This is a perft worker
 * @param board
 * @param depth
 * @param cache Shared cache, needs OMP synchronization
 * @return number of legal moves
 */
uint64_t minimax(Cache &cache, const ChessBoard &board, const int depth)
{
    //compute directly
    if(depth < 1) return 1;

    uint64_t count = cache.get(board.zobristKey, depth);
    if(count) return count;

    Move moves[MAX_MOVES_ARR_SIZE];
    Move *pointer = moves;

    ChessBoardComputedInfo boardInfo = computeInfo(&board);
    generateMoves(&board, &boardInfo, &pointer);

    Move *i = moves;

    ChessBoard nextBoard = board;

    while(i < pointer) {
        //make move
        makeMove(&nextBoard, boardInfo.allPieces, i ++);

        //is move legal?
        if(isNotUnderCheck(&nextBoard, nextBoard.nextMove)) {
            if(depth > 1) {
                count += minimax(cache, nextBoard, depth -1);
            } else {
                count += 1;
            }
        }

        //undo move - reset the move back
        if(i < pointer)
            nextBoard = board;
    }

    cache.set(board.zobristKey, depth, count);
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


    Move moves[MAX_MOVES_ARR_SIZE];
    Move *pointer = moves;

    ChessBoardComputedInfo boardInfo = computeInfo(board);
    generateMoves(board, &boardInfo, &pointer);

    const int nMoves = pointer - moves;

    ulong memSize = getMemorySize();
    uint cacheSize = 128*1024*1024;
    if(cacheSize * sizeof(CacheEntry) > (memSize / 4)) cacheSize = (memSize / 4) / sizeof(CacheEntry);

    std::vector<std::thread> threads;
    std::atomic<uint64_t> count(0);
    Cache cache(cacheSize);

    for(int i=0; i < nMoves; i++)
    {
        threads.push_back(std::thread([board, &boardInfo, i, moves, depth, &count, &cache](){
            ChessBoard nextBoard = *board;
            makeMove(&nextBoard, boardInfo.allPieces, moves + i);
            if(isNotUnderCheck(&nextBoard, nextBoard.nextMove)) {
                count += minimax(cache, nextBoard, depth -1);
            }
        }));
    }

    for(auto& thread : threads){
           thread.join();
    }

    return count.load();
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
