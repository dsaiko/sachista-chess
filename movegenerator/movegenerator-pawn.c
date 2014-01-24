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
    for (int i = 0; i < 64; i++) {
     //put the piece on the board
     bitboard piece = BITMASK_SQUARE(i);

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
        return ONE_NORTH_EAST(board->whitePawn) | ONE_NORTH_WEST(board->whitePawn);
    } else {
        return ONE_SOUTH_EAST(board->blackPawn) | ONE_SOUTH_WEST(board->blackPawn);
    }
}


void generateMovesPawn(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces, const bitboard opponentPieces)
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
            const bitboard source = BITMASK_SQUARE(sourceIndex);

            //get possible moves - moves minus my onw color
            //one step forward
            bitboard movesBoard = ONE_NORTH(source) & emptyBoard;

            //if one step forward was sucessful and we are on base rank, try double move
            if ((movesBoard) && (sourceIndex < 16)) {
                movesBoard |=  ONE_NORTH(movesBoard) & emptyBoard;
            }

            //get attacks, only against oponent pieces
            const bitboard attacks = (ONE_NORTH_EAST(source) | ONE_NORTH_WEST(source));
            movesBoard |=  attacks & oponentPieces;

            //for all moves
            while (movesBoard) {
                //get next move
                const int targetIndex = bitScan(movesBoard);
                const bitboard target = BITMASK_SQUARE(targetIndex);

                const bitboard capture = target & allPieces;


                //white promotion?
                if (targetIndex > 55) {
                    GENERATE_MOVE(WHITE_PAWN, WHITE_BISHOP, sourceIndex, targetIndex, 0, capture);
                    GENERATE_MOVE(WHITE_PAWN, WHITE_KNIGHT, sourceIndex,  targetIndex, 0, capture);
                    GENERATE_MOVE(WHITE_PAWN, WHITE_QUEEN, sourceIndex, targetIndex, 0, capture);
                    GENERATE_MOVE(WHITE_PAWN, WHITE_ROOK,  sourceIndex, targetIndex, 0, capture);
                } else {
                    //normal move/capture
                    GENERATE_MOVE(WHITE_PAWN, NO_PIECE, sourceIndex, targetIndex, 0, capture);
                }

                //remove this move
                movesBoard ^= target;
            }

            //check enpassant capture
            movesBoard = attacks & board->enPassant;
            if (movesBoard) {
              const int targetIndex = bitScan(movesBoard);
              GENERATE_MOVE(WHITE_PAWN, NO_PIECE, sourceIndex, targetIndex, 1, 1);
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
            const bitboard source = BITMASK_SQUARE(sourceIndex);

            //get possible moves - moves minus my onw color
            //one step forward
            bitboard movesBoard = ONE_SOUTH(source) & emptyBoard;

            //if one step forward was sucessful and we are on base rank, try double move
            if ((movesBoard) && (sourceIndex > 47)) {
                movesBoard |=  ONE_SOUTH(movesBoard) & emptyBoard;
            }

            //get attacks, only against oponent pieces
            const bitboard attacks = (ONE_SOUTH_EAST(source) | ONE_SOUTH_WEST(source));
            movesBoard |=  attacks & oponentPieces;

            //for all moves
            while (movesBoard) {
                //get next move
                const int targetIndex = bitScan(movesBoard);
                const bitboard target = BITMASK_SQUARE(targetIndex);

                const bitboard capture = target & allPieces;

                //white promotion?
                if (targetIndex < 8) {
                    GENERATE_MOVE(BLACK_PAWN, BLACK_BISHOP, sourceIndex, targetIndex, 0, capture);
                    GENERATE_MOVE(BLACK_PAWN, BLACK_KNIGHT, sourceIndex, targetIndex, 0, capture);
                    GENERATE_MOVE(BLACK_PAWN, BLACK_QUEEN, sourceIndex, targetIndex, 0, capture);
                    GENERATE_MOVE(BLACK_PAWN, BLACK_ROOK, sourceIndex, targetIndex, 0, capture);
                } else {
                    //normal move/capture
                    GENERATE_MOVE(BLACK_PAWN, NO_PIECE,  sourceIndex, targetIndex, 0, capture);
                }

                //remove this move
                movesBoard ^= target;
            }

            //check enpassant capture
            movesBoard = attacks & board->enPassant;
            if (movesBoard) {
              const int targetIndex = bitScan(movesBoard);
              GENERATE_MOVE(BLACK_PAWN, NO_PIECE, sourceIndex, targetIndex, 1, 1);
            }

            //remove this piece
            pieces ^= source;
        }
    }
}
