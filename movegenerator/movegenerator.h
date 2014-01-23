
#ifndef SACHISTA_CHESS_MOVEGENERATOR_H
#define SACHISTA_CHESS_MOVEGENERATOR_H

#include "bitboard.h"
#include "chesspiece.h"
#include "move.h"
#include "chessboard.h"

#ifdef __cplusplus
extern "C"{
#endif

bitboard moveBitBoard0(bitboard b, const int up, const int right);


#define GENERATE_MOVE(PIECE, PROMOTIONPIECE, SOURCEINDEX, TARGETINDEX, CASTLING, ENPASSANT)                                                                            \
    if(*movesIndex < bufferSize) {                                                                                                      \
       moves[*movesIndex] =  (struct move){(PIECE), (PROMOTIONPIECE), (SOURCEINDEX), (TARGETINDEX), (CASTLING), (ENPASSANT)};               \
       *movesIndex +=1;                                                                                                                 \
    }


void initMovesGeneratorKing();
void initMovesGeneratorRook();
void initMovesGeneratorKnight();
void initMovesGeneratorBishop();
void initMovesGeneratorPawn();

bitboard generateAttacksKing(const struct chessBoard *board, enum pieceColor color, bitboard allPieces);
bitboard generateAttacksPawn(const struct chessBoard *board, enum pieceColor color, bitboard allPieces);
bitboard generateAttacksKnight(const struct chessBoard *board, enum pieceColor color, bitboard allPieces);
bitboard generateAttacksRook(const struct chessBoard *board, enum pieceColor color, bitboard allPieces);
bitboard generateAttacksBishop(const struct chessBoard *board, enum pieceColor color, bitboard allPieces);

void generateMovesKing(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces);
void generateMovesQueen(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces);
void generateMovesPawn(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces);
void generateMovesRook(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces);
void generateMovesBishop(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces);
void generateMovesKnight(const struct chessBoard *board, struct move *moves, const int bufferSize, int *movesIndex, const bitboard boardAvailable, const bitboard allPieces);

#ifdef __cplusplus
}
#endif

#endif //SACHISTA_CHESS_MOVEGENERATOR_H
