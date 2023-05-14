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

#include "chessboard.h"
#include "move.h"
#include "movearray.h"

struct CacheEntry {
    uint64_t              hash;
    int                   depth;
    uint64_t              count;
};

struct Cache {
    int                       cacheSize;
    std::atomic<CacheEntry>   *cache;

    explicit Cache(int size) {
        cacheSize = size;
        cache = new std::atomic<CacheEntry>[cacheSize];
    }

    ~Cache() {
        delete[] cache;
    }

    [[nodiscard]] uint64_t get(const uint64_t hash, int depth) const {
        CacheEntry entry = cache[(cacheSize - 1) & hash];

        if(entry.hash == hash && entry.depth == depth) {
            return entry.count;
        }
        return 0;
    }

    void set(uint64_t hash, int depth, uint64_t count) const {
        auto entry = CacheEntry{
            .hash = hash,
            .depth = depth,
            .count = count
        };
        cache[(cacheSize - 1) & hash]=entry;
    }
};

Cache cache(64*1024*1024);

/**
 * @brief This is a perft worker
 * @param board
 * @param depth
 * @param cache Shared cache, needs OMP synchronization
 * @return number of legal moves
 */
uint64_t minimax(const ChessBoard &board, const int depth, const int parallelCount)
{
    if(depth < 1) return 1;

    if (auto count = cache.get(board.zobristKey, depth)) {
        return count;
    }

    bitmask attacks = MoveGenerator::attacks(board, board.opponentColor());
    bool    isCheck = 0 != (attacks & board.king());

    MoveArray moves;
    MoveGenerator::moves(board, moves);

    std::vector<std::thread> threads;
    std::atomic<uint64_t> count(0);

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
                if (parallelCount > 0) {
                    threads.emplace_back([nextBoard, depth, &count, parallelCount]() {
                        count += minimax(nextBoard, depth - 1, parallelCount - 1);
                    });
                } else {
                    count += minimax(nextBoard, depth - 1, 0);
                }
            }
        }
    }

    for(auto& thread : threads){
           thread.join();
    }

    cache.set(board.zobristKey, depth, count);
    return count;
}

uint64_t ChessBoard::perft(int depth) const
{
    return minimax(*this, depth, 2);
}









