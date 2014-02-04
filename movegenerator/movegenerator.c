#include "chessboard.h"
#include "movegenerator.h"

void initMovesGenerator() {
    initMovesGeneratorKnight();
    initMovesGeneratorPawn();
    initMovesGeneratorKing();
    initMovesGeneratorBishop();
    initMovesGeneratorRook();
}

INLINE int generateMoves(const ChessBoard *board, const ChessBoardComputedInfo *boardInfo, Move **moves)
{  
    generateMovesKnight (board, moves, boardInfo);
    generateMovesPawn   (board, moves, boardInfo);
    generateMovesKing   (board, moves, boardInfo);
    generateMovesRook   (board, moves, boardInfo);
    generateMovesBishop (board, moves, boardInfo);
}

bitboard moveBitBoard0(bitboard b, const int up, const int right) {
    //move the piece up or down
    if (up > 0) {
        for(int i=0; i < up; i++)
            b = ONE_NORTH(b);
    } else if(up < 0) {
        for(int i=0; i < -up; i++)
            b = ONE_SOUTH(b);
    }

    //move the piece right or left
    if (right > 0) {
        for(int i=0; i < right; i++)
            b = ONE_EAST(b);
    } else if( right < 0){
        for(int i=0; i < -right; i++)
            b = ONE_WEST(b);
    }
    return b;
}


int isLegal(const ChessBoard *board) {
   const bitboard allPieces = ALL_PIECES(board);
   bitboard rooks;
   bitboard bishops;
   int kingIndex;

   if (board->nextMove == BLACK) {
       //check if white king is not under check
       kingIndex = bitScan(board->whiteKing);


       //check in reverse
       if (board->blackKing & KING_MOVES[kingIndex]) {
           return 0;
       }
       if (board->blackPawn & WHITE_PAWN_ATTACKS[kingIndex]) {
           return 0;
       }
       if (board->blackKnight & KNIGHT_MOVES[kingIndex]) {
           return 0;
       }

       rooks = board->blackQueen | board->blackRook;
       bishops = board->blackQueen | board->blackBishop;

   } else {
       //check if black king is not under check
       kingIndex = bitScan(board->blackKing);

       //check in reverse
       if (board->whiteKing & KING_MOVES[kingIndex]) {
           return 0;
       }
       if (board->whitePawn & BLACK_PAWN_ATTACKS[kingIndex]) {
           return 0;
       }
       if (board->whiteKnight & KNIGHT_MOVES[kingIndex]) {
           return 0;
       }

       rooks = board->whiteQueen | board->whiteRook;
       bishops = board->whiteQueen | board->whiteBishop;

   }

   if (rooks) {
       if (MOVE_RANK_ATTACKS[kingIndex][(int) (((allPieces & MOVE_RANK_MASK[kingIndex]) >> MOVE_RANK_SHIFT[kingIndex]))] & rooks) {
           return 0;
       }
       if (MOVE_FILE_ATTACKS[kingIndex][(int) (((allPieces & MOVE_FILE_MASK[kingIndex]) * MOVE_FILE_MAGIC[kingIndex]) >> 57)] & rooks) {
           return 0;
       }
   }

   if (bishops) {
       if (MOVE_A8H1_ATTACKS[kingIndex][(int) (((allPieces & MOVE_A8H1_MASK[kingIndex]) * MOVE_A8H1_MAGIC[kingIndex]) >> 57)] & bishops) {
           return 0;
       }
       if (MOVE_A1H8_ATTACKS[kingIndex][(int) (((allPieces & MOVE_A1H8_MASK[kingIndex]) * MOVE_A1H8_MAGIC[kingIndex]) >> 57)] & bishops) {
           return 0;
       }
   }

   return 1;
}


int isLegalMove(const ChessBoard *board, const ChessBoardComputedInfo *boardInfo, Move *move) {
    ChessBoard nextBoard = *board;
    makeMove(&nextBoard, ALL_PIECES(&nextBoard), move);
    return isLegal(&nextBoard);
}

