#include <omp.h>
#include <string.h>
#include <stdlib.h>

#include "chessboard.h"
#include "utils.h"

#define HASHMAPSIZE     (128*1024)

typedef struct {
    unsigned long long hashCode;
    unsigned long long nodeCount;
} CacheEntry;

typedef struct {
    unsigned long long hits;
} CacheUsage;


unsigned long long computeHashCode(const ChessBoard *board) {
     #define PRIME 127

     unsigned long long result = board->nextMove;
     result = PRIME * result + board->castlingWhite;
     result = PRIME * result + board->castlingBlack;
     result = PRIME * result + board->enPassantIndex;

     result = PRIME * result + board->whiteKing;
     result = PRIME * result + (board->whiteQueen);
     result = PRIME * result + (board->whiteRook);
     result = PRIME * result + (board->whiteKnight);
     result = PRIME * result + (board->whiteBishop);
     result = PRIME * result + (board->whitePawn);

     result = PRIME * result + (board->blackKing);
     result = PRIME * result + (board->blackQueen);
     result = PRIME * result + (board->blackRook);
     result = PRIME * result + (board->blackKnight);
     result = PRIME * result + (board->blackBishop);
     result = PRIME * result + (board->blackPawn);

     return result;
 }

unsigned long long minimax(const ChessBoard *board, const int depth, CacheEntry cache[HASHMAPSIZE], CacheUsage *cacheUsage)
{
    //compute directly
    if(depth < 1) return 1;

    unsigned int hashCode = computeHashCode(board);
    int index = (HASHMAPSIZE - 1) & hashCode;

    CacheEntry *cacheEntry = &cache[index];

    if(cacheEntry->hashCode == hashCode) {
            cacheUsage->hits++;
            return cacheEntry->nodeCount;
    } else {
        cacheEntry->hashCode = hashCode;
    }


    unsigned long long count = 0;

    Move moves[MAX_MOVES_ARR_SIZE];
    Move *pointer = moves;

    ChessBoardComputedInfo boardInfo = computeInfo(board);
    generateMoves(board, &boardInfo, &pointer);

    Move *i = moves;

    ChessBoard nextBoard = *board;

    while(i < pointer) {
        makeMove(&nextBoard, boardInfo.allPieces, i ++);
        if(isNotUnderCheck(&nextBoard, nextBoard.nextMove)) {
            count += minimax(&nextBoard, depth -1, cache, cacheUsage);
        }
        nextBoard = *board;
    }


    cacheEntry->nodeCount = count;

    return count;
}

unsigned long long perft(const ChessBoard *board, const int depth)
{
    if(depth < 1) return 1;

    unsigned long long count = 0;

    Move moves[MAX_MOVES_ARR_SIZE];
    Move *pointer = moves;

    ChessBoardComputedInfo boardInfo = computeInfo(board);
    generateMoves(board, &boardInfo, &pointer);

    int  nMoves = pointer - moves;

    #pragma omp parallel for
    for(int i=0; i< nMoves; i++)
      {
        CacheUsage    cacheUsage = {0};
        CacheEntry    cache[HASHMAPSIZE] = {{0, 0}};

        ChessBoard nextBoard = *board;
        makeMove(&nextBoard, boardInfo.allPieces, moves + i);
        if(isNotUnderCheck(&nextBoard, nextBoard.nextMove)) {
            unsigned long long n = minimax(&nextBoard, depth -1, cache, &cacheUsage);
            #pragma omp atomic
            count += n;
        }

        printf("Cache bad hits: %llu\n", cacheUsage.hits);
    }

    return count;
}
