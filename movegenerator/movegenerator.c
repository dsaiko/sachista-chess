/*
  sachista-chess copyright (C) 2014 dusan.saiko@gmail.com

  sachista-chess is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  sachista-chess is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "chessboard.h"
#include "movegenerator.h"

void initMovesGenerator() {
    initMovesGeneratorKnight();
    initMovesGeneratorPawn();
    initMovesGeneratorKing();
    initMovesGeneratorBishop();
    initMovesGeneratorRook();
}

INLINE void generateMoves(const ChessBoard *board, const ChessBoardComputedInfo *boardInfo, Move **moves)
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


int isNotUnderCheck(const ChessBoard *board, const PieceColor nextMove) {
   const bitboard allPieces = ALL_PIECES(board);
   bitboard rooks;
   bitboard bishops;
   int kingIndex;

   if (nextMove == BLACK) {
       //check if white king is not under check
       if(board->whiteKing == 0) return 0;
       kingIndex = bitScan(board->whiteKing);

       if (board->blackPawn & WHITE_PAWN_ATTACKS[kingIndex]) {
           return 0;
       }

       if (board->blackKnight & KNIGHT_MOVES[kingIndex]) {
           return 0;
       }

       if (board->blackKing & KING_MOVES[kingIndex]) {
           return 0;
       }

       rooks = board->blackQueen | board->blackRook;
       bishops = board->blackQueen | board->blackBishop;

   } else {
       //check if black king is not under check
       if(board->blackKing == 0) return 0;
       kingIndex = bitScan(board->blackKing);

       if (board->whitePawn & BLACK_PAWN_ATTACKS[kingIndex]) {
           return 0;
       }

       if (board->whiteKnight & KNIGHT_MOVES[kingIndex]) {
           return 0;
       }

       if (board->whiteKing & KING_MOVES[kingIndex]) {
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


unsigned long long perft(const ChessBoard *board, const int depth)
{
    unsigned long long count = 0;
    if(depth < 1) return 1;

    //compute directly
    Move moves[MAX_MOVES_ARR_SIZE];
    Move *pointer = moves;
    ChessBoardComputedInfo boardInfo = computeInfo(board);

    generateMoves(board, &boardInfo, &pointer);

    Move *iterator = moves;
    ChessBoard nextBoard = *board;
    while(iterator < pointer) {
        makeMove(&nextBoard, boardInfo.allPieces, iterator ++);
        if(isNotUnderCheck(&nextBoard, nextBoard.nextMove)) {
            count += perft(&nextBoard, depth -1);
        }
        nextBoard = *board;
    }

    return count;
}
