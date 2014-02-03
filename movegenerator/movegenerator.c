#include "chessboard.h"
#include "movegenerator.h"

void initMovesGenerator() {
    initMovesGeneratorKnight();
    initMovesGeneratorPawn();
    initMovesGeneratorKing();
    initMovesGeneratorBishop();
    initMovesGeneratorRook();
}

int generateMoves(const ChessBoard *board, const bitboard allPieces, Move **moves)
{
    const bitboard opponentPieces = (board->nextMove == WHITE) ? BLACK_PIECES(board) : WHITE_PIECES(board);
    const bitboard boardAvailable = (board->nextMove == WHITE) ? ~WHITE_PIECES(board) : ~BLACK_PIECES(board);

    generateMovesKnight (board, moves, boardAvailable);
    generateMovesPawn   (board, moves, allPieces, opponentPieces);
    generateMovesKing   (board, moves, boardAvailable, allPieces, opponentPieces);
    generateMovesRook   (board, moves, boardAvailable, allPieces, opponentPieces);
    generateMovesBishop (board, moves, boardAvailable, allPieces, opponentPieces);
}

bitboard moveBitBoard0(bitboard b, const int up, const int right) {
    //move the piece up or down
    if (up > 0) {
        for(int i=0; i < up; i++)
            b = ONE_NORTH(b);
    } else if(up < 0) {
        for(int i=0; i < -up; i++)
            b = ONE_SOUTH(b);
    }

    //move the piece right or left
    if (right > 0) {
        for(int i=0; i < right; i++)
            b = ONE_EAST(b);
    } else if( right < 0){
        for(int i=0; i < -right; i++)
            b = ONE_WEST(b);
    }
    return b;
}
