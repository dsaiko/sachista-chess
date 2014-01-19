#include "chessboard.h"
#include "movegenerator.h"

bitboard WHITE_PAWN_MOVES[64];
bitboard WHITE_PAWN_DOUBLE_MOVES[64];
bitboard WHITE_PAWN_ATTACKS[64];
bitboard BLACK_PAWN_MOVES[64];
bitboard BLACK_PAWN_DOUBLE_MOVES[64];
bitboard BLACK_PAWN_ATTACKS[64];



void initMovesGeneratorPawn() {
    //for all fields
    int i=0;
    for (i = 0; i < 64; i++) {
     //put the piece on the board
     bitboard piece = BITMASK_SQUARE[i];

     //generate move
     WHITE_PAWN_MOVES[i]         = moveBitBoard0(piece, 1, 0);

     //generate move
     WHITE_PAWN_DOUBLE_MOVES[i]  = moveBitBoard0(piece, 2, 0);

     //generate attacks
     WHITE_PAWN_ATTACKS[i]       = moveBitBoard0(piece, 1, 1) | moveBitBoard0(piece, 1, -1);

     //generate move
     BLACK_PAWN_MOVES[i]         = moveBitBoard0(piece, -1, 0);

     //generate move
     BLACK_PAWN_DOUBLE_MOVES[i]  = moveBitBoard0(piece, -2, 0);

     //generate attacks
     BLACK_PAWN_ATTACKS[i]       = moveBitBoard0(piece, -1, 1) | moveBitBoard0(piece, -1, -1);

    }

}


bitboard generateAttacksPawn(const struct chessBoard *board, enum pieceColor color, bitboard allPieces)
{
    if(color == WHITE) {
        return oneNorthEast(board->whitePawn) | oneNorthWest(board->whitePawn);
    } else {
        return oneSouthEast(board->blackPawn) | oneSouthWest(board->blackPawn);
    }
}


void generateMovesPawn(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces)
{
    const bitboard emptyBoard = ~allPieces;

    if(board->nextMove == WHITE)
    {
        bitboard pieces = board->whitePawn;
        const bitboard oponentPieces = BLACK_PIECES(board);

        //while there are pieces
        while (pieces) {
            //get next piece
            const int sourceIndex = bitScan(pieces);
            const bitboard source = BITMASK_SQUARE[sourceIndex];

            //get possible moves - moves minus my onw color
            //one step forward
            bitboard movesBoard = oneNorth(source) & emptyBoard;

            //if one step forward was sucessful and we are on base rank, try double move
            if ((movesBoard) && (sourceIndex < 16)) {
                movesBoard |=  oneNorth(movesBoard) & emptyBoard;
            }

            //get attacks, only against oponent pieces
            const bitboard attacks = (oneNorthEast(source) | oneNorthWest(source));
            movesBoard |=  attacks & oponentPieces;

            //for all moves
            while (movesBoard) {
                //get next move
                const int targetIndex = bitScan(movesBoard);
                const bitboard target = BITMASK_SQUARE[targetIndex];

                //white promotion?
                if (targetIndex > 55) {
                    ADD_MOVE(WHITE_PAWN, WHITE_BISHOP, 0, 0);
                    ADD_MOVE(WHITE_PAWN, WHITE_KNIGHT, 0, 0);
                    ADD_MOVE(WHITE_PAWN, WHITE_QUEEN, 0, 0);
                    ADD_MOVE(WHITE_PAWN, WHITE_ROOK, 0, 0);
                } else {
                    //normal move/capture
                    ADD_MOVE(WHITE_PAWN, NO_PIECE, 0, 0);
                }

                //remove this move
                movesBoard ^= target;
            }

            //check enpassant capture
            movesBoard = attacks & board->enPassant;
            if (movesBoard) {
              const int targetIndex = bitScan(movesBoard);
              ADD_MOVE(WHITE_PAWN, NO_PIECE, 0, 1);
            }

            //remove this piece
            pieces ^= source;
        }
    } else {
        bitboard pieces = board->blackPawn;
        const bitboard oponentPieces = WHITE_PIECES(board);

        //while there are pieces
        while (pieces) {
            //get next piece
            const int sourceIndex = bitScan(pieces);
            const bitboard source = BITMASK_SQUARE[sourceIndex];

            //get possible moves - moves minus my onw color
            //one step forward
            bitboard movesBoard = oneSouth(source) & emptyBoard;

            //if one step forward was sucessful and we are on base rank, try double move
            if ((movesBoard) && (sourceIndex < 16)) {
                movesBoard |=  oneSouth(movesBoard) & emptyBoard;
            }

            //get attacks, only against oponent pieces
            const bitboard attacks = (oneSouthEast(source) | oneSouthWest(source));
            movesBoard |=  attacks & oponentPieces;

            //for all moves
            while (movesBoard) {
                //get next move
                const int targetIndex = bitScan(movesBoard);
                const bitboard target = BITMASK_SQUARE[targetIndex];

                //white promotion?
                if (targetIndex < 8) {
                    ADD_MOVE(BLACK_PAWN, WHITE_BISHOP, 0, 0);
                    ADD_MOVE(BLACK_PAWN, WHITE_KNIGHT, 0, 0);
                    ADD_MOVE(BLACK_PAWN, WHITE_QUEEN, 0, 0);
                    ADD_MOVE(BLACK_PAWN, WHITE_ROOK, 0, 0);
                } else {
                    //normal move/capture
                    ADD_MOVE(BLACK_PAWN, NO_PIECE, 0, 0);
                }

                //remove this move
                movesBoard ^= target;
            }

            //check enpassant capture
            movesBoard = attacks & board->enPassant;
            if (movesBoard) {
              const int targetIndex = bitScan(movesBoard);
              ADD_MOVE(BLACK_PAWN, NO_PIECE, 0, 1);
            }

            //remove this piece
            pieces ^= source;
        }
    }
}
