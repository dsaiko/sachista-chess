#include "chessboard.h"
#include "movegenerator.h"

int MOVE_RANK_SHIFT[64];
bitboard MOVE_RANK_MASK[64];
bitboard MOVE_RANK_ATTACKS[64][64];
bitboard MOVE_FILE_MASK[64];
bitboard MOVE_FILE_MAGIC[64];
bitboard MOVE_FILE_ATTACKS[64][64];

const bitboard MAGIC_FILE[] = {
           0x8040201008040200ULL,
           0x4020100804020100ULL,
           0x2010080402010080ULL,
           0x1008040201008040ULL,
           0x0804020100804020ULL,
           0x0402010080402010ULL,
           0x0201008040201008ULL,
           0x0100804020100804ULL
};

void initMovesGeneratorRook() {

    const bitboard FILE_A_MASK = BITMASK_A2 | BITMASK_A3 | BITMASK_A4 | BITMASK_A5 | BITMASK_A6 | BITMASK_A7;

    for (int i = 0; i < 64; i++) {
          //get 6-bit mask for a rank
          MOVE_RANK_MASK[i] = (0b01111110ULL) << (RANK_INDEX(i) << 3);

          //compute needed rank shift
          MOVE_RANK_SHIFT[i] = (RANK_INDEX(i) << 3) + 1;

          //get 6-bit mask for a file
          MOVE_FILE_MASK[i] = FILE_A_MASK << FILE_INDEX(i);

          //index magic number directly fo field
          MOVE_FILE_MAGIC[i] = MAGIC_FILE[FILE_INDEX(i)];
      }

      //precompute rank moves
      //for all pieces
      for (int i = 0; i < 64; i++) {
          //for all occupancy states
          for (int n = 0; n < 64; n++) {
              //reconstruct occupancy state
              const bitboard board = moveBitBoard0((bitboard) n, RANK_INDEX(i), 1);

              //generate available moves
              bitboard moves = 0;

              //set piece in Ith position
              bitboard piece = BITMASK_SQUARE(i);

              //move in one direction
              while (piece) {
                  piece = ONE_WEST(piece);

                  moves |= piece;

                  //end when there is another piece on the board (either color, own color will have to be stripped out)
                  if (piece & board) {
                      piece = 0;
                  }
              }

              //set piece back in Ith position
              piece = BITMASK_SQUARE(i);

              //move in other direction
              while (piece) {
                  piece = ONE_EAST(piece);
                  moves |= piece;
                  //end when there is another piece on the board (either color, own color will have to be stripped out)
                  if (piece & board) {
                      piece = 0;
                  }
              }

              //remember the moves
              MOVE_RANK_ATTACKS[i][n] = moves;
          }
      }

      //precompute file moves
      //for all pieces
      for (int i = 0; i < 64; i++) {
          //for all occupancy state indexes
          for (int n = 0; n < 64; n++) {
              //reconstuct the occupancy into file
              const bitboard board = moveBitBoard0(
                      flipDiagA1H8(mirrorHorizontal(moveBitBoard0((bitboard) n, 0, 1))),
                      0,
                      FILE_INDEX(i));

              //generate moves
              bitboard moves = 0;

              //set piece to original Ith index
              bitboard piece = BITMASK_SQUARE(i);

              //move piece in one direction
              while (piece) {
                  piece = ONE_NORTH(piece);
                  moves |= piece;
                  //end when there is another piece on the board (either color, own color will have to be stripped out)
                  if (piece & board) {
                      piece = 0;
                  }
              }

              //set piece back to original Ith index
              piece = BITMASK_SQUARE(i);

              //move piece in other direction
              while (piece) {
                  piece = ONE_SOUTH(piece);
                  moves |= piece;
                  //end when there is another piece on the board (either color, own color will have to be stripped out)
                  if (piece & board) {
                      piece = 0;
                  }
              }

              //remember file attacks
              MOVE_FILE_ATTACKS[i][n] = moves;
          }
      }

}

bitboard generateAttacksRook(const struct chessBoard *board, enum pieceColor color, bitboard allPieces)
{
    bitboard rook = (color == WHITE) ? (board->whiteRook | board->whiteQueen) : (board->blackRook | board->blackQueen);

    bitboard attacks = 0;

    //for all rooks
    while (rook) {
        //get next rook
        const int sourceIndex = bitScan(rook);
        const bitboard source = BITMASK_SQUARE(sourceIndex);

        //use magic multipliers to get occupancy state index
        const int stateIndexRank = (int) ((allPieces & MOVE_RANK_MASK[sourceIndex]) >> MOVE_RANK_SHIFT[sourceIndex]);
        const int stateIndexFile = (int) (((allPieces & MOVE_FILE_MASK[sourceIndex]) * MOVE_FILE_MAGIC[sourceIndex]) >> 57);

        //get possible attacks for field / occupancy state index
        attacks |= MOVE_RANK_ATTACKS[sourceIndex][stateIndexRank];
        attacks |= MOVE_FILE_ATTACKS[sourceIndex][stateIndexFile];

        //remove this rook
        rook ^= source;
    }

    return attacks;
}

void generateMovesRook(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces)
{
     bitboard rook;

      //configure color
      if (board->nextMove == WHITE) {
          rook = board->whiteRook | board->whiteQueen;
      } else {
          rook = board->blackRook | board->blackQueen;
      }

      //for all rooks
      while (rook) {
          //get next rook
          const int sourceIndex = bitScan(rook);
          const bitboard source = BITMASK_SQUARE(sourceIndex);

          //use magic multipliers to get occupancy state index
          const int stateIndexRank = (int) ((allPieces & MOVE_RANK_MASK[sourceIndex]) >> MOVE_RANK_SHIFT[sourceIndex]);
          const int stateIndexFile = (int) (((allPieces & MOVE_FILE_MASK[sourceIndex]) * MOVE_FILE_MAGIC[sourceIndex]) >> 57);

          //get possible moves
          bitboard movesBoard = MOVE_RANK_ATTACKS[sourceIndex][stateIndexRank];
          movesBoard |= MOVE_FILE_ATTACKS[sourceIndex][stateIndexFile];

          //un-mask own color
          movesBoard &= boardAvailable;

          //for all moves
          while (movesBoard) {
              //get current move
              const int targetIndex = bitScan(movesBoard);
              const bitboard target = BITMASK_SQUARE(targetIndex);


              enum chessPiece movingPiece;
              if(board->nextMove == WHITE) {
                if(board->whiteRook & source) {
                    movingPiece = WHITE_ROOK;
                } else {
                    movingPiece = WHITE_QUEEN;
                }
              } else {
                  if(board->blackRook & source) {
                      movingPiece = BLACK_ROOK;
                  } else {
                      movingPiece = BLACK_QUEEN;
                  }
              }
              GENERATE_MOVE(movingPiece, NO_PIECE, sourceIndex, targetIndex, 0);

              //remove move
              movesBoard ^= target;
          }

          //remove this rook
          rook ^= source;
      }
}
