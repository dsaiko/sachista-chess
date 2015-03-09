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

#include <string.h>
#include <vector>

#include "chessboard.h"
#include "zobrist.h"
#include "chessboard-stats.h"
#include "utility.h"
#include "move.h"

struct CacheEntry {
    uint64_t              hash;
    uint64_t              count;
    int                   depth;

    CacheEntry(): hash(0), count(0), depth(0) {}
};


struct Cache {
    const int                       cacheSize;
    CacheEntry                      *data;

    Cache(int size): cacheSize(size) {
        data = new CacheEntry[cacheSize];
    }

    ~Cache() {
        delete[] data;
    }

    uint64_t get(const uint64_t &hash, int depth) {
        CacheEntry *entry = (data + ((cacheSize - 1) & hash));
        if(entry->hash == hash && entry->depth == depth) {
            return entry->count;
        }
        return 0;
    }

    void set(uint64_t hash, int depth, uint64_t count) {
        CacheEntry *entry = (data + ((cacheSize - 1) & hash));

        if(entry->hash == 0) {
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
uint64_t minimax(Cache &cache, const ChessBoard &board, const int depth, const ChessBoardStats &stats)
{
    //TODO: multi thread
    //TODO: cache
    //compute directly
    if(depth < 1) return 1;

    uint64_t count = cache.get(board.zobristKey, depth);
    if(count) return count;

    std::vector<Move> moves = MoveGenerator::moves(board, stats);

    ChessBoard nextBoard = board;

    for(Move move : moves) {
        move.applyTo(nextBoard);

        ChessBoardStats nextStats(nextBoard);

        if(MoveGenerator::isKingNotUnderCheck(nextBoard, nextBoard.nextMove, nextStats)) {
            count += minimax(cache, nextBoard, depth -1, nextStats);
        } else {
            count += 1;
        }

        //TODO: not for the last one
        nextBoard = board;
    }

    cache.set(board.zobristKey, depth, count);
    return count;
}

uint64_t ChessBoard::perft(int depth)
{
    if(depth < 1) return 1;

    unsigned long memSize = Utility::getMemorySize();
    unsigned long cacheSize = 128*1024*1024;
    //get maximum of total_memory / 4 cache size
    if(cacheSize * sizeof(CacheEntry) > (memSize / 4)) cacheSize = (memSize / 4) / sizeof(CacheEntry);

    Cache cache(cacheSize);
    return minimax(cache, *this, depth, ChessBoardStats(*this));
}

