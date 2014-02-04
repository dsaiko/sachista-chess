#include "chessboard.h"
#include "movegenerator.h"

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


INLINE bitboard generateAttacksKnight(const ChessBoard *board, const PieceColor color)
{
    bitboard pieces = color == WHITE ? board->whiteKnight : board->blackKnight;
    bitboard attacks = 0;

    // while there are knight pieces
    while (pieces) attacks |= KNIGHT_MOVES[bitScanPop(pieces)];

    return attacks;
}

void generateMovesKnight(const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo)
{
    bitboard knight;
    Piece movingPiece;

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
         bitboard movesBoard = KNIGHT_MOVES[sourceIndex] & boardInfo->boardAvailable;
         // for all moves
         while (movesBoard) GENERATE_MOVE(board, boardInfo, moves, movingPiece, NO_PIECE, sourceIndex, bitScanPop(movesBoard), 0);
    }
}
