#include "chessboard.h"
#include "movegenerator.h"


void initMovesGeneratorQueen()
{

}

bitboard generateAttacksQueen(const struct chessBoard *board, enum pieceColor color, bitboard allPieces)
{
    bitboard queen = board->nextMove == WHITE ? board->whiteQueen : board->blackQueen;

    bitboard attacks = 0L;

    //for all queens
    while (queen) {

//         //get next queen
//         final int sourceIndex = BitBoard.getFirstBit(queen);
//         final long source = BitBoard.BITMASK_SQUARE[sourceIndex];

//         //use bishop and rook for move generation
//         //use magic multipliers to get occupancy state index for rank/file/diagonal
//         final int stateIndexRank = (int) ((allPieces & MoveGeneratorRook.MOVE_RANK_MASK[sourceIndex]) >>> MoveGeneratorRook.MOVE_RANK_SHIFT[sourceIndex]);
//         final int stateIndexFile = (int) (((allPieces & MoveGeneratorRook.MOVE_FILE_MASK[sourceIndex]) * MoveGeneratorRook.MOVE_FILE_MAGIC[sourceIndex]) >>> 57);
//         final int stateIndexA8H1 = (int) (((allPieces & MoveGeneratorBishop.MOVE_A8H1_MASK[sourceIndex]) * MoveGeneratorBishop.MOVE_A8H1_MAGIC[sourceIndex]) >>> 57);
//         final int stateIndexA1H8 = (int) (((allPieces & MoveGeneratorBishop.MOVE_A1H8_MASK[sourceIndex]) * MoveGeneratorBishop.MOVE_A1H8_MAGIC[sourceIndex]) >>> 57);

//         //use bishop and rook for move generation
//         attacks |= MoveGeneratorRook.MOVE_RANK_ATTACKS[sourceIndex][stateIndexRank];
//         attacks |= MoveGeneratorRook.MOVE_FILE_ATTACKS[sourceIndex][stateIndexFile];
//         attacks |= MoveGeneratorBishop.MOVE_A8H1_ATTACKS[sourceIndex][stateIndexA8H1];
//         attacks |= MoveGeneratorBishop.MOVE_A1H8_ATTACKS[sourceIndex][stateIndexA1H8];

//         //remove this queen
//         queen ^= source;
    }

    return attacks;

}


void generateMovesQueen(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces)
{

}
