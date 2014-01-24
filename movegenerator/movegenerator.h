
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


#define GENERATE_MOVE(PIECE, PROMOTIONPIECE, SOURCEINDEX, TARGETINDEX, ISENPASSANT, ISCAPTURE)                                      \
       if(*moves < arrayEnd) {                                                                                                      \
            *(*moves) =  (struct move){(PIECE), (PROMOTIONPIECE), (SOURCEINDEX), (TARGETINDEX), (ISENPASSANT), ((ISCAPTURE) != 0)}; \
            (*moves)++;                                                                                                             \
       }


void initMovesGeneratorKing();
void initMovesGeneratorRook();
void initMovesGeneratorKnight();
void initMovesGeneratorBishop();
void initMovesGeneratorPawn();

bitboard generateAttacksKing    (const struct chessBoard *board, enum pieceColor color, bitboard allPieces);
bitboard generateAttacksPawn    (const struct chessBoard *board, enum pieceColor color, bitboard allPieces);
bitboard generateAttacksKnight  (const struct chessBoard *board, enum pieceColor color, bitboard allPieces);
bitboard generateAttacksRook    (const struct chessBoard *board, enum pieceColor color, bitboard allPieces);
bitboard generateAttacksBishop  (const struct chessBoard *board, enum pieceColor color, bitboard allPieces);

void generateMovesKing  (const struct chessBoard *board, struct move **moves, const struct move *arrayEnd, const bitboard boardAvailable, const bitboard allPieces, const bitboard opponentPieces);
void generateMovesQueen (const struct chessBoard *board, struct move **moves, const struct move *arrayEnd, const bitboard boardAvailable, const bitboard allPieces, const bitboard opponentPieces);
void generateMovesPawn  (const struct chessBoard *board, struct move **moves, const struct move *arrayEnd, const bitboard boardAvailable, const bitboard allPieces, const bitboard opponentPieces);
void generateMovesRook  (const struct chessBoard *board, struct move **moves, const struct move *arrayEnd, const bitboard boardAvailable, const bitboard allPieces, const bitboard opponentPieces);
void generateMovesBishop(const struct chessBoard *board, struct move **moves, const struct move *arrayEnd, const bitboard boardAvailable, const bitboard allPieces, const bitboard opponentPieces);
void generateMovesKnight(const struct chessBoard *board, struct move **moves, const struct move *arrayEnd, const bitboard boardAvailable, const bitboard allPieces, const bitboard opponentPieces);

#ifdef __cplusplus
}
#endif

#endif //SACHISTA_CHESS_MOVEGENERATOR_H
