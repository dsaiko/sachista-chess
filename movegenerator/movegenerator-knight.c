#include "chessboard.h"
#include "movegenerator.h"


bitboard KNIGHT_MOVES[64];


void initMovesGeneratorKnight() {
    //for all fields
    for (int i = 0; i < 64; i++) {
        //put the piece on the board
        bitboard piece = BITMASK_SQUARE(i);

        //get moves
        KNIGHT_MOVES[i] =
                      moveBitBoard0(piece,  2,  1)       |
                      moveBitBoard0(piece,  2, -1)       |
                      moveBitBoard0(piece,  1,  2)       |
                      moveBitBoard0(piece, -1,  2)       |
                      moveBitBoard0(piece, -2,  1)       |
                      moveBitBoard0(piece, -2, -1)       |
                      moveBitBoard0(piece, -1, -2)       |
                      moveBitBoard0(piece,  1, -2)
        ;

    }
}


bitboard generateAttacksKnight(const struct chessBoard *board, enum pieceColor color, bitboard allPieces)
{
    bitboard pieces = color == WHITE ? board->whiteKnight : board->blackKnight;
    bitboard attacks = 0;

    // while there are knight pieces
    while (pieces) {
        int sourceIndex = bitScan(pieces);

        // get attacks
        attacks |= KNIGHT_MOVES[sourceIndex];
        pieces ^= BITMASK_SQUARE(sourceIndex);
    }

    return attacks;
}

void generateMovesKnight(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces, const bitboard opponentPieces)
{
    bitboard knight;
    enum chessPiece movingPiece;

    if(board->nextMove == WHITE) {
        knight = board->whiteKnight;
        movingPiece = WHITE_KNIGHT;
    } else {
        knight = board->blackKnight;
        movingPiece = BLACK_KNIGHT;
    }

    // while there are knight pieces
    while (knight) {
         int sourceIndex = bitScan(knight);
         bitboard source = BITMASK_SQUARE(sourceIndex);

         // get possible moves - moves minus my onw color
         bitboard movesBoard = KNIGHT_MOVES[sourceIndex] & boardAvailable;

         // for all moves
         while (movesBoard) {
             int targetIndex = bitScan(movesBoard);
             bitboard target = BITMASK_SQUARE(targetIndex);

             GENERATE_MOVE(movingPiece, NO_PIECE, sourceIndex, targetIndex, 0, target & allPieces);
             movesBoard ^= target;
         }

         // remove the piece
         knight ^= source;
    }
}
