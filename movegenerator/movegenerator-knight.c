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


bitboard generateAttacksKnight(const ChessBoard *board, const ChessPieceColor color, const bitboard allPieces)
{
    bitboard pieces = color == WHITE ? board->whiteKnight : board->blackKnight;
    bitboard attacks = 0;

    // while there are knight pieces
    while (pieces) attacks |= KNIGHT_MOVES[bitScanPop(pieces)];

    return attacks;
}

void generateMovesKnight(const ChessBoard *board, Move **moves, const bitboard boardAvailable, const bitboard allPieces, const bitboard opponentPieces)
{
    bitboard knight;
    ChessPiece movingPiece;

    if(board->nextMove == WHITE) {
        knight = board->whiteKnight;
        movingPiece = WHITE_KNIGHT;
    } else {
        knight = board->blackKnight;
        movingPiece = BLACK_KNIGHT;
    }

    // while there are knight pieces
    while (knight) {
         int sourceIndex = bitScanPop(knight);
         // get possible moves - moves minus my onw color
         bitboard movesBoard = KNIGHT_MOVES[sourceIndex] & boardAvailable;
         // for all moves
         while (movesBoard) GENERATE_MOVE(movingPiece, NO_PIECE, sourceIndex, bitScanPop(movesBoard), 0);
    }
}
