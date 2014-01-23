#include "chessboard.h"
#include "movegenerator.h"

bitboard KING_MOVES[64];

const bitboard WHITE_CASTLE_OO_EMPTY = BITMASK_F1 | BITMASK_G1;
const bitboard WHITE_CASTLE_OO_ATTACKS = BITMASK_E1 | BITMASK_F1 | BITMASK_G1;
const bitboard WHITE_CASTLE_OOO_EMPTY = BITMASK_B1 | BITMASK_C1 | BITMASK_D1;
const bitboard WHITE_CASTLE_OOO_ATTACKS = BITMASK_C1 | BITMASK_D1 | BITMASK_E1;

const bitboard BLACK_CASTLE_OO_EMPTY = BITMASK_F8 | BITMASK_G8;
const bitboard BLACK_CASTLE_OO_ATTACKS = BITMASK_E8 | BITMASK_F8 | BITMASK_G8;
const bitboard BLACK_CASTLE_OOO_EMPTY = BITMASK_B8 | BITMASK_C8 | BITMASK_D8;
const bitboard BLACK_CASTLE_OOO_ATTACKS = BITMASK_C8 | BITMASK_D8 | BITMASK_E8;


void initMovesGeneratorKing() {
   //for all fields
   for (int i = 0; i < 64; i++) {
       //put the piece on the board
       bitboard piece = BITMASK_SQUARE(i);

       //move all directions
       KING_MOVES[i] =
                       moveBitBoard0(piece,  1,  0) |
                       moveBitBoard0(piece,  1,  1) |
                       moveBitBoard0(piece,  0,  1) |
                       moveBitBoard0(piece, -1,  1) |
                       moveBitBoard0(piece, -1,  0) |
                       moveBitBoard0(piece, -1, -1) |
                       moveBitBoard0(piece,  0, -1) |
                       moveBitBoard0(piece,  1, -1)
       ;

   }
}

bitboard generateAttacksKing(const struct chessBoard *board, enum pieceColor color, bitboard allPieces)
{
    bitboard piece;
    if(color == WHITE) {
        piece = board->whiteKing;
    } else {
        piece = board->blackKing;
    }

    if(piece == 0) return 0;

    return KING_MOVES[bitScan(piece)];
}


int isUnderAttack(const struct chessBoard *board, char color, bitboard allPieces, bitboard bitmask) {

    bitboard attacks = generateAttacksRook(board, color, allPieces);
    if(attacks & bitmask) return 1;
    attacks  =  generateAttacksBishop(board, color, allPieces);
    if(attacks & bitmask) return 1;
    attacks  =  generateAttacksKnight(board, color, allPieces);
    if(attacks & bitmask) return 1;
    attacks  =  generateAttacksPawn(board, color, allPieces);
    if(attacks & bitmask) return 1;
    attacks  =  generateAttacksKing(board, color, allPieces);
    if(attacks & bitmask) return 1;

    return 0;
}


void generateMovesKing(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces)
{

    //set up color
        if (board->nextMove == WHITE) {
            const bitboard king = board->whiteKing;
            if (king == 0) return;

            const int sourceIndex = bitScan(king);

            bitboard movesBoard = KING_MOVES[sourceIndex] & boardAvailable;

            //for all moves
            while (movesBoard) {

                //get next move
                const int targetIndex = bitScan(movesBoard);
                const bitboard target = BITMASK_SQUARE(targetIndex);

                GENERATE_MOVE(WHITE_KING, NO_PIECE, sourceIndex, targetIndex, 0);

                //remove this move
                movesBoard ^= target;
            }

            if (board->castlingWhite == 0) return;

            //if castling available
            if ((board->castlingWhite & KING_SIDE) && ((allPieces & WHITE_CASTLE_OO_EMPTY) == 0)) {
                //generate oponent attacks for castling on demand only
                if(isUnderAttack(board, BLACK, allPieces, WHITE_CASTLE_OO_ATTACKS) == 0) {
                    //add short castling move
                    GENERATE_MOVE(WHITE_KING, NO_PIECE, sourceIndex, INDEX_G1, 0);
                }
            }
            if ((board->castlingWhite & QUEEN_SIDE) && ((allPieces & WHITE_CASTLE_OOO_EMPTY) == 0)) {
                if(isUnderAttack(board, BLACK, allPieces, WHITE_CASTLE_OOO_ATTACKS) == 0) {
                    //add long castling move
                    GENERATE_MOVE(WHITE_KING, NO_PIECE, sourceIndex, INDEX_C1, 0);
                }
            }

        } else {
            const bitboard king = board->blackKing;
            if (king == 0) return;

            const int sourceIndex = bitScan(king);

            bitboard movesBoard = KING_MOVES[sourceIndex] & boardAvailable;

            //for all moves
            while (movesBoard) {
                //get next move
                const int targetIndex = bitScan(movesBoard);
                const bitboard target = BITMASK_SQUARE(targetIndex);

                GENERATE_MOVE(BLACK_KING, NO_PIECE, sourceIndex, targetIndex, 0);

                //remove this move
                movesBoard ^= target;
            }

            if (board->castlingBlack == 0) return;

            //if castling available
            if ((board->castlingBlack & KING_SIDE) && ((allPieces & BLACK_CASTLE_OO_EMPTY) == 0)) {
                //generate oponent attacks for castling on demand only
                if(isUnderAttack(board, WHITE, allPieces, BLACK_CASTLE_OO_ATTACKS) == 0) {
                //add short castling move
                    GENERATE_MOVE(BLACK_KING, NO_PIECE, sourceIndex, INDEX_G8, 0);
                }
            }
            if ((board->castlingBlack & QUEEN_SIDE) && ((allPieces & BLACK_CASTLE_OOO_EMPTY) == 0)) {
                if(isUnderAttack(board, WHITE, allPieces, BLACK_CASTLE_OOO_ATTACKS) == 0) {
                    //add long castling move
                    GENERATE_MOVE(BLACK_KING, NO_PIECE, sourceIndex, INDEX_C8, 0);
                }
            }

        }
}


