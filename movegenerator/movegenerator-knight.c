#include "chessboard.h"



bitboard KNIGHT_MOVES[64];


void initMovesGeneratorKnight() {
    //for all fields
    int i=0;
    for (i = 0; i < 64; i++) {
        //put the piece on the board
        bitboard piece = 1ULL << i;

        //get moves
        KNIGHT_MOVES[i] =
                      moveBitBoard(piece, 2, 1) |
                      moveBitBoard(piece, 2, -1) |
                      moveBitBoard(piece, 1, 2) |
                      moveBitBoard(piece, -1, 2) |
                      moveBitBoard(piece, -2, 1) |
                      moveBitBoard(piece, -2, -1) |
                      moveBitBoard(piece, -1, -2) |
                      moveBitBoard(piece, 1, -2)
        ;

    }
}


bitboard generateAttacksKnight(struct chessBoard *board, enum pieceColor color)
{
    bitboard pieces = color == WHITE ? board->whiteKnight : board->blackKnight;
    bitboard attacks = 0;

    // while there are knight pieces
    while (pieces != 0) {
        int sourceIndex = bitScan(pieces);

        // get attacks
        attacks |= KNIGHT_MOVES[sourceIndex];
        pieces ^= BITMASK_SQUARE[sourceIndex];
    }

    return attacks;
}


void generateMovesKnight(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces)
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
    while (knight != 0) {

         int sourceIndex = bitScan(knight);
         bitboard source = BITMASK_SQUARE[sourceIndex];

         // get possible moves - moves minus my onw color
         bitboard movesBoard = KNIGHT_MOVES[sourceIndex] & boardAvailable;

         // for all moves
         while (movesBoard != 0) {
             int targetIndex = bitScan(movesBoard);
             bitboard target = BITMASK_SQUARE[targetIndex];

             moves[*movesIndex] =  (struct move){movingPiece, NO_PIECE, sourceIndex, targetIndex, 0, 0, 0};

             *movesIndex +=1;
             movesBoard ^= target;
         }

         // remove the piece
         knight ^= source;
    }
}
