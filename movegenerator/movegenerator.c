#include "chessboard.h"

bitboard RIGHT_SHIFTS[7];
bitboard LEFT_SHIFTS[7];

void initMovesGenerator() {

    RIGHT_SHIFTS[0] = BITMASK_NOT_FILE_A;
    LEFT_SHIFTS[0] = BITMASK_NOT_FILE_H;

    int i;

    for(i=1; i<7; i++) {
        RIGHT_SHIFTS[i] = oneEast(RIGHT_SHIFTS[i - 1]);
        LEFT_SHIFTS[i] = oneWest(LEFT_SHIFTS[i - 1]);
    }

    initMovesGeneratorKnight();
}

int generateMoves(const struct chessBoard *board, struct move *m, const int bufferSize)
{
    const bitboard boardAvailable = (board->nextMove == WHITE) ? ~WHITE_PIECES(board) : ~BLACK_PIECES(board);
    const bitboard allPieces = ALL_PIECES(board);

    int movesIndex = 0;

    generateMovesKnight(board, m, bufferSize, &movesIndex, boardAvailable, allPieces);

    return movesIndex;
}

struct chessBoard makeMove(const struct chessBoard *board, const struct move *m) {
    return standardBoard;
}

bitboard generateAttacks(struct chessBoard *board, enum pieceColor color, bitboard allPieces) {
    long attacks = 0L;

    attacks     |=  generateAttacksKnight(board, color);

    return attacks;
}



bitboard moveBitBoard(bitboard bitmask, const int up, const int right) {
    if (bitmask == 0) return 0L;

    //move the piece up or down
    if (up > 0) {
       bitmask <<= (long) (up << 3);
    } else if(up < 0) {
        bitmask >>= (long) ((-up) << 3);
    }

    //move the piece right or left
    if (right > 0) {
        bitmask =  (bitmask << right) & RIGHT_SHIFTS[right - 1];
    } else if( right < 0){
        bitmask = (bitmask >> -right) & LEFT_SHIFTS[-right - 1];
    }
    return bitmask;
}
