#include "chessboard.h"
#include "movegenerator.h"

void initMovesGenerator() {
    initMovesGeneratorKnight();
    initMovesGeneratorPawn();
    initMovesGeneratorKing();
    initMovesGeneratorQueen();
    initMovesGeneratorBishop();
    initMovesGeneratorRook();
}

int generateMoves(const struct chessBoard *board, struct move *m, const int bufferSize)
{
    const bitboard boardAvailable = (board->nextMove == WHITE) ? ~WHITE_PIECES(board) : ~BLACK_PIECES(board);
    const bitboard allPieces = ALL_PIECES(board);

    int movesIndex = 0;

    generateMovesKnight(board, m, bufferSize, &movesIndex, boardAvailable, allPieces);
    generateMovesPawn(board, m, bufferSize, &movesIndex, boardAvailable, allPieces);
    generateMovesKing(board, m, bufferSize, &movesIndex, boardAvailable, allPieces);
    generateMovesRook(board, m, bufferSize, &movesIndex, boardAvailable, allPieces);
    generateMovesBishop(board, m, bufferSize, &movesIndex, boardAvailable, allPieces);
    generateMovesQueen(board, m, bufferSize, &movesIndex, boardAvailable, allPieces);

    return movesIndex;
}

bitboard generateAttacks(struct chessBoard *board, enum pieceColor color, bitboard allPieces) {
    bitboard attacks = 0;

    attacks     |=  generateAttacksKnight(board, color, allPieces);
    attacks     |=  generateAttacksPawn(board, color, allPieces);
    attacks     |=  generateAttacksKing(board, color, allPieces);
    attacks     |=  generateAttacksQueen(board, color, allPieces);
    attacks     |=  generateAttacksRook(board, color, allPieces);
    attacks     |=  generateAttacksBishop(board, color, allPieces);


    return attacks;
}

bitboard moveBitBoard0(bitboard b, const int up, const int right) {
    //move the piece up or down
    int i;
    if (up > 0) {
        for(i=0; i < up; i++)
            b = ONE_NORTH(b);
    } else if(up < 0) {
        for(i=0; i < -up; i++)
            b = ONE_SOUTH(b);
    }

    //move the piece right or left
    if (right > 0) {
        for(i=0; i < right; i++)
            b = ONE_EAST(b);
    } else if( right < 0){
        for(i=0; i < -right; i++)
            b = ONE_WEST(b);
    }
    return b;
}
