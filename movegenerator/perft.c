#include <omp.h>
#include <string.h>
#include <stdlib.h>

#include "chessboard.h"
#include "utils.h"
#include "zobrist.h"

#define CACHESIZE     (128*1024)

typedef struct {
    uint64_t hashCode;
    uint64_t nodeCount;
} CacheEntry;

uint64_t minimax(const ChessBoard *board, const int depth, CacheEntry *cache)
{
    //compute directly
    if(depth < 1) return 1;

    uint64_t hashCode = board->zobristKey;
    int index = (CACHESIZE - 1) & hashCode;

    CacheEntry *cacheEntry = cache + (depth * CACHESIZE + index);

    if(cacheEntry->hashCode == hashCode) {
        return cacheEntry->nodeCount;
    }

    cacheEntry->hashCode = hashCode;


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


    cacheEntry->nodeCount = count;

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

    #pragma omp parallel for
    for(int i=0; i< nMoves; i++)
      {
        CacheEntry    *cache = malloc(depth * CACHESIZE * sizeof(CacheEntry));

        ChessBoard nextBoard = *board;
        makeMove(&nextBoard, boardInfo.allPieces, moves + i);
        if(isNotUnderCheck(&nextBoard, nextBoard.nextMove)) {
        uint64_t n = minimax(&nextBoard, depth -1, cache);
        #pragma omp atomic
        count += n;
      }

        free(cache);
    }

    return count;
}
