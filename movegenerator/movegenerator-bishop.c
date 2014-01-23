#include "bitboard.h"
#include "chessboard.h"
#include "movegenerator.h"


int A1H8_INDEX[64];
int A8H1_INDEX[64];

bitboard MOVE_A1H8_MASK[64];
bitboard MOVE_A1H8_MAGIC[64];
bitboard MOVE_A8H1_MASK[64];
bitboard MOVE_A8H1_MAGIC[64];

bitboard MOVE_A1H8_ATTACKS[64][64];
bitboard MOVE_A8H1_ATTACKS[64][64];


const bitboard MAGIC_A8H1[] = {
           0x0ULL,
           0x0ULL,
           0x0101010101010100ULL,
           0x0101010101010100ULL,
           0x0101010101010100ULL,
           0x0101010101010100ULL,
           0x0101010101010100ULL,
           0x0101010101010100ULL,
           0x0080808080808080ULL,
           0x0040404040404040ULL,
           0x0020202020202020ULL,
           0x0010101010101010ULL,
           0x0008080808080808ULL,
           0x0ULL,
           0x0ULL
};

const bitboard MAGIC_A1H8[] = {
           0x0ULL,
           0x0ULL,
           0x0101010101010100ULL,
           0x0101010101010100ULL,
           0x0101010101010100ULL,
           0x0101010101010100ULL,
           0x0101010101010100ULL,
           0x0101010101010100ULL,
           0x8080808080808000ULL,
           0x4040404040400000ULL,
           0x2020202020000000ULL,
           0x1010101000000000ULL,
           0x0808080000000000ULL,
           0x0ULL,
           0x0ULL
};

void initMovesGeneratorBishop()
{
    //for all fields
    for (int i = 0; i < 64; i++) {
        //compute index of diagonal for the field
        A8H1_INDEX[i] = FILE_INDEX(i) + RANK_INDEX(i) % 8;
        A1H8_INDEX[i] = FILE_INDEX(i) + 7 - RANK_INDEX(i) % 8;

        //compute 6-bit diagonal for the field
        MOVE_A8H1_MASK[i] = BITMASK_A8H1[A8H1_INDEX[i]] & ~BITMASK_FRAME;
        MOVE_A1H8_MASK[i] = BITMASK_A1H8[A1H8_INDEX[i]] & ~BITMASK_FRAME;

        //index magic multiplier for the field
        MOVE_A8H1_MAGIC[i] = MAGIC_A8H1[A8H1_INDEX[i]];
        MOVE_A1H8_MAGIC[i] = MAGIC_A1H8[A1H8_INDEX[i]];
    }


    //precompute A1H8 moves
    // i is field index
    // n is 6 bit configuration

    //for all fields
    for (int i = 0; i < 64; i++) {
        //for all possible diagonal states
        for (int n = 0; n < 64; n++) {

            //get the diagonal
            bitboard diagonal = BITMASK_A1H8[A1H8_INDEX[i]];

            //reconstruct the state (number) into the diagonal

            //get the left/bottom bit - start of diagonal
            bitboard tmp;
            while ((tmp = ONE_SOUTH_WEST(diagonal))) {
                diagonal = tmp;
            }

            bitboard board = 0;

            int m = n;
            //traverse diagonal and set bits according to N
            while (diagonal) {
                //shift up by one
                diagonal = ONE_NORTH_EAST(diagonal);
                if (m & 1) {
                    board |= diagonal;
                }
                m >>= 1;
            }

            //make it 6-bit only
            board &= ~BITMASK_FRAME;

            //compute possible moves
            bitboard moves = 0;

            //set piece to Ith index
            bitboard piece = BITMASK_SQUARE(i);

            //move in one direction
            while (piece) {
                piece = ONE_NORTH_EAST(piece);
                moves |= piece;

                //end when there is another piece (either color, own color will have to be stripped out)
                if (piece & board) {
                    piece = 0;
                }
            }

            //set piece back to Ith index
            piece = BITMASK_SQUARE(i);

            //move in the other direction
            while (piece) {
                piece = ONE_SOUTH_WEST(piece);
                moves |= piece;

                //end when there is another piece (either color, own color will have to be stripped out)
                if (piece & board) {
                    piece = 0;
                }
            }

            //remember the moves for Ith field within Nth occupancy state
            MOVE_A1H8_ATTACKS[i][n] = moves;
        }
    }

    //precompute A8H1 moves
    // i is field index
    // n is 6 bit configuration
    //for all fields
    for (int i = 0; i < 64; i++) {
        //for all possible diagonal states
        for (int n = 0; n < 64; n++) {

            //get the diagonal
            bitboard diagonal = BITMASK_A8H1[A8H1_INDEX[i]];

            //get the left/top bit - start of the diagonal
            bitboard tmp;
            while ((tmp = ONE_NORTH_WEST(diagonal))) {
                diagonal = tmp;
            }

            //traverse diagonal and set bits according to N
            bitboard board = 0;

            int m = n;
            while (diagonal) {
                //shift down by one
                diagonal = ONE_SOUTH_EAST(diagonal);
                if (m & 1) {
                    board |= diagonal;
                }
                m >>= 1;
            }

            //make it 6-bit only
            board &= ~BITMASK_FRAME;

            //pre-compute moves
            bitboard moves = 0;

            //set the piece to Ith position
            bitboard piece = BITMASK_SQUARE(i);

            //move one direction
            while (piece) {
                piece = ONE_NORTH_WEST(piece);
                moves |= piece;
                //end when there is another piece (either color, own color will have to be stripped out)
                if (piece & board) {
                    piece = 0;
                }
            }

            //set the piece back to Ith position
            piece = BITMASK_SQUARE(i);
            //move the other direction
            while (piece) {
                piece = ONE_SOUTH_EAST(piece);
                moves |= piece;
                //end when there is another piece (either color, own color will have to be stripped out)
                if (piece & board) {
                    piece = 0;
                }
            }
            MOVE_A8H1_ATTACKS[i][n] = moves;
        }
    }
}

bitboard generateAttacksBishop(const struct chessBoard *board, enum pieceColor color, bitboard allPieces)
{
    bitboard bishop = (color == WHITE) ? (board->whiteBishop | board->whiteQueen) : (board->blackBishop | board->blackQueen);

    bitboard attacks = 0;

       //for all bishops
       while (bishop) {
           //get index of next piece
           const int sourceIndex = bitScan(bishop);
           const bitboard source =  BITMASK_SQUARE(sourceIndex);

           //get states of diagonals using magic number multiplication
           const int stateIndexA8H1 = (int) (((allPieces & MOVE_A8H1_MASK[sourceIndex]) * MOVE_A8H1_MAGIC[sourceIndex]) >> 57);
           const int stateIndexA1H8 = (int) (((allPieces & MOVE_A1H8_MASK[sourceIndex]) * MOVE_A1H8_MAGIC[sourceIndex]) >> 57);

           //add attacks
           attacks |= MOVE_A8H1_ATTACKS[sourceIndex][stateIndexA8H1];
           attacks |= MOVE_A1H8_ATTACKS[sourceIndex][stateIndexA1H8];

           //remove the current bishop
           bishop ^= source;
       }

       return attacks;
}

void generateMovesBishop(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces)
{
    bitboard bishop;

    //choose color
    if (board->nextMove == WHITE) {
        bishop = board->whiteBishop | board->whiteQueen;
    } else {
        bishop = board->blackBishop | board->blackQueen;
    }

    //for all bishops
    while (bishop) {
        //get next piece index
        const int sourceIndex = bitScan(bishop);
        const bitboard source = BITMASK_SQUARE(sourceIndex);

        //get states of diagonals using magic number multiplication
        const int stateIndexA8H1 = (int) (((allPieces & MOVE_A8H1_MASK[sourceIndex]) * MOVE_A8H1_MAGIC[sourceIndex]) >> 57);
        const int stateIndexA1H8 = (int) (((allPieces & MOVE_A1H8_MASK[sourceIndex]) * MOVE_A1H8_MAGIC[sourceIndex]) >> 57);

        //get all moves using precomputed values
        bitboard movesBoard = MOVE_A8H1_ATTACKS[sourceIndex][stateIndexA8H1];
        movesBoard |= MOVE_A1H8_ATTACKS[sourceIndex][stateIndexA1H8];

        //remove own color from possible moves
        movesBoard &= boardAvailable;

        //for all moves
        while (movesBoard) {
            //get next move
            const int targetIndex = bitScan(movesBoard);
            const bitboard target = BITMASK_SQUARE(targetIndex);

            enum chessPiece movingPiece;
            if(board->nextMove == WHITE) {
              if(board->whiteBishop & source) {
                  movingPiece = WHITE_BISHOP;
              } else {
                  movingPiece = WHITE_QUEEN;
              }
            } else {
                if(board->blackBishop & source) {
                    movingPiece = BLACK_BISHOP;
                } else {
                    movingPiece = BLACK_QUEEN;
                }
            }

            //add move to array
            GENERATE_MOVE(movingPiece, NO_PIECE, sourceIndex, targetIndex, 0);

            //remove this move
            movesBoard ^= target;
        }

        //remove current piece
        bishop ^= source;
    }


}
