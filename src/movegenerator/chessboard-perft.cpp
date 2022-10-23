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

#include <vector>
#include <thread>
#include <atomic>
#include <new>
#include <functional>

#include "chessboard.h"
#include "zobrist.h"
#include "move.h"
#include "movearray.h"

struct CacheEntry {
    uint64_t              hash;
    uint64_t              count;
    int                   depth;
};

struct Cache {
    int                       cacheSize;
    CacheEntry                *data;

    explicit Cache(int size) {

        cacheSize = size;
        bool badAlloc = true;
        while(badAlloc) {
            badAlloc = false;
            try
            {
                data = new CacheEntry[cacheSize];
            }
            catch (std::bad_alloc& )
            {
                badAlloc = true;
                cacheSize = ((cacheSize * 2) / 3);
            }
        }
    }

    ~Cache() {
        delete[] data;
    }

    [[nodiscard]] uint64_t get(const uint64_t hash, int depth) const {
        CacheEntry *entry = (data + ((cacheSize - 1) & hash));

        if(entry->hash == hash && entry->depth == depth) {
            return entry->count;
        }
        return 0;
    }

    void set(uint64_t hash, int depth, uint64_t count) const {
        CacheEntry *entry = (data + ((cacheSize - 1) & hash));
        entry->hash = hash;
        entry->depth = depth;
        entry->count = count;
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
    uint64_t count = cache.get(board.zobristKey, depth);
    if(count) return count;

    bitmask attacks = MoveGenerator::attacks(board, board.opponentColor());
    bool    isCheck = 0 != (attacks & board.king());

    MoveArray moves;
    MoveGenerator::moves(board, moves);

    for(int i=0; i < moves.size(); i++) {
        Move &move = moves.data[i];
        bitmask sourceBitBoard = BitBoard::squareBitmask(move.sourceIndex);

        // need to validate legality of move only in following cases
        bool needToValidate = move.piece == King || isCheck || (sourceBitBoard & attacks) || move.isEnPassant;

        if(depth == 1) {
            if(!needToValidate || MoveGenerator::isOpponentsKingNotUnderCheck(move.applyToBoard(board))) {
                count ++;
            }
        } else {
            ChessBoard nextBoard = move.applyToBoard(board);
            if(!needToValidate || MoveGenerator::isOpponentsKingNotUnderCheck(nextBoard)) {
                count += minimax(cache, nextBoard, depth -1);
            }
        }
    }
    cache.set(board.zobristKey, depth, count);
    return count;
}

const int CACHE_SIZE = 4*1024*1024;

uint64_t ChessBoard::perft(int depth) const
{
    if(depth < 1) return 1;

    if(depth == 1) {
        Cache cache(1024);
        return minimax(cache, *this, depth);
    }

    std::vector<std::thread> threads;
    std::atomic<uint64_t> count(0);

    MoveArray moves;
    MoveGenerator::moves(*this,  moves);

    for(int i=0; i<moves.size(); i++) {
        Move &m = moves.data[i];

        ChessBoard board = m.applyToBoard(*this);
        if(MoveGenerator::isOpponentsKingNotUnderCheck(board)) {
            threads.emplace_back([board, depth, &count](){
                Cache cache(CACHE_SIZE);
                count += minimax(cache, board, depth -1);
            });
        }
    }

    //join threads
    for(auto& thread : threads){
           thread.join();
    }

    return count.load();
}









