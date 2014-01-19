#include "chessboard.h"
#include "movegenerator.h"


extern int MOVE_RANK_SHIFT[64];
extern bitboard MOVE_RANK_MASK[64];
extern bitboard MOVE_RANK_ATTACKS[64][64];
extern bitboard MOVE_FILE_MASK[64];
extern bitboard MOVE_FILE_MAGIC[64];
extern bitboard MOVE_FILE_ATTACKS[64][64];
extern const bitboard MAGIC_FILE[];

extern int A1H8_INDEX[64];
extern int A8H1_INDEX[64];

extern bitboard MOVE_A1H8_MASK[64];
extern bitboard MOVE_A1H8_MAGIC[64];
extern bitboard MOVE_A8H1_MASK[64];
extern bitboard MOVE_A8H1_MAGIC[64];

extern bitboard MOVE_A1H8_ATTACKS[64][64];
extern bitboard MOVE_A8H1_ATTACKS[64][64];

extern const bitboard MAGIC_A8H1[];
extern const bitboard MAGIC_A1H8[];



void initMovesGeneratorQueen()
{

}

bitboard generateAttacksQueen(const struct chessBoard *board, enum pieceColor color, bitboard allPieces)
{
    bitboard queen = color == WHITE ? board->whiteQueen : board->blackQueen;

    bitboard attacks = 0;

    //for all queens
    while (queen) {
         //get next queen
         const int sourceIndex = bitScan(queen);
         const bitboard source = BITMASK_SQUARE[sourceIndex];

         //use bishop and rook for move generation
         //use magic multipliers to get occupancy state index for rank/file/diagonal
         const int stateIndexRank = (int) ((allPieces & MOVE_RANK_MASK[sourceIndex]) >> MOVE_RANK_SHIFT[sourceIndex]);
         const int stateIndexFile = (int) (((allPieces & MOVE_FILE_MASK[sourceIndex]) * MOVE_FILE_MAGIC[sourceIndex]) >> 57);
         const int stateIndexA8H1 = (int) (((allPieces & MOVE_A8H1_MASK[sourceIndex]) * MOVE_A8H1_MAGIC[sourceIndex]) >> 57);
         const int stateIndexA1H8 = (int) (((allPieces & MOVE_A1H8_MASK[sourceIndex]) * MOVE_A1H8_MAGIC[sourceIndex]) >> 57);

         //use bishop and rook for move generation
         attacks |= MOVE_RANK_ATTACKS[sourceIndex][stateIndexRank];
         attacks |= MOVE_FILE_ATTACKS[sourceIndex][stateIndexFile];
         attacks |= MOVE_A8H1_ATTACKS[sourceIndex][stateIndexA8H1];
         attacks |= MOVE_A1H8_ATTACKS[sourceIndex][stateIndexA1H8];

         //remove this queen
         queen ^= source;
    }

    return attacks;

}


void generateMovesQueen(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces)
{

    enum chessPiece movingPiece;
    bitboard queen;

    //prepare color
    if (board->nextMove == WHITE) {
        movingPiece = WHITE_QUEEN;
        queen = board->whiteQueen;
    } else {
        movingPiece = BLACK_QUEEN;
        queen = board->blackQueen;
    }

     //for all queens
     while (queen != 0) {
         //get next queen
         const int sourceIndex = bitScan(queen);
         const bitboard source = BITMASK_SQUARE[sourceIndex];

         //use bishop and rook for move generation
         //use magic multipliers to get occupancy state index for rank/file/diagonal
         const int stateIndexA8H1 = (int) (((allPieces & MOVE_A8H1_MASK[sourceIndex]) * MOVE_A8H1_MAGIC[sourceIndex]) >> 57);
         const int stateIndexA1H8 = (int) (((allPieces & MOVE_A1H8_MASK[sourceIndex]) * MOVE_A1H8_MAGIC[sourceIndex]) >> 57);
         const int stateIndexRank = (int) ((allPieces & MOVE_RANK_MASK[sourceIndex]) >> MOVE_RANK_SHIFT[sourceIndex]);
         const int stateIndexFile = (int) (((allPieces & MOVE_FILE_MASK[sourceIndex]) * MOVE_FILE_MAGIC[sourceIndex]) >> 57);

         //use bishop and rook for move generation
         bitboard movesBoard = MOVE_A8H1_ATTACKS[sourceIndex][stateIndexA8H1];
         movesBoard |= MOVE_A1H8_ATTACKS[sourceIndex][stateIndexA1H8];
         movesBoard |= MOVE_RANK_ATTACKS[sourceIndex][stateIndexRank];
         movesBoard |= MOVE_FILE_ATTACKS[sourceIndex][stateIndexFile];

         //un-mask own color
         movesBoard &= boardAvailable;

         //for all moves
         while (movesBoard != 0) {
             //get next move
             const int targetIndex = bitScan(movesBoard);
             const bitboard target = BITMASK_SQUARE[targetIndex];

             ADD_MOVE(movingPiece, NO_PIECE, 0, 0);

             //remove move
             movesBoard ^= target;
         }

         //remove this queen
         queen ^= source;
     }

}
