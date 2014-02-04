
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


int MOVE_RANK_SHIFT[64];
bitboard MOVE_RANK_MASK[64];
bitboard MOVE_RANK_ATTACKS[64][64];
bitboard MOVE_FILE_MASK[64];
bitboard MOVE_FILE_MAGIC[64];
bitboard MOVE_FILE_ATTACKS[64][64];

bitboard MOVE_A1H8_MASK[64];
bitboard MOVE_A1H8_MAGIC[64];
bitboard MOVE_A8H1_MASK[64];
bitboard MOVE_A8H1_MAGIC[64];

bitboard MOVE_A1H8_ATTACKS[64][64];
bitboard MOVE_A8H1_ATTACKS[64][64];

bitboard KING_MOVES[64];
bitboard WHITE_PAWN_MOVES[64];
bitboard WHITE_PAWN_DOUBLE_MOVES[64];
bitboard WHITE_PAWN_ATTACKS[64];
bitboard BLACK_PAWN_MOVES[64];
bitboard BLACK_PAWN_DOUBLE_MOVES[64];
bitboard BLACK_PAWN_ATTACKS[64];
bitboard KNIGHT_MOVES[64];

void initMovesGeneratorKing();
void initMovesGeneratorRook();
void initMovesGeneratorKnight();
void initMovesGeneratorBishop();
void initMovesGeneratorPawn();

bitboard generateAttacksKing    (const ChessBoard *board, const PieceColor color);
bitboard generateAttacksPawn    (const ChessBoard *board, const PieceColor color);
bitboard generateAttacksKnight  (const ChessBoard *board, const PieceColor color);
bitboard generateAttacksRook    (const ChessBoard *board, const PieceColor color, const bitboard allPieces);
bitboard generateAttacksBishop  (const ChessBoard *board, const PieceColor color, const bitboard allPieces);

void generateMovesKing  (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);
void generateMovesPawn  (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);
void generateMovesRook  (const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);
void generateMovesBishop(const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);
void generateMovesKnight(const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo);


int isLegalMove(const ChessBoard *board, const ChessBoardComputedInfo *boardInfo, Move *move);

INLINE void GENERATE_MOVE(const ChessBoard *board, const ChessBoardComputedInfo *boardInfo, Move **moves, Piece piece, Piece promotionPiece, int sourceIndex, int targetIndex, int isEnPassant) {
    *(*moves) = (Move){(piece), (promotionPiece), (sourceIndex), (targetIndex), (isEnPassant)};
    if(isLegalMove(board, boardInfo, *moves)) {
        (*moves)++;
    }
}

#ifdef __cplusplus
}
#endif

#endif //SACHISTA_CHESS_MOVEGENERATOR_H
