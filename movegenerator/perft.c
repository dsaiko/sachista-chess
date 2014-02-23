#include <omp.h>
#include <string.h>
#include <stdlib.h>

#include "chessboard.h"
#include "utils.h"
#include "zobrist.h"

#define CACHESIZE     (16*1024*1024)

typedef struct {
    uint64_t hashCode;
    uint64_t nodeCount;
    int      depth;
} CacheEntry;

uint64_t minimax(const ChessBoard *board, const int depth, CacheEntry *cache)
{
    //compute directly
    if(depth < 1) return 1;

    uint64_t hashCode = board->zobristKey;
    int index = (CACHESIZE - 1) & hashCode;

    CacheEntry cacheEntry = *(cache + index);

    if(cacheEntry.hashCode == hashCode && cacheEntry.depth == depth)
        return cacheEntry.nodeCount;

    uint64_t count = 0;

    Move moves[MAX_MOVES_ARR_SIZE];
    Move *pointer = moves;

    ChessBoardComputedInfo boardInfo = computeInfo(board);
    generateMoves(board, &boardInfo, &pointer);

    Move *i = moves;

    ChessBoard nextBoard = *board;

    while(i < pointer) {
        makeMove(&nextBoard, boardInfo.allPieces, i ++);
        if(isNotUnderCheck(&nextBoard, nextBoard.nextMove)) {
            count += minimax(&nextBoard, depth -1, cache);
        }
        if(i < pointer)
            nextBoard = *board;
    }

    CacheEntry *pCacheEntry = (cache +index);

    #pragma omp critical
    {
        pCacheEntry->hashCode = hashCode;
        pCacheEntry->nodeCount = count;
        pCacheEntry->depth = depth;
    }

    return count;
}

uint64_t perft(const ChessBoard *board, const int depth)
{
    if(depth < 1) return 1;

    uint64_t count = 0;

    Move moves[MAX_MOVES_ARR_SIZE];
    Move *pointer = moves;

    ChessBoardComputedInfo boardInfo = computeInfo(board);
    generateMoves(board, &boardInfo, &pointer);

    int  nMoves = pointer - moves;

    CacheEntry    *cache = malloc(CACHESIZE * sizeof(CacheEntry));

    #pragma omp parallel for
    for(int i=0; i< nMoves; i++)
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
